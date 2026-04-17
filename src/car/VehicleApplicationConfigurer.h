//
// Created by Brandon on 10/12/25.
//

#ifndef RGBLIB_VEHICLEAPPLICATIONBUILDER2_H
#define RGBLIB_VEHICLEAPPLICATIONBUILDER2_H

#include <vector>
#include <unordered_map>
#include <typeindex>
#include "EventType.h"
#include "Func.h"
#include "Sensor.h"

namespace rgb {

class LEDCircuit;

template<typename EventVariantT = SystemEvent>
struct VehicleApplicationConfigurer {
  constexpr auto addLEDs(LEDCircuit& circuit) -> VehicleApplicationConfigurer&;
  constexpr auto addSensor(Sensor& sensor) -> VehicleApplicationConfigurer&;

  constexpr auto useHeartbeatLED() -> VehicleApplicationConfigurer&;

  template<typename T>
  constexpr auto on(std::function<void(const T&)> action) -> VehicleApplicationConfigurer&;

  std::vector<LEDCircuit*> mLeds{};
  std::vector<Sensor*> mSensors{};
  std::unordered_map<uint, std::vector<std::function<void(const EventVariantT&)>>> mEventMap{};
  bool mHeartbeat{};
};

template<typename EventVariantT>
constexpr auto VehicleApplicationConfigurer<EventVariantT>::useHeartbeatLED() -> VehicleApplicationConfigurer& {
  mHeartbeat = true;
  return *this;
}

template<typename EventVariantT>
constexpr auto VehicleApplicationConfigurer<EventVariantT>::addLEDs(rgb::LEDCircuit& circuit) -> VehicleApplicationConfigurer& {
  mLeds.push_back(&circuit);
  return *this;
}

template<typename EventVariantT>
constexpr auto VehicleApplicationConfigurer<EventVariantT>::addSensor(Sensor& sensor) -> VehicleApplicationConfigurer& {
  mSensors.push_back(&sensor);
  return *this;
}

template<typename EventVariantT>
template<typename T>
constexpr auto VehicleApplicationConfigurer<EventVariantT>::on(std::function<void(const T&)> action) -> VehicleApplicationConfigurer& {
  auto index = EventIndex_v<T, EventVariantT>;
  mEventMap[index].push_back([action = std::move(action)](auto& e) {
    action(std::get<T>(e));
  });
  return *this;
}

}

#endif //RGBLIB_VEHICLEAPPLICATIONBUILDER_H
