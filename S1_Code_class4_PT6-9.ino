// ==========================================
// KODE GABUNGAN REVISI (PERTEMUAN 5, 6, & 7-9)
// ==========================================

// 1. PIN TOMBOL & DRIVER L9110S
int pinTombol = 2; 
int AIA = 5; int AIB = 6;  // Motor Kiri
int BIA = 9; int BIB = 10; // Motor Kanan

void setup() {
  // Tombol menggunakan internal pull-up (Dipencet = LOW)
  pinMode(pinTombol, INPUT_PULLUP); 
  
  // Mengatur semua pin driver sebagai OUTPUT
  pinMode(AIA, OUTPUT); pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT); pinMode(BIB, OUTPUT);
  
  // Pastikan di awal dinyalakan robot dalam posisi diam
  robotBerhenti();
}

void loop() {
  // === LOGIKA GABUNGAN IF, WHILE, & BREAK ===
  
  // 1. IF: JIKA tombol dipencet (LOW), langsung masuk ke mode dansa otomatis!
  if (digitalRead(pinTombol) == LOW) {
    
    // Beri sedikit jeda agar pembacaan tombol lebih stabil saat jari dilepas
    delay(200); 
    
    // 2. WHILE: Mengunci program agar fokus menyelesaikan urutan gerakan sampai habis
    while (true) {
      
      // Langkah 1: Mundur 0,5 detik
      robotMundur();
      delay(500);
  
      // Langkah 2: Maju 2,5 detik
      robotMaju();
      delay(2500);
  
      // Langkah 3: Berhenti sebentar
      robotBerhenti();
      delay(500); // Waktu berhenti bisa disesuaikan, misal 0,5 detik
  
      // Langkah 4: Belok Kanan 0,5 detik
      robotBelokKanan();
      delay(500);
  
      // Langkah 5: Belok Kanan lagi 0,5 detik (Total U-Turn 1 detik)
      robotBelokKanan();
      delay(500);
  
      // Langkah 6: Maju 2 detik
      robotMaju();
      delay(2000);
      
      // 3. BREAK: Kunci Utama! Setelah urutan di atas selesai semua, 
      // hancurkan perulangan 'while' secara paksa agar program selesai!
      break; 
    }
    
    // Setelah berhasil BREAK (keluar dari while), robot otomatis mati permanen
    // dan kembali siaga menunggu tombol dipencet lagi di loop berikutnya.
    robotBerhenti();
  }
}

// ========================================================
// KOTAK MANTRA GERAKAN (Fungsi Buatan Sendiri)
// ========================================================

void robotMaju() {
  digitalWrite(AIA, HIGH); digitalWrite(AIB, LOW);
  digitalWrite(BIA, HIGH); digitalWrite(BIB, LOW);
}

void robotMundur() {
  digitalWrite(AIA, LOW); digitalWrite(AIB, HIGH);
  digitalWrite(BIA, LOW); digitalWrite(BIB, HIGH);
}

void robotBelokKanan() {
  digitalWrite(AIA, HIGH); digitalWrite(AIB, LOW); 
  digitalWrite(BIA, LOW);  digitalWrite(BIB, LOW); 
}

void robotBerhenti() {
  digitalWrite(AIA, LOW); digitalWrite(AIB, LOW);
  digitalWrite(BIA, LOW); digitalWrite(BIB, LOW);
}
