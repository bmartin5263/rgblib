//
// Created by Brandon on 1/10/26.
//

#ifndef RGBLIB_APPLICATION_H
#define RGBLIB_APPLICATION_H

#include "EventType.h"
#include "Func.h"

namespace rgb {

class Application {
public:
  static Application* instance;
  virtual auto publishSystemEvent(const SystemEvent& event) -> void = 0;

  template<typename T>
  static auto PublishSystemEvent(const T& event) -> void {
    instance->publishSystemEvent(SystemEvent{event});
  }

  virtual ~Application() = default;
protected:
  Application() = default;
  Application(const Application& rhs) = delete;
  Application(Application&& rhs) noexcept = delete;
  Application& operator=(const Application& rhs) = delete;
  Application& operator=(Application&& rhs) noexcept = delete;
};

}

#endif //RGBLIB_APPLICATION_H
