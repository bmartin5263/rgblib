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
- [ ] Smoothing vehicle value changes

## Debugging Tools

`RGB_DEBUG_ENABLE_DEBUG_SCREEN`
`RGB_DEBUG_ENABLE_ASSERTIONS`
`RGB_DEBUG_ENABLE_LOGGING`
`RGB_DEBUG_ENABLE_LOGGING`

|                     |                                                    |
|---------------------|----------------------------------------------------|
| `INFO(msg, ...)`    | Print a log message with level _Info_              |
| `ERROR(msg, ...)`   | Print a log message with level _Error_             |
| `ASSERT(cond, msg)` | WiFi network password. Required if SSID is defined |
| `RGB_DEBUG`         |                                                    |

## Compilation Flags

|                     |                                                                 |
|---------------------|-----------------------------------------------------------------|
| `RGB_WIFI_SSID`     | SSID of WiFi network to connect to. If defined, WiFi is enabled |
| `RGB_WIFI_PASSWORD` | WiFi network password. Required if SSID is defined              |
| `RGB_DEBUG`         |                                                                 |

## Terminology

### LED vs Pixel vs RGBW
- **LED** is the physical component that lights up
- **Pixel** is an abstract representation to usually 1 LED
- **RGB/W** represent the 3/4 possible color channels for an LED. Not all LEDs have W.
  - App represents them as `float` value between `[0-1]`, but device expects `unsigned char` value (`[0-255]`)