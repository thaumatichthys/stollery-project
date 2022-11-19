#include "DisplayDriver.hpp"


void DisplayDriver::Init() {
  for (int i = 0; i < sizeof(anodes); i++) {
    pinMode(anodes[i], OUTPUT);
    display_buffer[i] = 0;
  }
  for (int i = 0; i < sizeof(cathodes); i++) {
    pinMode(cathodes[i], OUTPUT);
    this->WritePin(cathodes[i], HIGH);
  }
}

void DisplayDriver::WritePin(uint8_t pin, bool value) {
  digitalWrite(pin, value); // replace digitalWrite with port register manipulation
}

void DisplayDriver::WriteSegment(uint8_t segment, bool value) {
  for (int i = 0; i < 8; i++) {
    this->WritePin(cathodes[i], HIGH);
  }
  this->WritePin(cathodes[segment], value);
}

void DisplayDriver::UpdateMultiplex() {
  WritePin(anodes[0], LOW);
  WritePin(anodes[1], LOW);
  WritePin(anodes[2], LOW);
  WritePin(anodes[3], LOW);
  for (int i = 0; i < 4; i++) {
    WritePin(anodes[i], ((bool) (digits[this->display_buffer[i]] & ((uint8_t) 1 << (7 - this->multiplex_state)))));
    this->WriteSegment(multiplex_state, LOW);
  }
  this->multiplex_state++;
  if (this->multiplex_state > 7) this->multiplex_state = 0;
}

void DisplayDriver::WriteNumber(uint16_t number) {
  this->display_buffer[3] = (number % 10);
  this->display_buffer[2] = (number % 100) / 10;
  this->display_buffer[1] = (number % 1000) / 100;
  this->display_buffer[0] = (number % 10000) / 1000;
}

void DisplayDriver::WriteDigit(uint8_t number, uint8_t digit) {
  this->display_buffer[digit] = number;
}
