//
// Created by Brandon on 1/5/25.
//

#include "Scene.h"

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

auto Scene::cleanup() -> void {

}
