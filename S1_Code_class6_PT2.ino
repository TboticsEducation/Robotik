// =========================
// LED RGB + Push Button
// ESP32 - SD Kelas 6
// =========================

// Pin LED RGB
const int ledMerah = 18;
const int ledHijau = 19;
const int ledBiru  = 21;

// Pin Push Button
const int tombol = 2;

// Variabel warna
int warna = 0;

// Untuk mendeteksi sekali tekan
bool tombolLama = HIGH;

void setup() {
  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);
  pinMode(ledBiru, OUTPUT);

  pinMode(tombol, INPUT_PULLUP);

  matikanSemua();
}

void loop() {

  bool tombolSekarang = digitalRead(tombol);

  // Jika tombol ditekan
  if (tombolLama == HIGH && tombolSekarang == LOW) {

    warna++;

    if (warna > 3) {
      warna = 1;
    }

    matikanSemua();

    if (warna == 1) {
      digitalWrite(ledMerah, HIGH);
    }
    else if (warna == 2) {
      digitalWrite(ledHijau, HIGH);
    }
    else if (warna == 3) {
      digitalWrite(ledBiru, HIGH);
    }

    delay(200); // Mengurangi bouncing tombol
  }

  tombolLama = tombolSekarang;
}

// Fungsi mematikan semua LED
void matikanSemua() {
  digitalWrite(ledMerah, LOW);
  digitalWrite(ledHijau, LOW);
  digitalWrite(ledBiru, LOW);
}