# UMOZ 🚀

An ultra-lightweight, high-performance multitasking framework and micro-RTOS designed for Arduino. UMOZ maximizes CPU efficiency by eliminating blocking delays, introducing independent macro-based timers, an advanced background task scheduler, and real-time CPU load profiling.

---

## ✨ Features

* **Micro-RTOS Task Scheduler:** Register background tasks using function pointers without dynamic memory allocation (RAM safe).
* **Independent Macro Timers (`UMOZ_EVERY`):** Create non-blocking independent intervals easily on any line using token-pasting macro expansions.
* **Real-time CPU Profiling:** Monitor actual CPU load percentage dynamically via free idle-loop calculation.
* **Turbo ADC Speed:** Injects hardware register tweaks to speed up analog readings by up to 8x on supported AVR boards.
* **Direct Port Manipulation:** High-speed `toggle()` routine that executes in a single clock cycle on AVR microcontrollers.
* **Zero-Overhead Smoothing:** Built-in Exponential Moving Average (EMA) filter for analog inputs to keep the loop fluid and non-blocking.
* **Hardware Switch Debouncing:** Built-in non-blocking button press stabilization.

---

## 📦 Installation

1. Download this repository as a `.ZIP` file.
2. Open your Arduino IDE.
3. Go to **Sketch** -> **Include Library** -> **Add .ZIP Library...**
4. Select the downloaded `UMOZ.zip` file.

---

## 🛠️ Quick Start & Usage

Here is a full demonstration of how UMOZ simplifies multi-tasking without messy bracket configurations or blocking delays:

```cpp
#include <UMOZ.h>

const uint8_t LED_PIN = 13;
const uint8_t BUTTON_PIN = 2;
const uint8_t SENSOR_PIN = A0;

// --- Background Task 1: Read and Filter Analog Sensor ---
void readSensorTask() {
  int filteredValue = tool.smoothRead(SENSOR_PIN);
  int percentage = tool.toPercentage(filteredValue, 0, 1023);
  
  Serial.print(F("[Task 1] Sensor Value: "));
  Serial.print(filteredValue);
  Serial.print(F(" | Percentage: "));
  Serial.print(percentage);
  Serial.println(F("%"));
}

// --- Background Task 2: Monitor System CPU Load ---
void monitorCPUTask() {
  int cpuLoad = tool.getCPUUsage();
  if (cpuLoad != -1) {
    Serial.print(F("[Task 2] Real-time CPU Usage: "));
    Serial.print(cpuLoad);
    Serial.println(F("%"));
  }
}

UMOZ_START()
  Serial.begin(9600);
  
  // Initialize Hardware Components
  tool.begin(LED_PIN);
  pinMode(BUTTON_PIN, INPUT);

  // Register Background Tasks to the Scheduler (Function, Interval in ms)
  tool.addTask(readSensorTask, 500);  // Runs every 500ms
  tool.addTask(monitorCPUTask, 2000); // Runs every 2000ms

UMOZ_RUN()
  // 1. Independent Multi-Timer (Flashes LED every 1000ms)
  UMOZ_EVERY_MS(1000) {
    tool.toggle(LED_PIN);
    Serial.println(F("[Timer] LED Toggled via UMOZ_EVERY_MS"));
  }

  // 2. High-Frequency independent Timer (Runs at 1Hz)
  UMOZ_EVERY_HZ(1) {
    Serial.println(F("[Timer] Heartbeat ticking at 1 Hz..."));
  }

  // 3. Non-blocking Hardware Debounced Button Press Detection
  if (tool.isButtonPressed(BUTTON_PIN)) {
    Serial.println(F("[Event] Button pressed! (Hardware Debounced)"));
  }

UMOZ_END
