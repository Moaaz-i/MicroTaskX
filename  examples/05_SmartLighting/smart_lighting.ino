#include <MicroTaskX.h>

const uint8_t LED = 9;
const uint8_t SENSOR = A0;

void adjustLight() {
  int raw = mtx.smoothRead(SENSOR);
  int brightness = map(raw, 0, 1023, 0, 255);
  analogWrite(LED, brightness);
}

MTX_START()
  pinMode(LED, OUTPUT);
  mtx.addTask(adjustLight, 50);
MTX_RUN()
MTX_END
