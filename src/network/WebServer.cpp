//
// Created by Brandon on 2/17/25.
//

#include "WebServer.h"
#include "Wireless.h"

namespace rgb {

auto WebServer::Instance() -> WebServer& {
  static WebServer instance;
  return instance;
}

auto WebServer::Start() -> void {
  Instance().start();
}

auto WebServer::start() -> void {
  if (started) {
    return;
  }
  Wifi::Start();
  server.begin();
  started = true;
}

auto WebServer::OnGet(const char* uri, HandlerFunction onRequest) -> WebServerHandle {
  return Instance().onGet(uri, onRequest);
}

auto WebServer::onGet(const char* uri, HandlerFunction onRequest) -> WebServerHandle {
  return WebServerHandle { &server.on(uri, HTTP_GET, onRequest) };
}

auto WebServer::RemoveHandler(WebHandler& handle) -> void {
  Instance().removeHandler(handle);
}

auto WebServer::removeHandler(WebHandler& handle) -> void {
  server.removeHandler(&handle);
}

auto HandleDeleter::operator()(WebHandler* ptr) -> void {
  WebServer::RemoveHandler(*ptr);
}

}