//
// Created by Brandon on 2/17/25.
//

#include "WebServer.h"
#include "Wireless.h"
#include "Assertions.h"

namespace rgb {

auto WebServer::start() -> void {
  if (started) {
    return;
  }
  Wifi::Start();
  server.begin();
  started = true;
}

auto WebServer::onGet(const char* uri, HandlerFunction onRequest) -> WebServerHandle {
  ASSERT(started, "WebServer is not started");
  return WebServerHandle { &server.on(uri, HTTP_GET, onRequest) };
}

auto WebServer::removeHandler(WebHandler& handle) -> void {
  ASSERT(started, "WebServer is not started");
  server.removeHandler(&handle);
}

auto WebServer::Instance() -> WebServer& {
  static WebServer instance;
  return instance;
}

auto WebServer::Start() -> void {
  Instance().start();
}


auto WebServer::OnGet(const char* uri, HandlerFunction onRequest) -> WebServerHandle {
  return Instance().onGet(uri, onRequest);
}


auto WebServer::RemoveHandler(WebHandler& handle) -> void {
  Instance().removeHandler(handle);
}


auto HandleDeleter::operator()(WebHandler* ptr) -> void {
  WebServer::RemoveHandler(*ptr);
}

}