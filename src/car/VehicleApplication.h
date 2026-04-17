//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_VEHICLEAPPLICATION_H
#define RGBLIB_VEHICLEAPPLICATION_H

#ifndef RGB_VEHICLE_RX
#define RGB_VEHICLE_RX D11
#endif

#ifndef RGB_VEHICLE_TX
#define RGB_VEHICLE_TX D12
#endif

#include "Application.h"
#include "VehicleApplicationConfigurer.h"
#include "Clock.h"
#include "Vehicle.h"
#include "Timer.h"
#include "Effects.h"
#include "LEDCore.h"
#include "Monitor.h"
#include "Debug.h"
#include "VehicleLogger.h"
#include <mutex>

namespace rgb {

static void vehicleReader(void* args);

struct SubtaskSharedState {
  Vehicle* vehicle;
};

template<typename EventVariantT = SystemEvent>
class VehicleApplication : public Application {
  using Application::on;

public:
  using AnyEvent = EventVariantT;
  using Configurer = VehicleApplicationConfigurer<EventVariantT>;

  VehicleApplication() = default;
  virtual ~VehicleApplication() = default;
  VehicleApplication(const VehicleApplication& rhs) = delete;
  VehicleApplication(VehicleApplication&& rhs) noexcept = delete;
  VehicleApplication& operator=(const VehicleApplication& rhs) = delete;
  VehicleApplication& operator=(VehicleApplication&& rhs) noexcept = delete;

  auto run() -> void;
  auto setup() -> void;
  auto loop() -> void;
  auto publishSystemEvent(const SystemEvent& event) -> void override;
  auto on(size_t uid, Consumer<const SystemEvent&> action) -> void override;
  auto getVehicle() -> Vehicle* override;
  auto isSleeping() -> bool;
  auto goToSleep(Duration time) -> void;
  auto goToSleep() -> void;
  auto wakeUp() -> void;

  static auto PublishEvent(const AnyEvent& event) -> void;

  Vehicle vehicle{};

protected:
  virtual auto configure(Configurer& app) -> void = 0;
  virtual auto update() -> void = 0;
  virtual auto draw() -> void = 0;
  virtual auto postDraw() -> void {};

private:
  auto configureApplication() -> void;
  auto initialize() -> void;
  auto baseUpdate() -> void;
  auto baseDraw() -> void;

  std::vector<LEDCircuit*> mLeds{};
  std::vector<Sensor*> mSensors{};
  std::unordered_map<uint, std::vector<std::function<void(const AnyEvent&)>>> mEventMap{};
  bool mSleeping;
};

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::getVehicle() -> Vehicle* {
  return &vehicle;
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::run() -> void {
  setup();
  loop();
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::setup() -> void {
  rgb::log::init();
  configureApplication();

  xTaskCreatePinnedToCore(vehicleReader, "vehicleReader", RGB_OTHER_CORE_STACK_SIZE, this, RGB_OTHER_CORE_PRIORITY, nullptr, 1);

  initialize();
  publishSystemEvent(WakeEvent{Clock::Now()});
  INFO("Setup Application");
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::loop() -> void {
  Clock::NextFrame();
  baseUpdate();
  if (!mSleeping) {
    baseDraw();
  }
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::initialize() -> void {
  SetupLEDs();
  std::for_each(std::begin(mLeds), std::end(mLeds), [](auto led){ led->start(); });
  std::for_each(std::begin(mSensors), std::end(mSensors), [](auto sensor){ sensor->start(); });
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::baseUpdate() -> void {
  for (auto& sensor : mSensors) {
    sensor->read();
  }
  Timer::ProcessTimers();
  Effects::Update();
  update();
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::baseDraw() -> void {
  std::for_each(std::begin(mLeds), std::end(mLeds), [](auto led){ led->reset(); });
  draw();
  Effects::Draw();
  Debug::Draw();
  postDraw();
  std::for_each(std::begin(mLeds), std::end(mLeds), [](auto led){ led->display(); });
  DisplayLEDs();
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::configureApplication() -> void {
  instance = this;
  vehicle.instance = &vehicle;

#ifdef RGB_ARDUINO_NANO
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
#endif

  Debug::SetBlinker(BlinkerColor::RED, []() { return Debug::HasFault(); });
  Debug::SetBlinker(BlinkerColor::GREEN, [this]() { return vehicle.isConnected(); });

  auto appConfig = Configurer{};
  configure(appConfig);

  mLeds = std::move(appConfig.mLeds);
  mSensors = std::move(appConfig.mSensors);
  mEventMap = std::move(appConfig.mEventMap);

  if (appConfig.mHeartbeat) {
    Debug::SetBlinker(BlinkerColor::PURPLE, []() { return true; });
  }

#if defined(RGB_DEBUG)
  // Monitoring only enabled for Debug configurations since Debug does logging and the monitor relies on that
  Timer::SetTimeout(Duration::Seconds(1), [](auto& context){
    static Monitor monitor;
    monitor.update();
    context.repeatIn = Duration::Seconds(1);
  }).detach();
#endif
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::publishSystemEvent(const SystemEvent& systemEvent) -> void {
  auto event = std::visit([](auto&& e) {
    return AnyEvent{e};
  }, systemEvent);
  auto uid = systemEvent.index();
  if (auto it = mEventMap.find(uid); it != mEventMap.end()) {
    for (auto& handler : it->second) {
      handler(event);
    }
  }
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::on(size_t uid, Consumer<const SystemEvent&> action) -> void {
  mEventMap[uid].push_back([action](auto& anyEvent) {
    if (auto systemEvent = narrow_variant<SystemEvent>(anyEvent)) {
      action(systemEvent.value());
    }
  });
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::PublishEvent(const AnyEvent& event) -> void {
  auto self = static_cast<VehicleApplication<EventVariantT>*>(Application::instance);
  auto uid = event.index();
  if (auto it = self->mEventMap.find(uid); it != self->mEventMap.end()) {
    for (auto& handler : it->second) {
      handler(event);
    }
  }
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::isSleeping() -> bool {
  return mSleeping;
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::goToSleep(rgb::Duration time) -> void {
  publishSystemEvent(SleepEvent{{Clock::Now()}, time});
  Timer::SetTimeout(time, [this](){
    goToSleep();
  }).detach();
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::goToSleep() -> void {
  mSleeping = true;
  Effects::StopAll();
  Timer::StopAll();
}

template<typename EventVariantT>
auto VehicleApplication<EventVariantT>::wakeUp() -> void {
  mSleeping = false;
}

void vehicleReader(void* args) {
  INFO("Vehicle Reader Task Started");

  auto app = static_cast<Application*>(args);
  auto vehicle = app->getVehicle();
  auto logger = VehicleLogger{PinNumber{A3}};
  auto logging = logger.begin();

  vehicle->connect(PinNumber{RGB_VEHICLE_RX}, PinNumber{RGB_VEHICLE_TX});
  while (true) {
    if (!vehicle->isConnected()) {
      if (logging) {
        logger.flush();
      }
      vehicle->connect(PinNumber{RGB_VEHICLE_RX}, PinNumber{RGB_VEHICLE_TX});
    }
    else {
      auto result = vehicle->update();
      if (logging) {
        logger.record(VehicleData{
          .lastUpdateResult = result,
          .rpm = vehicle->rpm(),
          .speed = vehicle->speed(),
          .coolantTemp = vehicle->coolantTemp(),
          .fuelLevel = vehicle->fuelLevel(),
          .throttlePosition = vehicle->throttlePosition(),
        });
      }
    }

    vTaskDelay(pdMS_TO_TICKS(70));
  }
}

}

#endif //RGBLIB_VEHICLEAPPLICATION_H
