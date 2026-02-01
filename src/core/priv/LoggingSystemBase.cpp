//
// Created by Brandon on 9/28/25.
//

#include "LoggingSystemBase.h"

namespace rgb::priv {

auto LoggingSystemBase::start() -> void {
}

auto LoggingSystemBase::stop() -> void {
}

auto LoggingSystemBase::writeMessage(const Message& message) -> void {
  messages.push(message);
}


}