//
// Created by Brandon on 2/17/25.
//

#include "BasicScene.h"
#include "network/WebServer.h"

namespace rgb {

int counter = 0;
int frame = 0;
constexpr ParameterTable<BasicScene, 7> PARAMETER_MAP {{
  { "speed", [](BasicScene& scene, const String& s){ scene.speed = s.toInt(); } },
  { "r1", [](BasicScene& scene, const String& s){ scene.r1 = s.toInt(); } },
  { "g1", [](BasicScene& scene, const String& s){ scene.g1 = s.toInt(); } },
  { "b1", [](BasicScene& scene, const String& s){ scene.b1 = s.toInt(); } },
  { "r2", [](BasicScene& scene, const String& s){ scene.r2 = s.toInt(); } },
  { "g2", [](BasicScene& scene, const String& s){ scene.g2 = s.toInt(); } },
  { "b2", [](BasicScene& scene, const String& s){ scene.b2 = s.toInt(); } },
}};

auto BasicScene::setup() -> void {
  circuit.setBrightness(brightness);
  circuit.start();

  handle = WebServer::OnGet("/", [this](AsyncWebServerRequest* request){
    INFO("OnGet() /");
    for (const auto& [parameterName, receiver] : PARAMETER_MAP) {
      if (request->hasParam(parameterName)) {
        auto param = request->getParam(parameterName);
        auto valueStr = param->value();
        receiver(*this, valueStr);
      }
    }
    request->send(200);
  });

  handle2 = WebServer::ParameterServer("/params", *this, PARAMETER_MAP);

  button1.onPress([this]() { r2 -= 3; });
  button2.onPress([this]() { r2 += 3; });
  button3.onPress([this]() { brightness -= 3; });
  button4.onPress([this]() { brightness += 3; });
}

auto BasicScene::cleanup() -> void {
  handle.reset();
}

auto BasicScene::update() -> void {
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  ++frame;
  if (frame >= speed) {
    counter = (counter + 1) % 16;
    frame = 0;
  }
}

auto BasicScene::draw() -> void {
  for (int i = 0; i < 6; ++i) {
    auto c = (counter + i) % 16;
    circuit.set(c, Color::FromBytes(r1, g1, b1, 0));
  }
  for (int i = 6; i < 16; ++i) {
    auto c = (counter + i) % 16;
    circuit.set(c, Color::FromBytes(r2, g2, b2, 0));
  }
  circuit.display();
}

}
