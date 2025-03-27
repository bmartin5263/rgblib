//
// Created by Brandon on 2/17/25.
//

#include "WebServer.h"

#include <utility>
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

  INFO("WebServer Started");
}

auto WebServer::onGet(const char* uri, HandlerFunction onRequest) -> WebServerHandle {
  INFO("OnGet Setup");
  ASSERT(started, "WebServer is not started");
  auto h = &server.on(uri, HTTP_GET, std::move(onRequest));
  INFO("Activating WebHandle");
  return WebServerHandle { h };
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
  return Instance().onGet(uri, std::move(onRequest));
}


auto WebServer::RemoveHandler(WebHandler& handle) -> void {
  Instance().removeHandler(handle);
}


auto WebServerHandleDeleter::operator()(WebHandler* ptr) -> void {
  INFO("Shutting Down WebHandle");
  WebServer::RemoveHandler(*ptr);
}

}