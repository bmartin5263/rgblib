//
// Created by Brandon on 4/19/25.
//

#include "DemoScene.h"
#include "PixelList.h"

using namespace rgb;

DemoScene::DemoScene(rgb::PixelList& ring)
  : ring(ring) {

}

auto DemoScene::setup() -> void {

}

auto DemoScene::update() -> void {

}

auto DemoScene::draw() -> void {
  fillEffect.draw(ring);
}