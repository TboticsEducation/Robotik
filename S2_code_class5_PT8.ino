#define TRIG 5
#define ECHO 18

#define LED_MERAH 26
#define LED_KUNING 27
#define LED_HIJAU 14

long durasi;
float jarak;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(LED_MERAH, OUTPUT);
  pinMode(LED_KUNING, OUTPUT);
  pinMode(LED_HIJAU, OUTPUT);
}

void loop() {

  // Kirim sinyal ultrasonik
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Baca pantulan
  durasi = pulseIn(ECHO, HIGH);

  // Hitung jarak (cm)
  jarak = durasi * 0.034 / 2;

  Serial.print("Jarak: ");
  Serial.println(jarak);

  // Logika jarak
  if (jarak < 10) {  // Dekat
    digitalWrite(LED_MERAH, HIGH);
    digitalWrite(LED_KUNING, LOW);
    digitalWrite(LED_HIJAU, LOW);
  }
  else if (jarak >= 10 && jarak < 20) {  // Sedang
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_KUNING, HIGH);
    digitalWrite(LED_HIJAU, LOW);
  }
  else {  // Jauh
    digitalWrite(LED_MERAH, LOW);
    digitalWrite(LED_KUNING, LOW);
    digitalWrite(LED_HIJAU, HIGH);
  }

  delay(500);
}
