#ifndef MTX_UTILS_H
#define MTX_UTILS_H

#include "Arduino.h"

class MTXUtils {
  public:
    template <uint8_t PIN>
    static inline void toggleFast() {
      #if defined(__AVR__)
        *portInputRegister(digitalPinToPort(PIN)) = digitalPinToBitMask(PIN);
      #else
        digitalWrite(PIN, !digitalRead(PIN));
      #endif
    }

    static inline void toggle(uint8_t pin) {
      digitalWrite(pin, !digitalRead(pin));
    }

    static inline int smoothReadFast(uint8_t analogPin, int &smoothedReference) {
      int newRead = analogRead(analogPin);
      smoothedReference = (smoothedReference * 7 + newRead) >> 3;
      return smoothedReference;
    }

    static int smoothRead(uint8_t analogPin, int &smoothedReference);
    static bool isButtonPressed(uint8_t buttonPin, uint32_t &lastDebounceTime);
    static bool isButtonPressed(uint8_t buttonPin);

    static inline int toPercentage(int rawValue, int minRaw, int maxRaw) {
      return constrain(map(rawValue, minRaw, maxRaw, 0, 100), 0, 100);
    }
};

#endif
