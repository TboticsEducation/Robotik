//======================================================
// KELAS 4 - WHILE & BREAK
// TOMBOL 1 = ROBOT BERJALAN
// TOMBOL 2 = ROBOT BERJALAN + RGB SIRINE
//======================================================

//--------------- PIN -----------------
const int pinTombolGerak  = 2;
const int pinTombolSirine = 3;

// Driver Motor
const int AIA = 5;
const int AIB = 6;
const int BIA = 9;
const int BIB = 10;

// RGB LED
const int pinR = 11;
const int pinG = 12;
const int pinB = 13;

//-------------------------------------

unsigned long waktuRGB = 0;
int warna = 0;

void setup()
{
  pinMode(pinTombolGerak, INPUT_PULLUP);
  pinMode(pinTombolSirine, INPUT_PULLUP);

  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);

  robotBerhenti();
  lampuMati();
}

void loop()
{
  int mode = 0;

  //==============================
  // MENUNGGU TOMBOL
  //==============================
  while (true)
  {
    if (digitalRead(pinTombolGerak) == LOW)
    {
      delay(20); // debounce

      if (digitalRead(pinTombolGerak) == LOW)
      {
        mode = 1;

        while (digitalRead(pinTombolGerak) == LOW);
        break;
      }
    }

    if (digitalRead(pinTombolSirine) == LOW)
    {
      delay(20);

      if (digitalRead(pinTombolSirine) == LOW)
      {
        mode = 2;

        while (digitalRead(pinTombolSirine) == LOW);
        break;
      }
    }
  }

  //==============================
  // PILIH MODE
  //==============================

  if (mode == 1)
  {
    jalankanRobot(false);
  }

  if (mode == 2)
  {
    jalankanRobot(true);
  }

  robotBerhenti();
  lampuMati();
}

//======================================================
// PROGRAM UTAMA ROBOT
//======================================================

void jalankanRobot(bool sirine)
{
  gerak(robotMundur, 500, sirine);

  gerak(robotMaju, 2500, sirine);

  gerak(robotBelokKanan, 500, sirine);

  gerak(robotBelokKanan, 500, sirine);

  gerak(robotMaju, 2000, sirine);
}

//======================================================
// GERAK + RGB
//======================================================

void gerak(void (*fungsiGerak)(), int waktu, bool sirine)
{
  fungsiGerak();

  unsigned long mulai = millis();

  while (millis() - mulai < waktu)
  {
    if (sirine)
    {
      updateSirine();
    }
  }
}

//======================================================
// RGB SIRINE
//======================================================

void updateSirine()
{
  if (millis() - waktuRGB >= 300)
  {
    waktuRGB = millis();

    warna++;

    if (warna > 2)
      warna = 0;

    lampuMati();

    if (warna == 0)
      digitalWrite(pinR, HIGH);

    else if (warna == 1)
      digitalWrite(pinG, HIGH);

    else
      digitalWrite(pinB, HIGH);
  }
}

//======================================================
// MOTOR
//======================================================

void robotMaju()
{
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, HIGH);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, HIGH);
}

void robotMundur()
{
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, HIGH);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, HIGH);
}

void robotBelokKanan()
{
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);
}

void robotBerhenti()
{
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);
}

//======================================================
// RGB
//======================================================

void lampuMati()
{
  digitalWrite(pinR, LOW);
  digitalWrite(pinG, LOW);
  digitalWrite(pinB, LOW);
}
