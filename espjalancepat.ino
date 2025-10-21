#define LDR_PIN A0
#define TRIG_PIN D7
#define ECHO_PIN D8

int leds[] = {D1, D2, D3, D4, D5, D6};
int numLeds = 6;

long duration;
int distance;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  for (int i = 0; i < numLeds; i++) pinMode(leds[i], OUTPUT);
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  int threshold = 500;

  // Baca jarak 3x lalu rata-rata
  long total = 0;
  for (int i = 0; i < 3; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms
    total += duration * 0.034 / 2;
  }
  distance = total / 3;

  Serial.print("LDR: "); Serial.print(ldrValue);
  Serial.print(" | Jarak: "); Serial.print(distance); Serial.println(" cm");

  if (ldrValue < threshold) {
    for (int i = 0; i < numLeds; i++) digitalWrite(leds[i], LOW);
  } else {
    if (distance > 0 && distance < 8) {
      for (int i = 0; i < numLeds; i++) digitalWrite(leds[i], HIGH);
      delay(500);  // nyala sebentar lalu baca lagi
    } else {
      for (int i = 0; i < numLeds; i++) digitalWrite(leds[i], LOW);
    }
  }

  delay(50); // baca 20x per detik
}
