//
// Created by Brandon on 8/10/26.
//

#include "RandomStd.h"

namespace rgb::priv {

auto RandomStd::next() -> u32 {
  return mEngine();
}

}
