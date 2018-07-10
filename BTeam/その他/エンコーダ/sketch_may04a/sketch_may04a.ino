void setup() {
  // put your setup code here, to run once:
  DDRD = 0;
  Serial.begin(9600);
  while (!Serial);
}
long int i = 0;
long int r = 0;
void loop() {
  // put your main code here, to run repeatedly:
  i += rec();
  if (i != r)Serial.println(i);
  r = i;
}

int rec(void) {


  static const int d[] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};
  static unsigned int p; p = (p << 2 | PIND >> 6) & 0x0f;
  return d[p];
}

