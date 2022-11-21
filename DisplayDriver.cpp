#include "DisplayDriver.hpp"


void DisplayDriver::Init(uint8_t _anodes[], uint8_t _cathodes[]) {
  // anodes is sorted from left to right, cathodes is sorted A to G, then the decimal point.
  for (int i = 0; i < sizeof(anodes); i++) {
    pinMode(_anodes[i], OUTPUT);
    display_buffer[i] = 0;
  }
  for (int i = 0; i < sizeof(cathodes); i++) {
    pinMode(_cathodes[i], OUTPUT);
    this->WritePin(_cathodes[i], HIGH);
  }
}

void DisplayDriver::WritePin(uint8_t pin, bool value) { // around 17 times faster than digitalWrite (on average)
  // note that this is not portable across different chips (ie this only works for ATMega328P chips and others with the same pin/port layout)
  uint8_t mask = (uint8_t) 1 << (pin % 8);
  if (pin <= 7) {
    if (value)
      PORTD |= (uint8_t) 1 << pin;
    else
      PORTD &= ~((uint8_t) 1 << pin);
  }
  else {
    if (value)
      PORTB |= (uint8_t) 1 << (pin - 8);
    else
      PORTB &= ~((uint8_t) 1 << (pin - 8));
  }
}

void DisplayDriver::WriteSegment(uint8_t segment, bool value) {
  for (int i = 0; i < 8; i++) {
    this->WritePin(cathodes[i], HIGH);
  }
  this->WritePin(cathodes[segment], value);
}

void DisplayDriver::Multiplex(uint8_t mask[]) {
  WritePin(anodes[0], LOW);
  WritePin(anodes[1], LOW);
  WritePin(anodes[2], LOW);
  WritePin(anodes[3], LOW);
  if (!this->enabled)
    return;
  for (int i = 0; i < 4; i++) {
    uint8_t digit_mask = mask[i] | (this->dot_state ? 1U : 0);
    WritePin(anodes[i], ((bool) (digit_mask & ((uint8_t) 1 << (7 - this->multiplex_state)))));
    this->WriteSegment(multiplex_state, LOW);
  }
  this->multiplex_state++;
  if (this->multiplex_state > 7) this->multiplex_state = 0;
}

void DisplayDriver::UpdateMultiplex() {
  uint8_t masks[4] = {
    digits[this->display_buffer[0]],
    digits[this->display_buffer[1]],
    digits[this->display_buffer[2]],
    digits[this->display_buffer[3]],
  };
  
  Multiplex(masks);
}

void DisplayDriver::WriteNumber(uint16_t number) {
  this->display_buffer[3] = (number % 10);
  this->display_buffer[2] = (number % 100) / 10;
  this->display_buffer[1] = (number % 1000) / 100;
  this->display_buffer[0] = (number % 10000) / 1000;
}

void DisplayDriver::WriteSeconds(uint16_t n_seconds) {
  uint8_t _seconds = (n_seconds % 60);
  uint8_t _minutes = (n_seconds - _seconds) / 60;
  this->display_buffer[3] = (_seconds % 10);
  this->display_buffer[2] = (_seconds % 100) / 10;
  this->display_buffer[1] = (_minutes % 10);
  this->display_buffer[0] = (_minutes % 100) / 10;
}

void DisplayDriver::WriteDigit(uint8_t number, uint8_t digit) {
  this->display_buffer[digit] = number;
}

void DisplayDriver::WriteLOL(bool pos) {
  if (pos) {
    this->display_buffer[0] = 10;
    this->display_buffer[1] = 0;
    this->display_buffer[2] = 10;
    this->display_buffer[3] = 11;
  }
  else {
    this->display_buffer[0] = 11;
    this->display_buffer[1] = 10;
    this->display_buffer[2] = 0;
    this->display_buffer[3] = 10;
  }
}
