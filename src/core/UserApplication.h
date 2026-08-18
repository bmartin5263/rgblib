//
// Created by Brandon on 10/11/25.
//

#ifndef RGBLIB_USERAPPLICATION_H
#define RGBLIB_USERAPPLICATION_H

#ifndef RGB_OTA
#define RGB_OTA 0
#endif

#include "Application.h"
#include "UserApplicationConfigurer.h"
#include "LEDDevice.h"
#include "Clock.h"
#include "Timer.h"
#include "Effects.h"
#include "Animations.h"
#include "LEDCore.h"
#include "Monitor.h"
#include "Debug.h"

#if RGB_OTA
#include "Wireless.h"
#include "OTASupport.h"
#endif

namespace rgb {

template<typename EventVariantT = SystemEvent>
class UserApplication : public Application {

public:
  using AnyEvent = EventVariantT;
  using Configurer = UserApplicationConfigurer<EventVariantT>;

  UserApplication() = default;

  auto run() -> void;
  auto setup() -> void;
  auto loop() -> void;
  auto publishSystemEvent(const SystemEvent& event) -> void final;

  static auto PublishEvent(const AnyEvent& event) -> void;

protected:
  // For registering LEDs, sensors, configure pins, event handlers, and any other static config.
  // Subsystems are not guaranteed to be available, safer to use 'initialize()' for Effects/Timers
  virtual auto configure(Configurer& app) -> void = 0;

  // For starting effects/timers. Runs right before main loop starts
  virtual auto initialize() -> void {}

  // Called once per-frame, used for updating the state of the application
  virtual auto update() -> void {};

  // Called once per-frame before Effects/Animations run, used for manually drawing individual pixels
  virtual auto draw() -> void {};

  // Called once per-frame after Effects/Animations run, used for manually drawing individual pixels
  virtual auto postDraw() -> void {}

private:
  auto configureApplication() -> void;
  auto startSubsystems() -> void;
  auto baseUpdate() -> void;
  auto baseDraw() -> void;

  std::vector<LEDDevice*> mPixels{};
  std::vector<Sensor*> mSensors{};

protected:
  std::unordered_map<uint, std::vector<EventHandler<AnyEvent>>> mEventMap{};
};

template<typename EventVariantT>
auto UserApplication<EventVariantT>::run() -> void {
  setup();
  while (true) {
    loop();
  }
}

template<typename EventVariantT>
auto UserApplication<EventVariantT>::setup() -> void {
  log::init();
  INFO("Setup Application");
  configureApplication();
  startSubsystems();
  initialize();

#if defined(RGB_DEBUG)
  static Monitor monitor;
  monitor.initialize();
  // Monitoring only enabled for Debug configurations since Debug does logging and the monitor depends on that
  Timer::SetTimeout(Duration::Seconds(1), [](auto& context){
    monitor.update();
    context.repeatIn = Duration::Seconds(1);
  }).detach();
#endif

  PublishEvent(AppReady{{Clock::Now()}});
  Clock::Start();
}

template<typename EventVariantT>
auto UserApplication<EventVariantT>::loop() -> void {
  Clock::NextFrame();
  baseUpdate();
  baseDraw();
}

template<typename EventVariantT>
auto UserApplication<EventVariantT>::startSubsystems() -> void {
  SetupLEDs();
  std::for_each(std::begin(mPixels), std::end(mPixels), [](auto led){ led->start(); });
  std::for_each(std::begin(mSensors), std::end(mSensors), [](auto sensor){ sensor->start(); });

#if RGB_OTA
  Wifi::SetMode(WIFI_STA);
  Wifi::Start();
  OTASupport::Start();
#endif
}

template<typename EventVariantT>
auto UserApplication<EventVariantT>::baseUpdate() -> void {
  for (auto& sensor : mSensors) {
    sensor->read();
  }
#if RGB_OTA
  Wifi::Update();
  OTASupport::Update();
#endif
  Timer::ProcessTimers();
  Effects::Update();
  update();
}

template<typename EventVariantT>
auto UserApplication<EventVariantT>::baseDraw() -> void {
  std::for_each(std::begin(mPixels), std::end(mPixels), [](auto* led){ led->reset(); });
  draw();
  Effects::Draw();
  Animations::Update();
  Debug::Draw();
  postDraw();
  std::for_each(std::begin(mPixels), std::end(mPixels), [](auto* led){ led->display(); });
  DisplayLEDs();
}

template<typename EventVariantT>
auto UserApplication<EventVariantT>::configureApplication() -> void {
  instance = this;

#ifdef RGB_ARDUINO_ESP32
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
#endif
  Debug::SetBlinker(BlinkerColor::RED, [] { return Debug::HasFault(); });
#if RGB_OTA
  Debug::SetBlinker(BlinkerColor::BLUE, [this] { return Wifi::GetStatus() == WL_CONNECTED; });
#endif


  auto appConfig = Configurer{};
  configure(appConfig);

  mPixels = std::move(appConfig.mPixels);
  mSensors = std::move(appConfig.mSensors);
  mEventMap = std::move(appConfig.mEventMap);

  if (appConfig.mHeartbeat) {
    Debug::SetBlinker(BlinkerColor::PURPLE, []() { return true; });
  }
}

template<typename EventVariantT>
auto UserApplication<EventVariantT>::publishSystemEvent(const SystemEvent& systemEvent) -> void {
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
auto UserApplication<EventVariantT>::PublishEvent(const AnyEvent& event) -> void {
  auto self = static_cast<UserApplication*>(instance);
  auto uid = event.index();
  if (auto it = self->mEventMap.find(uid); it != self->mEventMap.end()) {
    for (auto& handler : it->second) {
      handler(event);
    }
  }
}

}

#endif //RGBLIB_USERAPPLICATION_H
