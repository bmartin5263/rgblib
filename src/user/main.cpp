#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel circuit(16, D2, NEO_GRBW + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  circuit.begin();
  circuit.setBrightness(10);

  circuit.clear();
  for (int i = 0; i < 16; ++i) {
    circuit.setPixelColor(i, 0, 0, 255);
  }
  circuit.show();
}

void loop() {

}