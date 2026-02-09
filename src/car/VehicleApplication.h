//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_VEHICLEAPPLICATION_H
#define RGBLIB_VEHICLEAPPLICATION_H

#include "Application.h"
#include "VehicleApplicationConfigurer.h"
#include "Clock.h"
#include "Vehicle.h"
#include "Timer.h"
#include "Effects.h"
#include "LEDCore.h"
#include <mutex>

namespace rgb {

void subtask(void* args);

struct SubtaskSharedState {
  Vehicle* vehicle;
};

template<typename ...UserEvents>
class VehicleApplication : public Application {
  using Application::on;

public:
  using AnyEvent = Event<UserEvents...>;
  using Configurer = VehicleApplicationConfigurer<UserEvents...>;

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


  Clock clock{10};
  std::vector<LEDCircuit*> mLeds{};
  std::vector<Sensor*> mSensors{};
  std::unordered_map<uint, std::vector<std::function<void(const AnyEvent&)>>> mEventMap{};
  QueueHandle_t commandQueue;
  uint lastWakeTime;
};

template<typename... UserEvents>
auto VehicleApplication<UserEvents...>::getVehicle() -> Vehicle* {
  return &vehicle;
}

template<typename ...UserEvents>
auto VehicleApplication<UserEvents...>::run() -> void {
  setup();
  loop();
}

template<typename ...UserEvents>
auto VehicleApplication<UserEvents...>::setup() -> void {
  configureApplication();

  xTaskCreatePinnedToCore(subtask, "Subtask", RGB_OTHER_CORE_STACK_SIZE, this, RGB_OTHER_CORE_PRIORITY, nullptr, 1);

  initialize();
  publishSystemEvent(WakeEvent{Clock::Now()});
  INFO("Setup Application");
}

template<typename ...UserEvents>
auto VehicleApplication<UserEvents...>::loop() -> void {
  clock.startFrame();
  clock.printStats();
  baseUpdate();
  baseDraw();
  clock.endFrame();
}

template<typename ...UserEvents>
auto VehicleApplication<UserEvents...>::initialize() -> void {
  on<OBDIIDisconnected>([](auto& e){
    // TODO - go to sleep
  });

  SetupLEDs();

  std::for_each(std::begin(mLeds), std::end(mLeds), [](auto led){ led->start(); });
  std::for_each(std::begin(mSensors), std::end(mSensors), [](auto sensor){ sensor->start(); });
}

template<typename ...UserEvents>
auto VehicleApplication<UserEvents...>::baseUpdate() -> void {
  for (auto& sensor : mSensors) {
    sensor->read();
  }
  Timer::ProcessTimers();
  Effects::Update();
  update();
}

template<typename ...UserEvents>
auto VehicleApplication<UserEvents...>::baseDraw() -> void {
  std::for_each(std::begin(mLeds), std::end(mLeds), [](auto led){ led->reset(); });
  draw();
  Effects::Draw();
  Debug::Draw();
  postDraw();
  std::for_each(std::begin(mLeds), std::end(mLeds), [](auto led){ led->display(); });
  DisplayLEDs();
}

template<typename ...UserEvents>
auto VehicleApplication<UserEvents...>::configureApplication() -> void {
  instance = this;
  vehicle.instance = &vehicle;
  auto appConfig = VehicleApplicationConfigurer<UserEvents...>{};
  configure(appConfig);

  mLeds = std::move(appConfig.mLeds);
  mSensors = std::move(appConfig.mSensors);
  mEventMap = std::move(appConfig.mEventMap);

  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
}

template<typename... UserEvents>
auto VehicleApplication<UserEvents...>::publishSystemEvent(const SystemEvent& systemEvent) -> void {
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

template<typename... UserEvents>
auto VehicleApplication<UserEvents...>::on(size_t uid, Consumer<const SystemEvent&> action) -> void {
  mEventMap[uid].push_back([action](auto& anyEvent) {
    if (auto systemEvent = narrow_variant<SystemEvent>(anyEvent)) {
      action(systemEvent.value());
    }
  });
}

template<typename ...UserEvents>
auto VehicleApplication<UserEvents...>::PublishEvent(const AnyEvent& event) -> void {
  auto self = static_cast<VehicleApplication<UserEvents...>*>(Application::instance);
  auto uid = event.index();
  if (auto it = self->mEventMap.find(uid); it != self->mEventMap.end()) {
    for (auto& handler : it->second) {
      handler(event);
    }
  }
}

void subtask(void* args) {
  INFO("Subtask Started");

  auto app = static_cast<Application*>(args);
  auto vehicle = app->getVehicle();

  INFO("Starting Subtask");
  vehicle->connect(PinNumber{D11}, PinNumber{D12});
  while (true) {

    if (vehicle->isConnected()) {
      vehicle->update();
    }
    else {
      vehicle->connect(PinNumber{D11}, PinNumber{D12});
    }

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

}

#endif //RGBLIB_VEHICLEAPPLICATION_H
