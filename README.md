# RotaryEncoder ESP32

A high-performance rotary encoder library for ESP32 microcontrollers with detent filtering and multi-encoder support.

## Features

- **Template-based design** supporting multiple encoders simultaneously
- **Interrupt-driven operation** for responsive performance
- **Detent filtering** with configurable counts per detent
- **Thread-safe value reading** with atomic operations
- **Optional debug output** via callback functions
- **ESP32 optimized** for excellent performance
- **PEC11 compatible** and works with similar quadrature encoders

## Installation

### PlatformIO

Add to your `platformio.ini`:

```ini
lib_deps = 
    https://github.com/ky1ejs/rotary-encoder-esp32.git
```

### Arduino IDE

1. Download or clone this repository
2. Place in your Arduino libraries folder
3. Restart Arduino IDE

## Quick Start

### Single Encoder

```cpp
#include <RotaryEncoder.h>

// Create encoder on pins 2 and 3 with 4 counts per detent (PEC11 standard)
RotaryEncoder<0> encoder(2, 3, -1, 4);

void debugCallback(int id, int pin_a, int pin_b) {
  Serial.printf("RotaryEncoder %d initialized on pins A=%d, B=%d\n", id, pin_a, pin_b);
}

void setup() {
  Serial.begin(115200);
  encoder.begin(debugCallback);  // Optional debug callback
}

void loop() {
  long value = encoder.getValue();
  Serial.printf("Encoder value: %ld\n", value);
  delay(100);
}
```

### Multiple Encoders

```cpp
#include <RotaryEncoder.h>

// Create multiple encoders with unique template IDs
RotaryEncoder<0> encoder1(2, 3);    // First encoder
RotaryEncoder<1> encoder2(4, 5);    // Second encoder
RotaryEncoder<2> encoder3(6, 7);    // Third encoder

void setup() {
  Serial.begin(115200);
  
  encoder1.begin();
  encoder2.begin();
  encoder3.begin();
}

void loop() {
  Serial.printf("Encoder 1: %ld, Encoder 2: %ld, Encoder 3: %ld\n", 
                encoder1.getValue(), 
                encoder2.getValue(), 
                encoder3.getValue());
  delay(100);
}
```

## API Reference

### Constructor

```cpp
RotaryEncoder<ID>(int pin_a, int pin_b, int pin_sw = -1, int counts_per_detent = 4)
```

- **ID**: Template parameter for unique encoder identification (0, 1, 2, etc.)
- **pin_a**: GPIO pin for encoder A signal
- **pin_b**: GPIO pin for encoder B signal  
- **pin_sw**: GPIO pin for push button (optional, use -1 if not connected)
- **counts_per_detent**: Number of quadrature counts per physical detent (default: 4 for PEC11)

### Methods

#### `bool begin(DebugCallback debug_callback = nullptr)`

Initialize the encoder and attach interrupts.

- **debug_callback**: Optional function called on initialization for debugging
- **Returns**: `true` on success

#### `long getValue()`

Get the current encoder value (thread-safe).

- **Returns**: Current encoder position in detents

### Debug Callback

```cpp
void debugCallback(int id, int pin_a, int pin_b) {
  // Your debug output here
}
```

## Hardware Connection

### PEC11 Rotary Encoder

```
ESP32          PEC11
Pin A    ←→    A (CLK)
Pin B    ←→    B (DT)
GND      ←→    GND
3.3V     ←→    + (via 10kΩ pullup, optional - library uses internal pullups)
```

### Wiring Example

```cpp
// For ESP32-C6 DevKit-C-1
RotaryEncoder<0> encoder(2, 3);  // A=GPIO2, B=GPIO3
```

## Performance Notes

- Uses hardware interrupts for immediate response
- Template-based design eliminates runtime overhead
- Atomic value reading prevents race conditions
- Optimized state machine reduces spurious counts

## Troubleshooting

### Encoder jumps or skips values
- Check wiring connections
- Ensure stable power supply
- Try adjusting `counts_per_detent` (typically 2 or 4)

### Multiple encoders interfering
- Ensure each encoder uses a unique template ID
- Check for pin conflicts
- Verify adequate power supply capacity

### Erratic behavior
- Add hardware debouncing capacitors (100nF between each signal and GND)
- Check for electromagnetic interference
- Ensure proper grounding

## Compatible Hardware

- **ESP32** (all variants)
- **PEC11** rotary encoders
- **EC11** rotary encoders  
- Most quadrature encoders with open-collector or push-pull outputs

## License

MIT License - see LICENSE file for details.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## Author

Kyle Johnson - [kylejs.com](https://kylejs.com)