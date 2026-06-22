#include "UMOZ.h"

UMOZ::UMOZ() {
  _previousMillisBlink = 0;
  _smoothedAnalog = 0;
  _idleCounter = 0;
  _maxIdle = 0;
  _cpuCheckMillis = 0;
  _taskCount = 0;
  _smartSleepEnabled = false;

  for(uint8_t i = 0; i < UMOZ_MAX_TASKS; i++) {
     _tasks[i].isActive = false;
  }
}

void UMOZ::begin(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void UMOZ::initLibrary() {
  #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADCSRA = (ADCSRA & 0xf8) | 0x04;
  #endif

  uint32_t startWin = millis();
  _idleCounter = 0;
  while (millis() - startWin < 50) {
    _idleCounter++;
  }
  _maxIdle = _idleCounter * 20;
  _idleCounter = 0;
  _cpuCheckMillis = millis();
}

int UMOZ::getCPUUsage() {
  uint32_t currentMillis = millis();
  if (currentMillis - _cpuCheckMillis >= 1000) {
    if (_maxIdle == 0) _maxIdle = 1;

    long usage = 100 - (((long)_idleCounter * 100) / _maxIdle);
    usage = constrain(usage, 0, 100);

    _idleCounter = 0;
    _cpuCheckMillis = currentMillis;
    return (int)usage;
  }
  return -1;
}

void UMOZ::blink(uint32_t delayTime) {
  uint32_t currentMillis = millis();
  if (currentMillis - _previousMillisBlink >= delayTime) {
    _previousMillisBlink = currentMillis;
    digitalWrite(_pin, !digitalRead(_pin));
  }
}

int UMOZ::smoothRead(uint8_t analogPin) {
  int newRead = analogRead(analogPin);
  _smoothedAnalog = (_smoothedAnalog * 7 + newRead) >> 3;
  return _smoothedAnalog;
}

bool UMOZ::isButtonPressed(uint8_t buttonPin) {
  static uint32_t defaultDebounce = 0;
  return isButtonPressed(buttonPin, defaultDebounce);
}

bool UMOZ::addTask(umoz_task_t func, uint32_t intervalMs, UMOZPriority priority) {
  if (_taskCount < UMOZ_MAX_TASKS) {
    _tasks[_taskCount].taskFunction = func;
    _tasks[_taskCount].interval = intervalMs;
    _tasks[_taskCount].lastRun = millis();
    _tasks[_taskCount].priority = static_cast<uint8_t>(priority);
    _tasks[_taskCount].isActive = true;
    _taskCount++;
    return true;
  }
  return false;
}

void UMOZ::runTasks() {
  uint32_t currentMillis = millis();
  int targetIndex = -1;
  int highestPriority = -1;
  uint32_t minTimeToNextTask = 0xFFFFFFFF;

  for (uint8_t i = 0; i < _taskCount; i++) {
    if (_tasks[i].isActive) {
      uint32_t timeElapsed = currentMillis - _tasks[i].lastRun;

      if (timeElapsed >= _tasks[i].interval) {
        if (static_cast<int>(_tasks[i].priority) > highestPriority) {
          highestPriority = static_cast<int>(_tasks[i].priority);
          targetIndex = i;
        }
      } else {
        uint32_t timeLeft = _tasks[i].interval - timeElapsed;
        if (timeLeft < minTimeToNextTask) {
          minTimeToNextTask = timeLeft;
        }
      }
    }
  }

  if (targetIndex != -1) {
    _tasks[targetIndex].taskFunction();
    _tasks[targetIndex].lastRun = millis();
  } else {
    if (_smartSleepEnabled && minTimeToNextTask > 5) {
      enterLowPowerSleep();
    }
  }
}

void UMOZ::enterLowPowerSleep() {
  #if defined(__AVR__)
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    power_adc_disable();
    power_spi_disable();
    sleep_cpu();
    sleep_disable();
    power_all_enable();
    _idleCounter += 120;
  #elif defined(ARDUINO_ARCH_ESP32)
  #endif
}
