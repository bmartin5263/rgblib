//
// Created by Brandon on 2/17/25.
//

#ifndef RGBLIB_BASICSCENE_H
#define RGBLIB_BASICSCENE_H

#include "Scene.h"
#include "network/WebServerFwd.h"

namespace rgb {

class BasicScene : public Scene {
public:
  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;
  auto cleanup() -> void override;

private:
  WebServerHandle handle{};
  int speed{200};
  u8 r1{255};
  u8 g1{0};
  u8 b1{0};
  u8 r2{16};
  u8 g2{0};
  u8 b2{0};
};

}


#endif //RGBLIB_BASICSCENE_H
