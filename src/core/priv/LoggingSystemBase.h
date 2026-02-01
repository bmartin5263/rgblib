//
// Created by Brandon on 9/28/25.
//

#ifndef RGBLIB_LOGGINGSYSTEMBASE_H
#define RGBLIB_LOGGINGSYSTEMBASE_H

#include <array>
#include <string>
#include "CircularLog.h"

namespace rgb::priv {

class LoggingSystemBase {
public:
  static constexpr auto BUFFER_SIZE = 20;
  using Message = std::string;
  using MessageBuffer = CircularLog<std::array<Message, BUFFER_SIZE>>;

  auto start() -> void;
  auto stop() -> void;

  auto writeMessage(const Message& message) -> void;
  auto flush() -> void;

private:
  MessageBuffer messages{};
};

}


#endif //RGBLIB_LOGGINGSYSTEMBASE_H
