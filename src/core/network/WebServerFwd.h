//
// Created by Brandon on 2/18/25.
//

#ifndef RGBLIB_WEBSERVERFWD_H
#define RGBLIB_WEBSERVERFWD_H

#if defined(RGB_ARDUINO_ESP32)

#include <utility>
#include "ESPAsyncWebServer.h"
#include "Types.h"

namespace rgb {

struct WebServerHandleDeleter;
using HandlerFunction = ArRequestHandlerFunction;
using WebHandler = AsyncWebHandler;

struct WebServerHandleDeleter {
  constexpr WebServerHandleDeleter() noexcept = default;
  auto operator()(WebHandler* ptr) -> void;
};

using WebServerHandle = std::unique_ptr<WebHandler, WebServerHandleDeleter>;

template<typename T>
using ParameterMapping = std::pair<cstring, void (*)(T& scene, const String& s)>;

template<typename T, int N>
using ParameterTable = std::array<ParameterMapping<T>, N>;

}

#endif //defined(RGB_ARDUINO_ESP32)

#endif //RGBLIB_WEBSERVERFWD_H
