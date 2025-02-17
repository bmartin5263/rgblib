//
// Created by Brandon on 2/16/25.
//

#ifndef RGBLIB_WIFI_H
#define RGBLIB_WIFI_H


class OTASupport {
public:
  static auto Start() -> void;
  static auto Update() -> void;

private:
  bool started{false};

  auto start() -> void;
  auto update() -> void;

  static const char* SSID;
  static const char* PASSWORD;
  static auto Instance() -> OTASupport&;
};


#endif //RGBLIB_WIFI_H
