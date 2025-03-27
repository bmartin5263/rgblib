# RGBLib

## Terminology

### LED vs Pixel vs RGBW
**LED** is the physical component that lights up

**Pixel** is an abstract handle to some LED

**RGB/W** represent the 3/4 possible color channels for an LED. Not all LEDs have W.
May be represented as a `float` value between `[0-1]`, or as a `unsigned char` value (which has a range `[0-255]`)
`float` permits math operations, while physical devices expect `unsinged char`

### Circuit
Can refer to the physical electrical circuit between the controller and its lights. 
Or the abstract representation of that circuit. 

Circuits often have their data stored in contiguous memory, so fewer circuits means less memory jumps 
when writing the data to the driver. This is based on how Neopixel library will allocate memory for all the
LEDs contiguously, but if you have another circuit it gets its own memory possibly far away from the original
circuit.

### Driver
Handles writing out the abstract color data to the physical device.

### Grid
All the components connected to a LED controller. Includes the controller, LEDs, sensors, and more.

### Constellation
A group of LEDs, sensors, and other components within a Grid
