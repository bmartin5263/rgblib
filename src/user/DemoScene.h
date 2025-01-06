//
// Created by Brandon on 1/5/25.
//

#ifndef RGBLIB_DEMOSCENE_H
#define RGBLIB_DEMOSCENE_H

#include "core/Scene.h"

class DemoScene : public Scene {
public:
  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;

private:

};


#endif //RGBLIB_DEMOSCENE_H
