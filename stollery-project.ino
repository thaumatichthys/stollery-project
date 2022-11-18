
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

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < sizeof(anodes); i++) {
    pinMode(anodes[i], OUTPUT);
  }
  for (int i = 0; i < sizeof(cathodes); i++) {
    pinMode(cathodes[i], OUTPUT);
  }

  
  Serial.begin(9600);
}

void WriteDigit(uint8_t number, uint8_t digit) {
  for (int i = 0; i < 8; i++) {
    bool val = !(bool) (digits[number] & (1U << (7 - i)));
    Serial.println(val);
    digitalWrite(cathodes[i], val);
  }
  digitalWrite(anodes[digit], HIGH);
}

uint8_t val = 0;
void loop() {
  // put your main code here, to run repeatedly:
  WriteDigit(val, 2);
  val++;
  if (val > 9) val = 0;
  delay(1000);
}
