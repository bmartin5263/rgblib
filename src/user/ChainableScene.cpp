//
// Created by Brandon on 3/18/25.
//

#include "ChainableScene.h"
#include "user/Grid.h"

namespace rgb {

ChainableScene::ChainableScene(Grid* grid): grid(grid) {

}

auto ChainableScene::setup() -> void {
  userSetup();
}

auto ChainableScene::update() -> void {
  userUpdate();
}

auto ChainableScene::draw() -> void {
  userDraw();
}

auto ChainableScene::cleanup() -> void {
  userCleanup();
}

}