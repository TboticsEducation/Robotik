#define REMOTEXY_MODE__ESP32CORE_BLE

#include <BLEDevice.h>
#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "Smart_home_01"

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t const PROGMEM RemoteXY_CONF_PROGMEM[] =   
  { 255,2,0,0,0,73,0,19,0,0,0,0,31,1,106,200,1,1,4,0,
  2,31,56,44,22,0,2,26,31,31,79,78,0,79,70,70,0,2,31,123,
  44,22,0,5,26,31,31,79,78,0,79,70,70,0,129,33,41,41,12,64,
  17,76,65,77,80,85,0,129,36,108,33,12,64,21,75,73,80,65,83,0 };
  
struct {
  uint8_t switch_01; 
  uint8_t switch_02; 
  uint8_t connect_flag;  
} RemoteXY;   
#pragma pack(pop)

/////////////////////////////////////////////
// PIN DEFINISI
/////////////////////////////////////////////

#define PIN_LAMPU 2
#define PIN_KIPAS1 22
#define PIN_KIPAS2 23
#define PIN_BUZZER 19
#define PIN_TRIG 5
#define PIN_ECHO 18

long durasi;
float jarak;

/////////////////////////////////////////////

void setup() 
{
  RemoteXY_Init ();  
  
  pinMode(PIN_LAMPU, OUTPUT);
  pinMode(PIN_KIPAS1, OUTPUT);
  pinMode(PIN_KIPAS2, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  digitalWrite(PIN_LAMPU, LOW);
  digitalWrite(PIN_KIPAS1, LOW);
  digitalWrite(PIN_KIPAS2, LOW);
}

void loop() 
{ 
  // KODE KONTROL LAMPU DAN KIPAS
  RemoteXY_Handler ();   

  // Kontrol Lampu
  if (RemoteXY.switch_01 == 1) {
    digitalWrite(PIN_LAMPU, HIGH);
  } else {
    digitalWrite(PIN_LAMPU, LOW);
  }

  // Kontrol Kipas
  if (RemoteXY.switch_02 == 1) {
    digitalWrite(PIN_KIPAS1, HIGH);
    digitalWrite(PIN_KIPAS2, LOW);
  } else {
    digitalWrite(PIN_KIPAS1, LOW);
    digitalWrite(PIN_KIPAS2, LOW);
  }

  RemoteXY_delay(10);

  // KODE ULTRASONIK
  // Kirim sinyal ultrasonik
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // Baca pantulan
  durasi = pulseIn(PIN_ECHO, HIGH);

  // Hitung jarak (cm)
  jarak = durasi * 0.034 / 2;

  // Logika jarak
  if (jarak < 10) {  // Dekat
    digitalWrite(PIN_BUZZER, HIGH);
  }
  else {  // Jauh
    digitalWrite(PIN_BUZZER, LOW);
  }

  delay(500);
}
