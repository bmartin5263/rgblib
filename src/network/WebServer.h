//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_WEBSERVER_H
#define RGBLIB_WEBSERVER_H

#include "WebServerFwd.h"
#include "Config.h"
#include "Types.h"

namespace rgb {

class WebServer {
public:
  static auto Start() -> void;
  static auto OnGet(const char* uri, HandlerFunction onRequest) -> WebServerHandle;

private:
  friend class HandleDeleter;

  AsyncWebServer server{config::WEB_SERVER_PORT};
  bool started{false};

  static auto Instance() -> WebServer&;
  static auto RemoveHandler(WebHandler& handle) -> void;

  auto start() -> void;
  auto onGet(const char* uri, HandlerFunction onRequest) -> WebServerHandle;
  auto removeHandler(WebHandler& handle) -> void;
};

}


#endif //RGBLIB_WEBSERVER_H
