#include "BluetoothSerial.h"
#include <ESP32Servo.h>
#include <SPI.h>
#include <MFRC522.h>

BluetoothSerial SerialBT;
Servo palangServo;

// Definisi PIN RFID
#define SS_PIN  5 //sda
#define RST_PIN 22
MFRC522 rfid(SS_PIN, RST_PIN);

// Definisi PIN Komponen Lain
const int pinServo  = 13;
const int pinBuzzer = 12;
const int pinMerah  = 26;
const int pinHijau  = 27;
const int pinBiru   = 25;

// VARIABEL KONTROL MODE
bool modeDarurat = false; 

// P10: UID KARTU YANG TERDAFTAR (Siswa akan mengganti bagian ini dengan UID mereka)
String kartuTerdaftar = "a3 b1 c2 d4"; 

void setup() {
  Serial.begin(115200);
  
  // Mengaktifkan Bluetooth
  SerialBT.begin("Smart_Parking_Gate"); 
  Serial.println("Sistem Siap! Sambungkan ke 'Smart_Parking_Gate'");

  // Inisialisasi RFID
  SPI.begin();
  rfid.PCD_Init();

  // Inisialisasi Servo
  palangServo.attach(pinServo);
  palangServo.write(0); // Posisi awal menutup

  // Inisialisasi Output
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinMerah, OUTPUT);
  pinMode(pinHijau, OUTPUT);
  pinMode(pinBiru, OUTPUT);

  // Kondisi awal (Standby): Lampu Biru selalu menyala sesuai instruksi
  aturLampu(LOW, LOW, HIGH); 
}

void loop() {
  // ---- CEK DATA BLUETOOTH (P4-P7 + FITUR DARURAT P10) ----
  if (SerialBT.available()) {
    String perintah = SerialBT.readStringUntil('\n');
    perintah.trim();

    // 1. Logika Manual dari P4-P7 (Tetap dipertahankan)
    if (!modeDarurat) {
      if (perintah == "buka") {
        palangServo.write(90);
        SerialBT.println("Palang Terbuka!");
      } 
      else if (perintah == "tutup") {
        palangServo.write(0);
        SerialBT.println("Palang Tertutup!");
      } 
      else if (perintah == "nyala-merah") {
        aturLampu(HIGH, LOW, LOW); SerialBT.println("merah nyala");
      } 
      else if (perintah == "nyala-hijau") {
        aturLampu(LOW, HIGH, LOW); SerialBT.println("hijau nyala");
      } 
      else if (perintah == "nyala-biru") {
        aturLampu(LOW, LOW, HIGH); SerialBT.println("biru nyala");
      }
    }

    // 2. FITUR LOGIKA MODE DARURAT (P10)
    if (perintah == "darurat") {
      modeDarurat = true;
      SerialBT.println("Sistem Masuk Mode Darurat! RFID Dinonaktifkan.");
    } 
    else if (perintah == "darurat-buka" && modeDarurat) {
      palangServo.write(90);
      aturLampu(LOW, HIGH, LOW); // LED Hijau Menyala
      digitalWrite(pinBuzzer, HIGH);
      delay(1000);               // Durasi 1 Detik
      digitalWrite(pinBuzzer, LOW);
      // Kembali ke lampu standby biru setelah aksi selesai
      aturLampu(LOW, LOW, HIGH); 
      SerialBT.println("darurat buka gate berhasil");
    } 
    else if (perintah == "darurat-tutup" && modeDarurat) {
      palangServo.write(0);
      aturLampu(HIGH, LOW, LOW); // LED Merah Menyala
      digitalWrite(pinBuzzer, HIGH);
      delay(1000);               // Durasi 1 Detik
      digitalWrite(pinBuzzer, LOW);
      // Kembali ke lampu standby biru setelah aksi selesai
      aturLampu(LOW, LOW, HIGH); 
      SerialBT.println("darurat tutup berhasil");
    } 
    else if (perintah == "keluar-darurat") {
      modeDarurat = false;
      aturLampu(LOW, LOW, HIGH); // Standby Biru
      SerialBT.println("masuk ke sistem normal dengan rfid");
    }
  }

  // ---- LOGIKA UTAMA RFID (JIKA TIDAK SEDANG MODE DARURAT) ----
  if (modeDarurat) {
    return; // Jika dalam mode darurat, program di bawah (RFID) dilewati/stop looping
  }

  // Cek apakah ada kartu baru didekatkan
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return; 
  }

  // P9: Membaca dan Menyusun teks UID Kartu
  String uidKartu = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidKartu += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    uidKartu += String(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) uidKartu += " ";
  }

  // P9: Kirim Feedback UID ke Terminal HP Anak
  SerialBT.println("UID Kartu Anda: " + uidKartu); 

  // P10: Logika Buka Otomatis via RFID
  if (uidKartu == kartuTerdaftar) {
    SerialBT.println("Akses Diterima! Membuka Palang...");
    
    // Indikator Sukses
    aturLampu(LOW, HIGH, LOW); // LED Hijau
    digitalWrite(pinBuzzer, HIGH); delay(200); digitalWrite(pinBuzzer, LOW);
    
    palangServo.write(90);     // Palang Terbuka
    delay(4000);               // Tunggu 4 detik agar mobil lewat
    
    palangServo.write(0);      // Palang Menutup Kembali
    aturLampu(LOW, LOW, HIGH); // Kembali ke Standby Biru
  } else {
    // Jika kartu tidak terdaftar
    SerialBT.println("Akses Ditolak! Kartu Tidak Dikenal.");
    aturLampu(HIGH, LOW, LOW); // LED Merah berkedip peringatan
    digitalWrite(pinBuzzer, HIGH); delay(1000); digitalWrite(pinBuzzer, LOW);
    aturLampu(LOW, LOW, HIGH); // Kembali ke Standby Biru
  }

  rfid.PICC_HaltA();
}

// Sub-fungsi pembantu untuk mengatur warna RGB secara ringkas
void aturLampu(int r, int g, int b) {
  digitalWrite(pinMerah, r);
  digitalWrite(pinHijau, g);
  digitalWrite(pinBiru, b);
}
