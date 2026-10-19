#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

//====================== RGB ======================
const int pinRed = 12;
const int pinGreen = 13;
const int pinBlue = 14;

//==================== BUZZER =====================
const int pinBuzzer = 25;

// Deklarasi fungsi pendukung

void setColor(int red, int green, int blue);


void setup() {
  Serial.begin(9600);
  SerialBT.begin("kelas 5 p6-p9");

  // Konfigurasi PIN sebagai OUTPUT
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

           // Pastikan robot diam saat awal dinyalakan
  setColor(37, 166, 154); // Set warna awal RGB (Toska)
}

void loop() {
  // Jika ada data masuk dari Bluetooth HP
  if (SerialBT.available() > 0) {
    // Membaca data per baris kalimat (Mencegah data bertumpuk & merusak RGB picker)
    String command = SerialBT.readStringUntil('\n');
    command.trim(); // Membersihkan karakter enter atau spasi tak terlihat

    // JIKA DATA KOSONG, ABAIKAN PROSES DI BAWAH
    if (command.length() == 0) return;

    // =================================================
    // 1. FITUR RGB PICKER (Format 9 Digit Angka Murni)
    // =================================================
    if (command.length() == 9 && isDigit(command.charAt(0))) {
      int redValue   = command.substring(0, 3).toInt();
      int greenValue = command.substring(3, 6).toInt();
      int blueValue  = command.substring(6, 9).toInt();
      setColor(redValue, greenValue, blueValue);
    }

    // =================================================
    // 2. FITUR KONTROL MOTOR & TERMINAL
    // =================================================

    else if (command.indexOf("klakson") >= 0) {
      klakson();
      SerialBT.println("Klakson Aktif");
    }
    else if (command.indexOf("speaker") >= 0) {
      digitalWrite(pinBuzzer, HIGH);
      SerialBT.println("Speaker Aktif");
      delay(1000);
      digitalWrite(pinBuzzer, LOW);
    }
    
      if (command == "merah") {
      setColor(255, 0, 0);
      SerialBT.println("LED MERAH");
    }

    else if (command == "hijau") {
      setColor(0, 255, 0);
      SerialBT.println("LED HIJAU");
    }

    else if (command == "biru") {
      setColor(0, 0, 255);
      SerialBT.println("LED BIRU");
    }
    // =================================================
    // 3. FITUR SWITCH (1 Sampai 10)
    // =================================================
    else if (command.indexOf("ON1") >= 0)  { digitalWrite(pinBuzzer, HIGH); }
    else if (command.indexOf("OFF1") >= 0) { digitalWrite(pinBuzzer, LOW); }

  }
}

//=================================================
// FUNGSI PENDUKUNG
//=================================================
void setColor(int red, int green, int blue) {
  analogWrite(pinRed, red);
  analogWrite(pinGreen, green);
  analogWrite(pinBlue, blue);
}

void klakson() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(pinBuzzer, HIGH);
    delay(200);
    digitalWrite(pinBuzzer, LOW);
    delay(200);
  }
}
