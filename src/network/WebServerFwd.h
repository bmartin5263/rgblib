//
// Created by Brandon on 2/18/25.
//

#ifndef RGBLIB_WEBSERVERFWD_H
#define RGBLIB_WEBSERVERFWD_H

#include "ESPAsyncWebServer.h"

namespace rgb {

class HandleDeleter;
using HandlerFunction = ArRequestHandlerFunction;
using WebHandler = AsyncWebHandler;

struct HandleDeleter {
  constexpr HandleDeleter() noexcept = default;
  auto operator()(WebHandler* ptr) -> void;
};

using WebServerHandle = std::unique_ptr<WebHandler, HandleDeleter>;

}

#endif //RGBLIB_WEBSERVERFWD_H
