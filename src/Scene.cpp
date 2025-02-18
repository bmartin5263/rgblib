//
// Created by Brandon on 1/5/25.
//

#include "Scene.h"
#include "Log.h"

namespace rgb {

auto Scene::doSetup() -> void {
  setup();
}

auto Scene::doUpdate() -> void {
  update();
}

auto Scene::doDraw() -> void {
  draw();
}

auto Scene::doCleanup() -> void {
  cleanup();
}

auto NullScene::Instance() -> NullScene& {
  static NullScene instance;
  return instance;
}

}