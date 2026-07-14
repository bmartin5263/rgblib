//
// Created by Brandon on 1/11/26.
//

#ifndef RGBLIB_SYSTEMEVENTS_H
#define RGBLIB_SYSTEMEVENTS_H

#include "Types.h"
#include "IRButtonType.h"

namespace rgb {

struct BaseEvent {
  Timestamp occurredAt;
};

// Nothing happened...
struct NullEvent : BaseEvent {
};

// Car's engine has started
struct VehicleConnected : BaseEvent {};

// Car's engine has stopped
struct VehicleDisconnected : BaseEvent {};

// Car's engine has started
struct CarEngineStarted : BaseEvent {};

// Car's engine has stopped
struct CarEngineStopped : BaseEvent {};

struct IRButtonPressed : BaseEvent {
  IRButtonType button{};
};

}

#endif //RGBLIB_SYSTEMEVENTS_H
