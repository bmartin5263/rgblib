//
// Created by Brandon on 3/18/25.
//

#ifndef RGBLIB_ABSTRACTSCENE_H
#define RGBLIB_ABSTRACTSCENE_H

#include "Scene.h"

namespace rgb {

struct Grid;

class ChainableScene : public Scene {
public:
  explicit ChainableScene(Grid* grid);

  auto setup() -> void override;
  auto update() -> void override;
  auto draw() -> void override;
  auto cleanup() -> void override;

  auto setNextScene(ChainableScene* next);
  auto setPreviousScene(ChainableScene* prev);

protected:
  virtual auto userSetup() -> void {};
  virtual auto userUpdate() -> void = 0;
  virtual auto userDraw() -> void = 0;
  virtual auto userCleanup() -> void {};

private:
  Grid* grid;
  ChainableScene* next;
  ChainableScene* prev;

};

}

#endif //RGBLIB_ABSTRACTSCENE_H
