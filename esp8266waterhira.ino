#define SOIL_PIN A0     // Sensor kelembapan tanah
#define RELAY_PIN D1    // Relay pompa air

#define DRY 800         // Nilai saat tanah kering (sesuaikan)
#define WET 780         // Nilai saat tanah basah (sesuaikan)

void setup() {
  Serial.begin(9600);
  pinMode(SOIL_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay off di awal (aktif LOW)
}

void loop() {
  int soilValue = analogRead(SOIL_PIN);
  Serial.print("Kelembapan tanah: ");
  Serial.println(soilValue);

  if (soilValue > DRY) {
    // Tanah kering → nyalakan pompa
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Pompa ON (tanah kering)");
  } 
  else if (soilValue < WET) {
    // Tanah basah → matikan pompa
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Pompa OFF (tanah basah)");
  }       

  delay(1000);
}
