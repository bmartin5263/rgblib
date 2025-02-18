//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_BASICSCENE_H
#define RGBLIB_BASICSCENE_H

#include "Scene.h"

namespace rgb {

class BasicScene : public Scene {
public:
  auto setup() -> void;
  auto update() -> void;
  auto draw() -> void;

private:

};

}


#endif //RGBLIB_BASICSCENE_H
