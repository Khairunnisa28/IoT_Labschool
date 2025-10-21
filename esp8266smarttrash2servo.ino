  #include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 8
#define SERVO_LEFT_PIN 3   // Servo kiri
#define SERVO_RIGHT_PIN 5  // Servo kanan

Servo servoLeft;
Servo servoRight;

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  servoLeft.attach(SERVO_LEFT_PIN);
  servoRight.attach(SERVO_RIGHT_PIN);

  // posisi awal tutup
  servoLeft.write(0);     // kiri posisi tutup
  servoRight.write(180);  // kanan posisi tutup (kebalikan)
  delay(1000);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Smart Trash Bin 2-Servo (Flip) Started...");
}

void loop() {
  // Kirim pulsa ultrasonik
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Hitung jarak
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // konversi ke cm

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Jika tangan dekat, buka tutup
  if (distance > 0 && distance < 15) {
    servoLeft.write(90);    // buka kiri
    servoRight.write(90);   // buka kanan (arah berlawanan)
    delay(3000);            // tunggu 3 detik
    servoLeft.write(0);     // tutup kiri
    servoRight.write(180);  // tutup kanan
  }

  delay(200); // delay pembacaan
}
