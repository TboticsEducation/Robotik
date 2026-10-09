#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// ================= PIN =================
const int pinRed = 12;
const int pinGreen = 13;
const int pinBlue = 14;
const int pinBuzzer = 25;

// ================= SETUP =================
void setup() {

  Serial.begin(115200);

  // Bluetooth
  SerialBT.begin("Tbot_Kelas5");

  // Output
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  // Warna awal
  setColor(0, 0, 0);
}

// ================= LOOP =================
void loop() {

  if (SerialBT.available() > 0) {

    String command = SerialBT.readString();
    command.trim();
    command.toLowerCase();

    // =========================================
    // PERINTAH WARNA
    // =========================================

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

    // =========================================
    // MATIKAN LED
    // =========================================

    else if (command == "mati") {
      setColor(0, 0, 0);
      SerialBT.println("LED MATI");
    }

    // =========================================
    // RGB PICKER
    // Format: 255000128
    // =========================================

    else if (command.length() == 9) {

      int redValue = command.substring(0, 3).toInt();
      int greenValue = command.substring(3, 6).toInt();
      int blueValue = command.substring(6, 9).toInt();

      setColor(redValue, greenValue, blueValue);

      SerialBT.println("RGB BERUBAH");
    }

    // =========================================
    // BUZZER
    // =========================================

    else if (command.indexOf("speaker") >= 0) {

      digitalWrite(pinBuzzer, HIGH);

      SerialBT.println("speaker aktif");

      delay(1000);

      digitalWrite(pinBuzzer, LOW);
    }

    // =========================================
    // SWITCH
    // =========================================

    else if (command.indexOf("ON") >= 0) {
      digitalWrite(pinBuzzer, HIGH);
    }

    else if (command.indexOf("OFF") >= 0) {
      digitalWrite(pinBuzzer, LOW);
    }
  }
}

// ================= FUNGSI RGB =================

void setColor(int red, int green, int blue) {

  analogWrite(pinRed, red);
  analogWrite(pinGreen, green);
  analogWrite(pinBlue, blue);
}
```
