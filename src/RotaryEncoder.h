/*
 * RotaryEncoder.h - ESP32 Rotary Encoder Library with Detent Filtering
 * Supports PEC11 and similar quadrature encoders with push buttons
 *
 * Features:
 * - Template-based design supporting multiple encoders
 * - Detent filtering with configurable counts per detent
 * - Interrupt-driven for responsive performance
 * - Thread-safe value reading
 * - Optional debug output via callback
 */

#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include <Arduino.h>

template <int ID>
class RotaryEncoder {
 public:
  using DebugCallback = void (*)(int id, int pin_a, int pin_b);

  RotaryEncoder(int pin_a, int pin_b, int pin_sw = -1, int counts_per_detent = 4);
  bool begin(DebugCallback debug_callback = nullptr);
  long getValue();
  static RotaryEncoder<ID>* instance;
  static void handleEncoderISR();

 private:
  int pin_a;
  int pin_b;
  int pin_sw;
  int counts_per_detent;
  long _value;
  long value;
  DebugCallback debug_callback;

  int prev_a_state;
  int prev_b_state;
};

#include "RotaryEncoder.tpp"

#endif  // RotaryEncoder_h