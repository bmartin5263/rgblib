# RGBLib

## TODO
- [X] Vehicle Thread to eliminate blocking main thread when accessing vehicle data
- [X] Update sensors on every frame in main thread
- [X] Debug LEDS on top layer
- [X] OTA led turns on even when its not active
- [X] Scene Manager timer for intro
- [ ] Resiliency - able to automatically recover subsystems if connection issues
- [ ] Check if vehicle supports PID
- [ ] Git submodules for libs
- [ ] Library build + import into _another_ project w/o copying and pasting this project into it

## Terminology

### LED vs Pixel vs RGBW
**LED** is the physical component that lights up

**Pixel** is an abstract handle to some LED

**RGB/W** represent the 3/4 possible color channels for an LED. Not all LEDs have W.
May be represented as a `float` value between `[0-1]`, or as a `unsigned char` value (which has a range `[0-255]`)
`float` permits math operations, while physical devices expect `unsinged char`