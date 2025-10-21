#define TRIG D5
#define ECHO D6
#define RELAY D1

const int DISTANCE_LIMIT = 15;        // Jarak tangan (cm)
const unsigned long HOLD_TIME = 1500; // Pompa minimal nyala 2 detik

bool pumpOn = false;
unsigned long lastOn = 0;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW); // pompa mati di awal
  Serial.println("Wastafel otomatis siap...");
}

void loop() {
  // --- Hitung jarak tangan ---
  digitalWrite(TRIG, LOW); delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  Serial.print("Jarak: "); Serial.print(distance); Serial.println(" cm");

  unsigned long now = millis();

  // --- Logika pompa ---
  if (distance > 0 && distance < DISTANCE_LIMIT) {
    pumpOn = true;
    lastOn = now;
  } else if (pumpOn && (now - lastOn > HOLD_TIME)) {
    pumpOn = false;
  }

  digitalWrite(RELAY, pumpOn ? HIGH : LOW);
  delay(200);
}
