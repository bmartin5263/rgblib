# RGBLib

## TODO
- [X] Vehicle Thread to eliminate blocking main thread when accessing vehicle data
- [X] Update sensors on every frame in main thread
- [X] Debug LEDS on top layer
- [X] OTA led turns on even when its not active
- [X] Scene Manager timer for intro
- [X] Library build + import into _another_ project w/o copying and pasting this project into it
- [ ] Resiliency - able to automatically recover subsystems if connection issues
  - [X] Vehicle
  - [ ] Wi-Fi
- [ ] Check if vehicle supports PID
- [ ] CICD pipeline

## Terminology

### LED vs Pixel vs RGBW
- **LED** is the physical component that lights up
- **Pixel** is an abstract representation to usually 1 LED
- **RGB/W** represent the 3/4 possible color channels for an LED. Not all LEDs have W.
  - App represents them as `float` value between `[0-1]`, but device expects `unsigned char` value (`[0-255]`)