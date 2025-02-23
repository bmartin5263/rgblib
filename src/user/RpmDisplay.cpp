//
// Created by Brandon on 2/21/25.
//

#include "RpmDisplay.h"
#include "network/WebServer.h"

namespace rgb {

constexpr ParameterTable<RpmDisplay, 6> PARAMETER_MAP {{
  { "bright", [](RpmDisplay& scene, const String& s){ scene.brightBrightness = s.toInt(); } },
  { "master", [](RpmDisplay& scene, const String& s){ scene.masterBrightness = s.toInt(); } },
  { "dim", [](RpmDisplay& scene, const String& s){ scene.dimBrightness = s.toInt(); } },
  { "number", [](RpmDisplay& scene, const String& s){ scene.number = s.toInt(); } },
  { "colors", [](RpmDisplay& scene, const String& s){ scene.colorMap = std::string(s.c_str()); } },
  { "speed", [](RpmDisplay& scene, const String& s){ scene.speed = s.toInt(); } },
}};

auto RpmDisplay::setup() -> void {
  Log.infoLn("RPM setup");
  circuit.setBrightness(masterBrightness);
  handle = WebServer::ParameterServer("/params", *this, PARAMETER_MAP);
}

auto RpmDisplay::update() -> void {
  if (++frame >= speed) {
    if (number <= 0 || number >= 11 ) {
      change = -change;
    }
    number += change;
    frame = 0;
  }

  circuit.setBrightness(masterBrightness);
}

constexpr size_t OFFSET = 1;
constexpr u16 remap(int i) {
  return (i + OFFSET) % 12;
}

auto RpmDisplay::draw() -> void {
  for (int i = 0; i < 10; ++i) {

    float brightness;
    if (i < number) {
      brightness = ByteToFloat(brightBrightness);
    }
    else {
      brightness = ByteToFloat(dimBrightness);
    }

    char colorChar = colorMap[i];
    auto c = Color::BLUE();
    if (i < colorMap.size()) {
      if (colorChar == 'g') {
        c = Color::GREEN(brightness);
      }
      else if (colorChar == 'y') {
        c = Color::YELLOW(brightness);
      }
      else if (colorChar == 'r') {
        c = Color::RED(brightness);
      }
      else if (colorChar == 'p') {
        c = Color::MAGENTA(brightness);
      }
      else if (colorChar == 'c') {
        c = Color::CYAN(brightness);
      }
      else if (colorChar == 'b') {
        c = Color::BLUE(brightness);
      }
      else if (colorChar == 'w') {
        c = Color::WHITE(brightness);
      }
    }

    circuit[remap(i)] = c;
  }

  circuit.display();
}

}