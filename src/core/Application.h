//
// Created by Brandon on 1/10/26.
//

#ifndef RGBLIB_APPLICATION_H
#define RGBLIB_APPLICATION_H

#include "EventType.h"
#include "Func.h"

namespace rgb {

class Vehicle;
class Application {
public:
  static Application* instance;
  virtual auto publishSystemEvent(const SystemEvent& event) -> void = 0;

  template<typename T>
  constexpr auto on(Consumer<const T&> action) -> void {
    auto index = EventIndex_v<T, SystemEvent>;
    on(index, [&](auto& eventVariant){
      action(std::get<T>(eventVariant));
    });
  }

  virtual auto on(size_t uid, Consumer<const SystemEvent&> action) -> void = 0;
  virtual auto getVehicle() -> Vehicle* = 0;
};

}

#endif //RGBLIB_APPLICATION_H
