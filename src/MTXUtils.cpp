#include "MTXUtils.h"

int MTXUtils::smoothRead(uint8_t analogPin, int &smoothedReference) {
  int newRead = analogRead(analogPin);
  smoothedReference = (smoothedReference * 7 + newRead) >> 3;
  return smoothedReference;
}

bool MTXUtils::isButtonPressed(uint8_t buttonPin, uint32_t &lastDebounceTime) {
  if (digitalRead(buttonPin) == HIGH) {
    if (millis() - lastDebounceTime >= 50) {
      lastDebounceTime = millis();
      return true;
    }
  }
  return false;
}

bool MTXUtils::isButtonPressed(uint8_t buttonPin) {
  static uint32_t defaultDebounce = 0;
  return isButtonPressed(buttonPin, defaultDebounce);
}
