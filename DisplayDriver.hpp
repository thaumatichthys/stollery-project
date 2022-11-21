#include "Arduino.h"



/*              |-|                                      |-|
 *              | |                                      | | 
 *              | |  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  ^  | |
 *              | |------------ Top down view -----------| |
 *  Pin number  |    1  2  3  4  5  6  7  8  9  10 11 12   |
 *  Pin type    |    K  K     K  K  A  K  A  A  K  K  A    |
 *  Pin value   |    E  D     C  G  4  B  3  2  F  A  1    |
 *  
 */

// default values
const uint8_t anodes[] = { // sorted from the left
  2, 3, 4, 5
};
// default values
const uint8_t cathodes[] = { // sorted alphabetically
  6, 7, 8, 9, 10, 11, 12, 13
};

const uint8_t digits[] = { // digit "ROM" 
  0b11111100, // '0'
  0b01100000, // '1'
  0b11011010, // '2'
  0b11110010, // '3'
  0b01100110, // '4'
  0b10110110, // '5'
  0b10111110, // '6'
  0b11100000, // '7'
  0b11111110, // '8'
  0b11110110, // '9'

  0b00011100, // 'L'
  0           // blank digit
};

class DisplayDriver {
  uint8_t display_buffer[4];
  uint8_t multiplex_state = 0;
  void WriteSegment(uint8_t segment, bool value);
  void WritePin(uint8_t pin, bool value);
  void Multiplex(uint8_t mask[]);
public:
  bool dot_state = false;
  bool enabled = true;
  void Init(uint8_t _anodes[], uint8_t _cathodes[]);
  void UpdateMultiplex();
  void WriteNumber(uint16_t number);
  void WriteSeconds(uint16_t n_seconds);
  void WriteDigit(uint8_t number, uint8_t digit);

  void WriteLOL(bool pos);
};
