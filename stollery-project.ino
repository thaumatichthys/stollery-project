#include "DisplayDriver.hpp"

DisplayDriver dp;

void setup() {
  // put your setup code here, to run once:
  dp.Init();
  Serial.begin(9600);
}

uint16_t val0 = 0;
uint8_t val = 0;
void loop() {
  // put your main code here, to run repeatedly:
  val++;
  if (val > 100) {
    dp.WriteNumber(val0);
    val0++;
    val = 0;
  }
  
  dp.UpdateMultiplex();
  delay(1);
}
