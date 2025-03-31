//
// Created by Brandon on 3/30/25.
//

#ifndef RGBLIB_STARTOTACOMMAND_H
#define RGBLIB_STARTOTACOMMAND_H

#include "threading/ThreadCommand.h"
#include "network/OTASupport.h"

namespace rgb {

class StartOTACommand : public ThreadCommand {
public:
  auto execute() -> void override {
    OTASupport::Start();
  }

  static auto Instance() -> StartOTACommand& {
    static StartOTACommand instance;
    return instance;
  }
};

}


#endif //RGBLIB_STARTOTACOMMAND_H
