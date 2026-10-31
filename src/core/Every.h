//
// Created by Brandon on 5/31/25.
//

#ifndef RGBLIB_EVERY_H
#define RGBLIB_EVERY_H

#include "Types.h"
#include "Func.h"
#include "Clock.h"

namespace rgb {
/**
 * Returns 'true' if it has been at least 'duration' since 'lastExecutedAt', and updates 'lastExecutedAt'.
 * Returns 'false' if otherwise.
 *
 * Usage may look like
 * <pre>
 * if (static auto lastUpdated = Timestamp{}; Every(Duration::Seconds(1), lastUpdated)) {
 *   // Action to be done every second
 * }
 * </pre>
 */
[[nodiscard]]
inline auto Every(Duration duration, Timestamp& lastExecutedAt) -> bool {
  if (auto now = Clock::Now(); now.timeSince(lastExecutedAt) >= duration) {
    lastExecutedAt = now;
    return true;
  }
  return false;
}

}


#endif //RGBLIB_EVERY_H
