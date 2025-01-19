//
// Created by Brandon on 1/19/25.
//

#ifndef RGBLIB_SOLIDCOLORGENERATOR_H
#define RGBLIB_SOLIDCOLORGENERATOR_H

#include "ColorGenerator.h"

class SolidColorGenerator : public ColorGenerator {
public:
  SolidColorGenerator();
  SolidColorGenerator(const Color& color);

  auto color() -> Color&;
  auto generate(const Parameters& params) -> Color const;

private:
  Color _color;

};


#endif //RGBLIB_SOLIDCOLORGENERATOR_H
