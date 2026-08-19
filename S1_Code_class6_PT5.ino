// ==========================================
// LED RGB + Push Button + Buzzer + Servo
// ESP32 - SD Kelas 6
// ==========================================

#include <ESP32Servo.h>

// ==========================================
// PIN LED RGB
// ==========================================
const int ledMerah = 18;
const int ledHijau = 19;
const int ledBiru  = 21;

// ==========================================
// PIN PUSH BUTTON
// ==========================================
const int tombol = 2;

// ==========================================
// PIN BUZZER
// ==========================================
const int buzzer = 4;

// ==========================================
// PIN SERVO
// ==========================================
const int pinServo = 13;

Servo servo;


// ==========================================
// PARAMETER SERVO
// Ubah angka di sini
// ==========================================

int sudut1 = 0;       // Posisi pertama
int sudut2 = 90;      // Posisi kedua
int sudut3 = 180;     // Posisi ketiga
int sudut4 = 0;     // Posisi keempat

int waktuTunggu = 1000;   // Waktu tunggu setelah sampai posisi
                           // 1000 = 1 detik

int kecepatanServo = 15;  // Semakin besar = semakin lambat
                           // Semakin kecil = semakin cepat


// ==========================================
// VARIABEL LED
// ==========================================

int warna = 0;

// Untuk mendeteksi sekali tekan
bool tombolLama = HIGH;


// ==========================================
// VARIABEL BUZZER
// ==========================================

unsigned long waktuBuzzer = 0;
bool statusBuzzer = LOW;


// ==========================================
// SETUP
// ==========================================

void setup() {

  // Mengatur LED sebagai OUTPUT
  pinMode(ledMerah, OUTPUT);
  pinMode(ledHijau, OUTPUT);
  pinMode(ledBiru, OUTPUT);

  // Mengatur tombol
  pinMode(tombol, INPUT_PULLUP);

  // Mengatur buzzer
  pinMode(buzzer, OUTPUT);

  // Menghubungkan servo ke pin 13
  servo.attach(pinServo);

  // Servo mulai dari posisi pertama
  servo.write(sudut1);

  // Mematikan semua LED
  matikanSemua();
}


// ==========================================
// LOOP
// ==========================================

void loop() {

  // ========================================
  // BUZZER BUNYI TERUS
  // ========================================

  if (millis() - waktuBuzzer >= 200) {

    waktuBuzzer = millis();

    // Mengubah buzzer ON dan OFF
    statusBuzzer = !statusBuzzer;

    digitalWrite(buzzer, statusBuzzer);
  }


  // ========================================
  // PUSH BUTTON
  // ========================================

  bool tombolSekarang = digitalRead(tombol);

  // Jika tombol baru saja ditekan
  if (tombolLama == HIGH && tombolSekarang == LOW) {

    // Pindah ke warna berikutnya
    warna++;

    // Jika sudah warna ke-3,
    // kembali ke warna pertama
    if (warna > 3) {
      warna = 1;
    }

    // Matikan semua LED
    matikanSemua();

    // ----------------------------
    // WARNA 1 = MERAH
    // ----------------------------

    if (warna == 1) {
      digitalWrite(ledMerah, HIGH);
    }

    // ----------------------------
    // WARNA 2 = HIJAU
    // ----------------------------

    else if (warna == 2) {
      digitalWrite(ledHijau, HIGH);
    }

    // ----------------------------
    // WARNA 3 = BIRU
    // ----------------------------

    else if (warna == 3) {
      digitalWrite(ledBiru, HIGH);
    }

    // Anti bouncing tombol
    delay(200);
  }

  // Menyimpan kondisi tombol
  tombolLama = tombolSekarang;


  // ========================================
  // SERVO BERGERAK SMOOTH
  // ========================================

  // Servo ke sudut pertama
  gerakSmooth(sudut1);
  delay(waktuTunggu);

  // Servo ke sudut kedua
  gerakSmooth(sudut2);
  delay(waktuTunggu);

  // Servo ke sudut ketiga
  gerakSmooth(sudut3);
  delay(waktuTunggu);

  // Tambahkan lagi fungsi program gerakan sudut keempat disini

}


// ==========================================
// FUNGSI SERVO BERGERAK SMOOTH
// ==========================================

void gerakSmooth(int tujuan) {

  // Membaca posisi servo sekarang
  int posisiSekarang = servo.read();

  // Jika tujuan lebih besar
  if (tujuan > posisiSekarang) {

    for (int posisi = posisiSekarang; posisi <= tujuan; posisi++) {

      servo.write(posisi);

      delay(kecepatanServo);
    }
  }

  // Jika tujuan lebih kecil
  else {

    for (int posisi = posisiSekarang; posisi >= tujuan; posisi--) {

      servo.write(posisi);

      delay(kecepatanServo);
    }
  }
}


// ==========================================
// FUNGSI MEMATIKAN SEMUA LED
// ==========================================

void matikanSemua() {

  digitalWrite(ledMerah, LOW);
  digitalWrite(ledHijau, LOW);
  digitalWrite(ledBiru, LOW);
}
