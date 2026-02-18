//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>

#define REMOTEXY_BLUETOOTH_NAME "RemoteXY"

#include <RemoteXY.h>

// RemoteXY GUI configuration
#pragma pack(push, 1)
uint8_t const PROGMEM RemoteXY_CONF_PROGMEM[] =
{ 255,4,0,0,0,53,0,19,0,0,0,0,31,1,106,200,1,1,4,0,
  1,41,68,24,24,0,2,31,70,0,
  1,41,111,24,24,0,2,31,66,0,
  1,63,89,24,24,0,2,31,82,0,
  1,18,90,24,24,0,2,31,76,0 };

// Struktur tombol RemoteXY
struct {
  uint8_t button_01;
  uint8_t button_02;
  uint8_t button_03;
  uint8_t button_04;
  uint8_t connect_flag;
} RemoteXY;
#pragma pack(pop)

//////////////////////////////////////////////
//        Pin Motor Driver L9110            //
//////////////////////////////////////////////

// Motor Kiri
#define LEFT_IA   26
#define LEFT_IB   27

// Motor Kanan
#define RIGHT_IA  32
#define RIGHT_IB  33

//////////////////////////////////////////////
//        Fungsi Gerakan Motor              //
//////////////////////////////////////////////

void stopMotor() {
  digitalWrite(LEFT_IA, LOW);
  digitalWrite(LEFT_IB, LOW);
  digitalWrite(RIGHT_IA, LOW);
  digitalWrite(RIGHT_IB, LOW);
}

void maju() {
  digitalWrite(LEFT_IA, HIGH);
  digitalWrite(LEFT_IB, LOW);

  digitalWrite(RIGHT_IA, HIGH);
  digitalWrite(RIGHT_IB, LOW);
}

void mundur() {
  digitalWrite(LEFT_IA, LOW);
  digitalWrite(LEFT_IB, HIGH);

  digitalWrite(RIGHT_IA, LOW);
  digitalWrite(RIGHT_IB, HIGH);
}

void kanan() {
  // kiri maju, kanan stop
  digitalWrite(LEFT_IA, HIGH);
  digitalWrite(LEFT_IB, LOW);

  digitalWrite(RIGHT_IA, LOW);
  digitalWrite(RIGHT_IB, HIGH);
}

void kiri() {
  // kanan maju, kiri stop
  digitalWrite(LEFT_IA, LOW);
  digitalWrite(LEFT_IB, HIGH);

  digitalWrite(RIGHT_IA, HIGH);
  digitalWrite(RIGHT_IB, LOW);
}

//////////////////////////////////////////////
//                Setup                    //
//////////////////////////////////////////////

void setup() {
  RemoteXY_Init();

  pinMode(LEFT_IA, OUTPUT);
  pinMode(LEFT_IB, OUTPUT);
  pinMode(RIGHT_IA, OUTPUT);
  pinMode(RIGHT_IB, OUTPUT);

  stopMotor();
}

//////////////////////////////////////////////
//                Loop                     //
//////////////////////////////////////////////

void loop() {
  RemoteXYEngine.handler();

  if (RemoteXY.button_01 == 1) {
    maju();
  }
  else if (RemoteXY.button_02 == 1) {
    mundur();
  }
  else if (RemoteXY.button_03 == 1) {
    kanan();
  }
  else if (RemoteXY.button_04 == 1) {
    kiri();
  }
  else {
    stopMotor();
  }

  RemoteXYEngine.delay(20);
}
