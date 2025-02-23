//
// Created by Brandon on 2/22/25.
//

#include "NullScene.h"

namespace rgb {

auto NullScene::Instance() -> NullScene& {
  static NullScene instance;
  return instance;
}

}