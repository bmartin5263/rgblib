//
// Created by Brandon on 1/11/26.
//

#ifndef RGBLIB_PIXELSTITCH_H
#define RGBLIB_PIXELSTITCH_H

#include "PixelList.h"

namespace rgb {

class PixelStitch : public PixelList {
public:
  PixelStitch(
    PixelList& leftStart,
    PixelList& rightStart
  );

  PixelStitch(
    PixelList& leftStart,
    uint leftLength,
    PixelList& rightStart,
    uint rightLength
  );



  auto length() const -> uint override;
  auto get(uint pixel) const -> Pixel override;
  auto set(uint pixel, const Color& color) -> void override;

private:
  PixelList* leftStart;
  PixelList* rightStart;
  uint leftLength;
  uint rightLength;
};

}

#endif //RGBLIB_PIXELSTITCH_H
