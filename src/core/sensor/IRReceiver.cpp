//
// Created by Brandon on 5/13/25.
//

#include "IRReceiver.h"

#undef LOCAL_TRACE
#undef LOCAL_DEBUG
#undef DEBUG
#undef TRACE
#define SEND_PWM_BY_TIMER       // the best and default method for ESP32 etc.
#include <IRremote.hpp>
#include "Application.h"
#include "Clock.h"
#include "Log.h"

namespace rgb {

IRReceiver::IRReceiver(PinNumber pin): pin(pin) {}

auto IRReceiver::doStart() -> bool {
  IrReceiver.begin(pin.to<uint_fast8_t>(), false);
  INFO("Started IRReceiver on Pin %i", pin.to<uint_fast8_t>());
  return true;
}

auto IRReceiver::doRead() -> void {
  if (IrReceiver.decode()) {
//    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
//      IrReceiver.resume();
//      return;
//    }
//    IrReceiver.printIRResultShort(&Serial);
//    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
//      IrReceiver.printIRResultRawFormatted(&Serial, true);
//    }
//    switch (IrReceiver.decodedIRData.protocol) {
//      case UNKNOWN:         INFO("Protocol: UNKNOWN"); break;
//      case PULSE_DISTANCE:  INFO("Protocol: PULSE_DISTANCE"); break;
//      case PULSE_WIDTH:     INFO("Protocol: PULSE_WIDTH"); break;
//      case DENON:           INFO("Protocol: DENON"); break;
//      case JVC:             INFO("Protocol: JVC"); break;
//      case LG:              INFO("Protocol: LG"); break;
//      case LG2:             INFO("Protocol: LG2"); break;
//      case NEC:             INFO("Protocol: NEC"); break;
//      case NEC2:            INFO("Protocol: NEC2"); break;
//      case ONKYO:           INFO("Protocol: ONKYO"); break;
//      case APPLE:           INFO("Protocol: APPLE"); break;
//      case PANASONIC:       INFO("Protocol: PANASONIC"); break;
//      case KASEIKYO:        INFO("Protocol: KASEIKYO"); break;
//      case KASEIKYO_DENON:  INFO("Protocol: KASEIKYO_DENON"); break;
//      case KASEIKYO_SHARP:  INFO("Protocol: KASEIKYO_SHARP"); break;
//      case KASEIKYO_JVC:    INFO("Protocol: KASEIKYO_JVC"); break;
//      case KASEIKYO_MITSUBISHI: INFO("Protocol: KASEIKYO_MITSUBISHI"); break;
//      case RC5:             INFO("Protocol: RC5"); break;
//      case RC6:             INFO("Protocol: RC6"); break;
//      case RC6A:            INFO("Protocol: RC6A"); break;
//      case SAMSUNG:         INFO("Protocol: SAMSUNG"); break;
//      case SAMSUNG48:       INFO("Protocol: SAMSUNG48"); break;
//      case SAMSUNGLG:      INFO("Protocol: SAMSUNG_LG"); break;
//      case SHARP:           INFO("Protocol: SHARP"); break;
//      case SONY:            INFO("Protocol: SONY"); break;
//      case BANG_OLUFSEN:    INFO("Protocol: BANG_OLUFSEN"); break;
//      case BOSEWAVE:        INFO("Protocol: BOSEWAVE"); break;
//      case LEGO_PF:         INFO("Protocol: LEGO_PF"); break;
//      case MAGIQUEST:       INFO("Protocol: MAGIQUEST"); break;
//      case WHYNTER:         INFO("Protocol: WHYNTER"); break;
//      case FAST:            INFO("Protocol: FAST"); break;
//      default:              INFO("Protocol: OTHER (%d)", IrReceiver.decodedIRData.protocol); break;
//    }
    auto rawData = IrReceiver.decodedIRData.decodedRawData;
    auto data = static_cast<IRButtonType>(rawData);
    Application::PublishSystemEvent(IRButtonPressed{{Clock::Now()}, data});
    lastCommand = data;
    IrReceiver.resume();
  }
  else {
    lastCommand = std::nullopt;
  }
}

}