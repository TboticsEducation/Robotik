// ==========================================
// LED RGB + Push Button
// ESP32 - Kelas 5
// ==========================================

// Pin LED RGB
const int ledMerah = 18;
const int ledHijau = 19;
const int ledBiru  = 21;

// Pin Push Button
const int tombol = 2;

// Kecepatan kedip LED
int lambat = 1000;   // 1 detik
int sedang = 500;    // 0,5 detik
int cepat = 200;     // 0,2 detik

// Menyimpan mode kecepatan
int mode = 1;

// Menyimpan waktu kedip
unsigned long waktuSebelumnya = 0;

// Status LED
bool ledNyala = false;

// Status tombol sebelumnya
bool tombolSebelumnya = HIGH;


void setup() {

  // LED sebagai OUTPUT
  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);
  pinMode(ledBiru, OUTPUT);

  // Tombol sebagai INPUT
  pinMode(tombol, INPUT_PULLUP);

}


void loop() {

  // Membaca tombol
  bool tombolSekarang = digitalRead(tombol);


  // Jika tombol baru saja ditekan
  if (tombolSebelumnya == HIGH && tombolSekarang == LOW) {

    // Ganti mode
    mode++;

    // Jika sudah mode 3, kembali ke mode 1
    if (mode > 3) {
      mode = 1;
    }

    delay(200); // Anti tombol terlalu cepat
  }


  // Simpan kondisi tombol
  tombolSebelumnya = tombolSekarang;


  // Menentukan kecepatan berdasarkan mode
  int waktuKedip;

  if (mode == 1) {
    waktuKedip = lambat;
  }
  else if (mode == 2) {
    waktuKedip = sedang;
  }
  else {
    waktuKedip = cepat;
  }


  // Mengatur waktu kedip LED
  if (millis() - waktuSebelumnya >= waktuKedip) {

    waktuSebelumnya = millis();

    // Membalik kondisi LED
    ledNyala = !ledNyala;

    if (ledNyala) {

      // LED menyala
      digitalWrite(ledMerah, HIGH);
      digitalWrite(ledHijau, HIGH);
      digitalWrite(ledBiru, HIGH);

    }
    else {

      // LED mati
      digitalWrite(ledMerah, LOW);
      digitalWrite(ledHijau, LOW);
      digitalWrite(ledBiru, LOW);

    }
  }

}
