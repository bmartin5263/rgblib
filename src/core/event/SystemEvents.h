//
// Created by Brandon on 1/11/26.
//

#ifndef RGBLIB_SYSTEMEVENTS_H
#define RGBLIB_SYSTEMEVENTS_H

#include "Types.h"
#include "IRButtonType.h"

namespace rgb {

struct BaseEvent {
  Timestamp when;
};

// Nothing happened...
struct NullEvent : public BaseEvent {
};

// System woke up from its sleep
struct WakeEvent : public BaseEvent {};

// System is going to sleep soon
struct SleepEvent : public BaseEvent {
   Duration timeLimit; // how long before the system ACTUALLY goes to sleep
};

// Car's engine has started
struct OBDIIConnected : public BaseEvent {};

// Car's engine has stopped
struct OBDIIDisconnected : public BaseEvent {};

// Car's engine has started
struct CarEngineStarted : public BaseEvent {};

// Car's engine has stopped
struct CarEngineStopped : public BaseEvent {};

// Hard brake threshold was crossed
struct HardBrakeDetected : public BaseEvent {};

struct IRButtonPressed : public BaseEvent {
  IRButtonType button{};
};

struct CarMoving : public BaseEvent {
  revs_per_minute rpm{};
};

struct CarStopped : public BaseEvent {};

struct RainbowModeEntered : public BaseEvent {};

struct RainbowModeExited : public BaseEvent {};

}

#endif //RGBLIB_SYSTEMEVENTS_H
