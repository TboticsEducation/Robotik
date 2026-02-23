// Sensor IR
int sensorIR = 2;

// MOTOR KIRI
int kiri1 = 3;
int kiri2 = 4;

// MOTOR KANAN
int kanan1 = 5;
int kanan2 = 6;

void setup() {
  pinMode(sensorIR, INPUT);
  pinMode(kiri1, OUTPUT);
  pinMode(kiri2, OUTPUT);
  pinMode(kanan1, OUTPUT);
  pinMode(kanan2, OUTPUT);
}

void loop() {
  int bacaSensor = digitalRead(sensorIR);

  if (bacaSensor == HIGH) {
    maju();
  } else {
    berhenti();
    delay(300);
    mundur();
    delay(600);
    putarBalik();
    delay(1800);
  }
}

void maju() {
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}

void berhenti() {
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void mundur() {
  digitalWrite(3, LOW);  
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW); 
  digitalWrite(6, HIGH);
}

void putarBalik() {
  digitalWrite(3, HIGH);  // motor kiri maju
  digitalWrite(4, LOW);

  digitalWrite(5, LOW);   // motor kanan mundur
  digitalWrite(6, HIGH);
}
