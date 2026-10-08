#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

//====================== RGB ======================
const int pinRed = 12;
const int pinGreen = 13;
const int pinBlue = 14;

//==================== BUZZER =====================
const int pinBuzzer = 25;

//===================== MOTOR =====================
// Motor Kiri
const int motorKiri1 = 32;
const int motorKiri2 = 33;

// Motor Kanan
const int motorKanan1 = 26;
const int motorKanan2 = 27;

// Deklarasi fungsi pendukung
void stopMotor();
void setColor(int red, int green, int blue);
void maju();
void mundur();
void kanan();
void kiri();
void klakson();

void setup() {
  Serial.begin(9600);
  SerialBT.begin("Tbot_Kelas5");

  // Konfigurasi PIN sebagai OUTPUT
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(motorKiri1, OUTPUT);
  pinMode(motorKiri2, OUTPUT);
  pinMode(motorKanan1, OUTPUT);
  pinMode(motorKanan2, OUTPUT);

  stopMotor();            // Pastikan robot diam saat awal dinyalakan
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
    else if (command.indexOf("maju") >= 0) {
      maju();
      SerialBT.println("Robot Maju");
    }
    else if (command.indexOf("mundur") >= 0) {
      mundur();
      SerialBT.println("Robot Mundur");
    }
    else if (command.indexOf("kanan") >= 0) {
      kanan();
      SerialBT.println("Belok Kanan");
    }
    else if (command.indexOf("kiri") >= 0) {
      kiri();
      SerialBT.println("Belok Kiri");
    }
    else if (command.indexOf("stop") >= 0) {
      stopMotor();
      SerialBT.println("Robot Stop");
    }
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
    
    // =================================================
    // 3. FITUR SWITCH (1 Sampai 10)
    // =================================================
    else if (command.indexOf("ON1") >= 0)  { digitalWrite(pinBuzzer, HIGH); }
    else if (command.indexOf("OFF1") >= 0) { digitalWrite(pinBuzzer, LOW); }
    // else if (command.indexOf("ON2") >= 0)  { digitalWrite(pinBuzzer, HIGH); }
    // else if (command.indexOf("OFF2") >= 0) { digitalWrite(pinBuzzer, LOW); }
    // else if (command.indexOf("ON3") >= 0)  { digitalWrite(pinBuzzer, HIGH); }
    // else if (command.indexOf("OFF3") >= 0) { digitalWrite(pinBuzzer, LOW); }
    // else if (command.indexOf("ON4") >= 0)  { digitalWrite(pinBuzzer, HIGH); }
    // else if (command.indexOf("OFF4") >= 0) { digitalWrite(pinBuzzer, LOW); }
    // else if (command.indexOf("ON5") >= 0)  { digitalWrite(pinBuzzer, HIGH); }
    // else if (command.indexOf("OFF5") >= 0) { digitalWrite(pinBuzzer, LOW); }
    // else if (command.indexOf("ON6") >= 0)  { digitalWrite(pinBuzzer, HIGH); }
    // else if (command.indexOf("OFF6") >= 0) { digitalWrite(pinBuzzer, LOW); }
    // else if (command.indexOf("ON7") >= 0)  { digitalWrite(pinBuzzer, HIGH); }
    // else if (command.indexOf("OFF7") >= 0) { digitalWrite(pinBuzzer, LOW); }
    // else if (command.indexOf("ON8") >= 0)  { digitalWrite(pinBuzzer, HIGH); }
    // else if (command.indexOf("OFF8") >= 0) { digitalWrite(pinBuzzer, LOW); }
    // else if (command.indexOf("ON9") >= 0)  { digitalWrite(pinBuzzer, HIGH); }
    // else if (command.indexOf("OFF9") >= 0) { digitalWrite(pinBuzzer, LOW); }
    // else if (command.indexOf("ON10") >= 0) { digitalWrite(pinBuzzer, HIGH); }
    // else if (command.indexOf("OFF10") >= 0){ digitalWrite(pinBuzzer, LOW); }
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

void maju() {
  digitalWrite(motorKiri1, HIGH);
  digitalWrite(motorKiri2, LOW);
  digitalWrite(motorKanan1, HIGH);
  digitalWrite(motorKanan2, LOW);
}

void mundur() {
  digitalWrite(motorKiri1, LOW);
  digitalWrite(motorKiri2, HIGH);
  digitalWrite(motorKanan1, LOW);
  digitalWrite(motorKanan2, HIGH);
}

void kanan() {
  digitalWrite(motorKiri1, HIGH);
  digitalWrite(motorKiri2, LOW);
  digitalWrite(motorKanan1, LOW);
  digitalWrite(motorKanan2, HIGH);
}

void kiri() {
  digitalWrite(motorKiri1, LOW);
  digitalWrite(motorKiri2, HIGH);
  digitalWrite(motorKanan1, HIGH);
  digitalWrite(motorKanan2, LOW);
}

void stopMotor() {
  digitalWrite(motorKiri1, LOW);
  digitalWrite(motorKiri2, LOW);
  digitalWrite(motorKanan1, LOW);
  digitalWrite(motorKanan2, LOW);
}

void klakson() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(pinBuzzer, HIGH);
    delay(200);
    digitalWrite(pinBuzzer, LOW);
    delay(200);
  }
}
