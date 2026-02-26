const int LM35_PIN = A0;
const int ENC_A = 2;
const int ENC_B = 3;

volatile long count = 0;

unsigned long lastPrint = 0;
const unsigned long Ts_ms = 100;

void isrA() {
  bool a = digitalRead(ENC_A);
  bool b = digitalRead(ENC_B);

  if (a == b) count++;
  else        count--;
}

void setup() {
  Serial.begin(9600);

  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENC_A), isrA, CHANGE);
}

void loop() {
  int adc = analogRead(LM35_PIN);
  float volt = adc * (5.0 / 1023.0);
  float tempC = volt * 100.0;

  if (millis() - lastPrint >= Ts_ms) {
    lastPrint = millis();

    long c;
    noInterrupts();
    c = count;
    interrupts();

    Serial.print(tempC, 2);
    Serial.print(",");
    Serial.println(c);
  }
}