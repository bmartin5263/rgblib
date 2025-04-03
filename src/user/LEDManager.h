//
// Created by Brandon on 3/20/25.
//

#ifndef RGBLIB_NEOPIXEL_LED_MANAGER_H
#define RGBLIB_NEOPIXEL_LED_MANAGER_H

#include <array>
#include "ILEDManager.h"
#include "led/LEDCircuit.h"

template <uint N>
class LEDManager : public rgb::ILEDManager {
public:
  LEDManager(rgb::LEDCircuit<N>& circuit):
    circuit(circuit) {

  }

  auto clear() -> void override {
    circuit.clear();
  }

  auto display() -> void override {
    circuit.display();
  }

private:
  rgb::LEDCircuit<N>& circuit;
};


#endif //RGBLIB_NEOPIXEL_LED_MANAGER_H
