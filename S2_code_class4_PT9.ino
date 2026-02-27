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
  digitalWrite(kiri1, HIGH);
  digitalWrite(kiri2, LOW);
  digitalWrite(kanan1, HIGH);
  digitalWrite(kanan2, LOW);
}

void berhenti() {
  digitalWrite(kiri1, LOW);
  digitalWrite(kiri2, LOW);
  digitalWrite(kanan1, LOW);
  digitalWrite(kanan2, LOW);
}

void mundur() {
  digitalWrite(kiri1, LOW);  
  digitalWrite(kiri2, HIGH);
  digitalWrite(kanan1, LOW); 
  digitalWrite(kanan2, HIGH);
}

void putarBalik() {
  digitalWrite(kiri1, HIGH);  
  digitalWrite(kiri2, LOW);
  digitalWrite(kanan1, LOW);   
  digitalWrite(kanan2, HIGH);
}
