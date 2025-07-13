#include <Arduino.h>
#include <RotaryEncoder.h>

// Create multiple encoders to demonstrate the template-based design
RotaryEncoder<0> encoder1(2, 3, -1, 4);    // Primary encoder on pins 2,3
RotaryEncoder<1> encoder2(4, 5, -1, 4);    // Secondary encoder on pins 4,5

// Optional debug callback to show initialization
void debugCallback(int id, int pin_a, int pin_b) {
  Serial.printf("RotaryEncoder %d initialized on pins A=%d, B=%d\n", id, pin_a, pin_b);
}

void setup() {
  Serial.begin(115200);
  
  // Wait for serial connection
  while (!Serial) {
    delay(10);
  }
  
  Serial.println("RotaryEncoder ESP32 - Basic Usage Example");
  Serial.println("==========================================");
  
  // Initialize encoders with debug output
  encoder1.begin(debugCallback);
  encoder2.begin(debugCallback);
  
  Serial.println("Setup complete. Turn the encoders to see values change.");
  Serial.println("Format: Encoder1: value | Encoder2: value");
  Serial.println("");
}

void loop() {
  // Read encoder values (thread-safe)
  long value1 = encoder1.getValue();
  long value2 = encoder2.getValue();
  
  // Display values
  Serial.printf("Encoder1: %4ld | Encoder2: %4ld\n", value1, value2);
  
  // Update every 100ms
  delay(100);
}