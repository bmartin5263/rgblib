//
// Created by Brandon on 1/10/26.
//

#include "ReversePixelList.h"

namespace rgb {

ReversePixelList::ReversePixelList(PixelList& source) :
  mSource(source)
{
}

auto ReversePixelList::length() const -> uint {
  return mSource.length();
}

auto ReversePixelList::get(uint pixel) const -> Pixel {
  return mSource.get(mSource.length() - 1 - pixel);
}

auto ReversePixelList::set(uint pixel, const Color& color) -> void {
  mSource.set(mSource.length() - 1 - pixel, color);
}

}
