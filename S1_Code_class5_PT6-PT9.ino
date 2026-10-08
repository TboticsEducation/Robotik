#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// PIN Komponen (Sesuai proyekmu)
const int pinRed = 12;
const int pinGreen = 13;
const int pinBlue = 14;
const int pinBuzzer = 25; // Mengontrol buzzer

void setup() {
  // Memulai Bluetooth dengan nama Tbot
  SerialBT.begin("Tbot_Kelas5");
  
  // Mengatur semua PIN sebagai OUTPUT
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  // Set warna awal (Bawaan contoh developer)
  setColor(37, 166, 154); 
}

void loop() {
  // Jika ada data masuk dari Bluetooth HP
  if (SerialBT.available() > 0) {
    // Membaca semua data yang tersedia di buffer saat itu
    String command = SerialBT.readString();
    command.trim(); // Membersihkan sisa spasi tak terlihat

    // --- 1. FITUR RGB PICKER (Format 9 Digit Angka) ---
    if (command.length() == 9) {
      int redValue = command.substring(0, 3).toInt();
      int greenValue = command.substring(3, 6).toInt();
      int blueValue = command.substring(6).toInt();
      setColor(redValue, greenValue, blueValue);
    }
    
    // --- 2. FITUR SWITCH 1 SAMPAI 10 (Menggunakan indexOf) ---
    // Jika teks di dalam kurung ditemukan di dalam variabel 'command'
    else if (command.indexOf("ON1") >= 0)  { digitalWrite(pinBuzzer, HIGH); } 
    else if (command.indexOf("OFF1") >= 0) { digitalWrite(pinBuzzer, LOW); }
    
    else if (command.indexOf("ON2") >= 0)  { digitalWrite(pinBuzzer, HIGH); } 
    else if (command.indexOf("OFF2") >= 0) { digitalWrite(pinBuzzer, LOW); }
    
    else if (command.indexOf("ON3") >= 0)  { digitalWrite(pinBuzzer, HIGH); } 
    else if (command.indexOf("OFF3") >= 0) { digitalWrite(pinBuzzer, LOW); }
    
    else if (command.indexOf("ON4") >= 0)  { digitalWrite(pinBuzzer, HIGH); } 
    else if (command.indexOf("OFF4") >= 0) { digitalWrite(pinBuzzer, LOW); }
    
    else if (command.indexOf("ON5") >= 0)  { digitalWrite(pinBuzzer, HIGH); } 
    else if (command.indexOf("OFF5") >= 0) { digitalWrite(pinBuzzer, LOW); }
    
    else if (command.indexOf("ON6") >= 0)  { digitalWrite(pinBuzzer, HIGH); } 
    else if (command.indexOf("OFF6") >= 0) { digitalWrite(pinBuzzer, LOW); }
    
    else if (command.indexOf("ON7") >= 0)  { digitalWrite(pinBuzzer, HIGH); } 
    else if (command.indexOf("OFF7") >= 0) { digitalWrite(pinBuzzer, LOW); }
    
    else if (command.indexOf("ON8") >= 0)  { digitalWrite(pinBuzzer, HIGH); } 
    else if (command.indexOf("OFF8") >= 0) { digitalWrite(pinBuzzer, LOW); }
    
    else if (command.indexOf("ON9") >= 0)  { digitalWrite(pinBuzzer, HIGH); } 
    else if (command.indexOf("OFF9") >= 0) { digitalWrite(pinBuzzer, LOW); }
    
    else if (command.indexOf("ON10") >= 0) { digitalWrite(pinBuzzer, HIGH); } 
    else if (command.indexOf("OFF10") >= 0) { digitalWrite(pinBuzzer, LOW); }
    
    // --- 3. FITUR TERMINAL ---
    else if (command.indexOf("speaker") >= 0) {
      digitalWrite(pinBuzzer, HIGH);        
      SerialBT.println("speaker aktif");    
      delay(1000);                          
      digitalWrite(pinBuzzer, LOW);         
    }
  }
}

void setColor(int red, int green, int blue) {
  analogWrite(pinRed, red);
  analogWrite(pinGreen, green);
  analogWrite(pinBlue, blue);
}
