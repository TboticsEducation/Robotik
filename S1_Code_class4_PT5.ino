// Pin LED RGB
int merah = 13;
int hijau = 12;
int biru = 11;

void setup() {
  pinMode(merah, OUTPUT);
  pinMode(hijau, OUTPUT);
  pinMode(biru, OUTPUT);
}

void loop() {

  // 🔴 Menyalakan warna merah
  digitalWrite(merah, HIGH);
  digitalWrite(hijau, LOW);
  digitalWrite(biru, LOW);
  delay(1000);

  // 🟢 Menyalakan warna hijau
  digitalWrite(merah, LOW);
  digitalWrite(hijau, HIGH);
  digitalWrite(biru, LOW);
  delay(1000);

  // 🔵 Menyalakan warna biru
  digitalWrite(merah, LOW);
  digitalWrite(hijau, LOW);
  digitalWrite(biru, HIGH);
  delay(1000);
}
