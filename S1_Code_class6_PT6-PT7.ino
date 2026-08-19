#include "BluetoothSerial.h"
#include <ESP32Servo.h>

// Inisialisasi Bluetooth dan Servo
BluetoothSerial SerialBT;
Servo palangServo;

// Definisi PIN Komponen
const int pinServo  = 13;
const int pinMerah  = 26;
const int pinHijau  = 27;
const int pinBiru   = 25;

void setup() {
  Serial.begin(115200);
  
  // Mengaktifkan Bluetooth ESP32 untuk Kelas 6 Sesi Servo-RGB
  SerialBT.begin("Robot_Servo_IoT"); 
  Serial.println("Bluetooth siap! Sambungkan HP ke 'Robot_Servo_IoT'");

  // Menghubungkan Servo ke Pin 13
  palangServo.attach(pinServo);
  palangServo.write(0); // Posisi awal menutup (0 derajat)

  // Mengatur Pin RGB sebagai Output Digital
  pinMode(pinMerah, OUTPUT);
  pinMode(pinHijau, OUTPUT);
  pinMode(pinBiru, OUTPUT);

  // Memastikan semua lampu mati di awal
  digitalWrite(pinMerah, LOW);
  digitalWrite(pinHijau, LOW);
  digitalWrite(pinBiru, LOW);
}

void loop() {
  // Mengecek apakah ada data/perintah masuk dari aplikasi terminal HP siswa
  if (SerialBT.available()) {
    // Membaca perintah teks hingga tanda enter (\n)
    String perintah = SerialBT.readStringUntil('\n');
    perintah.trim(); // Membersihkan spasi atau karakter enter tak terlihat

    // ---- LOGIKA KENDALI SERVO (P5 - P7) ----
    if (perintah == "buka") {
      palangServo.write(90); // Servo bergerak ke 90 derajat
      SerialBT.println("Palang Terbuka!"); // Kirim feedback ke layar HP
      Serial.println("Perintah: Buka -> Servo 90 derajat");
    } 
    else if (perintah == "tutup") {
      palangServo.write(0);  // Servo kembali ke 0 derajat
      SerialBT.println("Palang Tertutup!"); // Kirim feedback ke layar HP
      Serial.println("Perintah: Tutup -> Servo 0 derajat");
    }

    // ---- LOGIKA KENDALI LED RGB (P5 - P7) ----
    else if (perintah == "nyala-merah") {
      digitalWrite(pinMerah, HIGH);
      digitalWrite(pinHijau, LOW);
      digitalWrite(pinBiru, LOW);
      SerialBT.println("merah nyala"); // Feedback sesuai instruksi Bapak
    } 
    else if (perintah == "nyala-hijau") {
      digitalWrite(pinMerah, LOW);
      digitalWrite(pinHijau, HIGH);
      digitalWrite(pinBiru, LOW);
      SerialBT.println("hijau nyala"); // Feedback sesuai instruksi Bapak
    } 
    else if (perintah == "nyala-biru") {
      digitalWrite(pinMerah, LOW);
      digitalWrite(pinHijau, LOW);
      digitalWrite(pinBiru, HIGH);
      SerialBT.println("biru nyala"); // Feedback sesuai instruksi Bapak
    }
    else if (perintah == "mati-lampu") {
      digitalWrite(pinMerah, LOW);
      digitalWrite(pinHijau, LOW);
      digitalWrite(pinBiru, LOW);
      SerialBT.println("Semua lampu mati");
    }
  }
}
