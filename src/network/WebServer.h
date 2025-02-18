//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_WEBSERVER_H
#define RGBLIB_WEBSERVER_H

#include <ESPAsyncWebServer.h>

namespace rgb {

class WebServer {
public:
  static auto Start() -> void;

private:
  AsyncWebServer server{80};
  bool started{false};

  static auto Instance() -> WebServer&;
  auto start() -> void;
};

}


#endif //RGBLIB_WEBSERVER_H
