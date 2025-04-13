# RGBLib

## TODO
- [X] Vehicle Thread to eliminate blocking main thread when accessing vehicle data
- [ ] Update sensors on every frame in main thread
- [ ] Debug LEDS on top layer
- [ ] Resiliency - able to automatically recover subsystems if connection issues
- [ ] OTA led turns on even when its not active
- [ ] Check if vehicle supports PID
- [ ] Git submodules for libs
- [ ] Scene Manager timer for intro

## Terminology

### LED vs Pixel vs RGBW
**LED** is the physical component that lights up

**Pixel** is an abstract handle to some LED

**RGB/W** represent the 3/4 possible color channels for an LED. Not all LEDs have W.
May be represented as a `float` value between `[0-1]`, or as a `unsigned char` value (which has a range `[0-255]`)
`float` permits math operations, while physical devices expect `unsinged char`