#include "Arduino.h"

const uint8_t anodes[] = {
  2, 3, 4, 5
};

const uint8_t cathodes[] = {
  6, 7, 8, 9, 10, 11, 12
};

const uint8_t digits[] = {
  0b11111100,
  0b01100000,
  0b11011010,
  0b11110010,
  0b01100110,
  0b10110110,
  0b10111110,
  0b11100000,
  0b11111110,
  0b11110110
};

class DisplayDriver {
  public:
  void Init();
  void UpdateMultiplex();
  void WriteNumber(uint8_t numbers);
};
