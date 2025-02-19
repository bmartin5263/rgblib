//
// Created by Brandon on 2/17/25.
//

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// D2 = D5

#include "WebServer.h"
#include "BasicScene.h"
#include "sensor/PushButton.h"
#include "network/WebServer.h"
#include "led/LEDCircuit.h"

namespace rgb {

LEDCircuit<16> circuit{D2};

int counter = 0;
int frame = 0;

PushButton button1{D4};
PushButton button2{D6};
PushButton button3{D9};
PushButton button4{D12};

auto BasicScene::setup() -> void {
//  circuit.begin();
//  circuit.setBrightness(10);

  circuit.setBrightness(15);
  circuit.start();
  button1.init();

  handle = WebServer::OnGet("/", [this](AsyncWebServerRequest* request){
    if (request->hasParam("speed")) {
      auto param = request->getParam("speed");
      auto valueStr = param->value();
      speed = valueStr.toInt();
    }

    if (request->hasParam("r1")) {
      auto param = request->getParam("r1");
      auto valueStr = param->value();
      r1 = valueStr.toInt();
    }
    if (request->hasParam("g1")) {
      auto param = request->getParam("g1");
      auto valueStr = param->value();
      g1 = valueStr.toInt();
    }
    if (request->hasParam("b1")) {
      auto param = request->getParam("b1");
      auto valueStr = param->value();
      b1 = valueStr.toInt();
    }
    if (request->hasParam("r2")) {
      auto param = request->getParam("r2");
      auto valueStr = param->value();
      r2 = valueStr.toInt();
    }
    if (request->hasParam("g2")) {
      auto param = request->getParam("g2");
      auto valueStr = param->value();
      g2 = valueStr.toInt();
    }
    if (request->hasParam("b2")) {
      auto param = request->getParam("b2");
      auto valueStr = param->value();
      b2 = valueStr.toInt();
    }

    request->send(200);
  });
}

auto BasicScene::cleanup() -> void {
  handle.reset();
}

auto BasicScene::update() -> void {
  auto state = button1.update();
  if (state == ButtonState::PRESS) {
    Log.infoLn("Press1");
  }

  state = button2.update();
  if (state == ButtonState::PRESS) {
    Log.infoLn("Press2");
  }

  state = button3.update();
  if (state == ButtonState::PRESS) {
    Log.infoLn("Press3");
  }

  state = button4.update();
  if (state == ButtonState::PRESS) {
    Log.infoLn("Press4");
  }

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
