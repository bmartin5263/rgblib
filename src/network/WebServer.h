//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_WEBSERVER_H
#define RGBLIB_WEBSERVER_H

#include "WebServerFwd.h"
#include "Config.h"
#include "Types.h"
#include "Log.h"

namespace rgb {

class WebServer {
public:
  static auto Start() -> void;
  static auto OnGet(const char* uri, HandlerFunction onRequest) -> WebServerHandle;
  static auto RemoveHandler(WebHandler& handle) -> void;

  template<class T, size_t N>
  static auto ParameterServer(const char* uri, T& target, const ParameterTable<T, N>& mapping) -> WebServerHandle {
    return Instance().parameterServer(uri, target, mapping);
  }

private:
  AsyncWebServer server{80};
  bool started{false};

  static auto Instance() -> WebServer&;

  auto start() -> void;
  auto onGet(const char* uri, HandlerFunction onRequest) -> WebServerHandle;
  auto removeHandler(WebHandler& handle) -> void;

  template<class T, size_t N>
  auto parameterServer(const char* uri, T& target, const ParameterTable<T, N>& mapping) {
    return onGet(uri, [&mapping, &target, uri](AsyncWebServerRequest* request){
      INFO("OnGet() %s", uri);
      for (const auto& [parameterName, receiver] : mapping) {
        if (request->hasParam(parameterName)) {
          auto param = request->getParam(parameterName);
          auto valueStr = param->value();
          receiver(target, valueStr);
        }
      }
      request->send(200);
    });
  }
};

}


#endif //RGBLIB_WEBSERVER_H
