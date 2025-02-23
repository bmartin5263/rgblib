//
// Created by Brandon on 2/22/25.
//

#ifndef RGBLIB_NULLSCENE_H
#define RGBLIB_NULLSCENE_H

#include "Scene.h"

namespace rgb {

class NullScene : public Scene {
public:
  constexpr NullScene() = default;
  auto update() -> void override {
    Log.infoLn("NullScene::update()");
  }
  auto draw() -> void override {
    Log.infoLn("NullScene::draw()");
  }
  static auto Instance() -> NullScene&;
};

}

#endif //RGBLIB_NULLSCENE_H
