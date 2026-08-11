//
// Created by Brandon on 8/10/26.
//

#include "RandomESP32.h"
#include <esp_random.h>

namespace rgb::priv {

auto RandomESP32::next() -> u32 {
  return esp_random();
}

}
