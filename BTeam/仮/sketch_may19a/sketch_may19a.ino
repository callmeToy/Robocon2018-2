void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  Serial.begin(115200);
}

void loop() {
  uint8_t a = (PIND & _BV(2)) >> 2;
  uint8_t b = (PIND & _BV(3)) >> 3;
  Serial.print(a);
  Serial.print(b);
}
