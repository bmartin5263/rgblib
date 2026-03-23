# RGBLib

C++ library for complex LED projects

## Rendering

### Effect System
Effects are one of the ways to color pixels. 

The primary way to customize the coloring behavior of Effects is through a **Shader**.
A shader is a function that is invoked for each "activated" pixel. 
It takes in the pixel's current color and a set of parameters that vary depending on the effect and returns a new color for that pixel

Different effects activate pixels in different ways, for example a fill effect will activate all pixels uniformly and has no concept of cycles. Its only shader parameter is the pixel's position.
In contrast, a Chase effect activates only a subset of Pixels on a given strip based on the position of activated segment. 
It's Shader has more information about what cycle the effect is in, what position within the segment the pixel is, its overall position in the strip, etc.

#### Builtin

| Effect             | Cycles | Activation Pattern (for a given PixelList)                                |
|--------------------|--------|---------------------------------------------------------------------------|
| Fill               | No     | All pixels uniformly                                                      |
| Chase              | Yes    | Segment of pixels that moves along a linear path                          |
| Chase (speed only) | Yes    | Chase, but with speed-only restriction optimized for smooth speed changes |
| Wipe               | Yes    | Overlapping linear fills                                                  |

`TODO`

| Effect   | Activation Pattern (for a given PixelList) | Cycles |
|----------|--------------------------------------------|--------|
| Pixelate | All pixels randomly over time              | Yes    |

## Debugging Tools

### Built-in LED (todo)

| Color  | Meaning              |
|--------|----------------------|
| Red    |                      |
| Yellow |                      |
| Green  | Connected to Vehicle |
| Cyan   |                      |
| Blue   | Connected to WiFi    |
| Purple |                      |


### Logs
Macros such as `INFO()` and `ERROR()` can be used to print logs to the Serial output. The library makes
use of these macros for reporting issues at runtime

| Logging Macro      | Description                                                                                |
|--------------------|--------------------------------------------------------------------------------------------|
| `PRINTF(msg, ...)` | Print a log message without any header/timestamp. Always enabled, intended for real output |
| `TRACE(msg, ...)`  | Print a log message with level _Trace_. Intended for low-level or frequent messages        |
| `INFO(msg, ...)`   | Print a log message with level _Info_. Intended for high-level messages                    |
| `ERROR(msg, ...)`  | Print a log message with level _Error_. Intended for abnormal events                       |

| Configuration Macro | Description                                                                 |
|---------------------|-----------------------------------------------------------------------------|
| `RGB_DEBUG`         | Sets `RGB_LOG_LEVEL` to `1`. Meant to do other debug-related things as well |
| `RGB_LOG_LEVEL`     | `0=ERROR`, `1=INFO`, `2=TRACE`. Defaults to `0`                             |

## Terminology

### LED vs Pixel vs RGBW
- **LED** is the physical component that lights up
- **Pixel** is an abstract representation to usually 1 LED
- **RGB/W** represent the 3/4 possible color channels for an LED. Not all LEDs have W.
  - App represents them as `float` value between `[0-1]`, but device expects `unsigned char` value (`[0-255]`)

## TODO 

(in no particular order)

- Debug LED Flashes
  - Make it so that we can blink the debug LED colors depending on system status
  - Every 3 seconds or so, the LED will blink and cycle through all colors that represent system codes
    - Second 1 - Nothing
    - Second 2 - Nothing
    - Second 3 - Start Debug Flashing, flash the first color, then the next after a fraction of a second, until all codes are displayed
  - Green Flash = Connected to Vehicle
  - Blue Flash = Connected to WIFI
  - etc
- Extract out Vehicle stuff, make a generic vehicle-less application
  - Some projects exist outside a vehicle (obviously), shouldn't have to bring in the vehicle connection stuff if not needed
- Effects should have a delay until they start again, so we don't _need_ DeadPixelLists
- Unit Tests
  - Lots of stuff can be unit tested, let's start
