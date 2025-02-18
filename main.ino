//============== MAIN CODE ==============

void setup() {
  Wire.begin();
  Serial.begin(115200);
  inisiasimode();
  pinMode(SWITCH, INPUT);
}

void loop() {
  if (digitalRead(SWITCH) == HIGH) {
    statusbutton = 1;
  } else if (digitalRead(SWITCH) == LOW) {
    statusbutton = 0;
    digitalWrite(enableMotor, LOW);
    speedA = 0, speedB = 0, speedC = 0, speedD = 0;
    Pa = 0, Pb = 0, Pc = 0, Pd = 0;
  }
  OledPrintValue();
  runkompas();
  hitungposisi();
  UART_receive();
  play();

  // ---------- BNN ( Bagian Ngedebug-Ngedebug ) -----------
  // Debug_LF_Vertikal();
  // Serial.println(yaw);
  // Serial.println(Da);
  // Debug_PosXY();
  // Debug_GridPosXY();
  // BISA_OLED();
  // Debug_GridXY();
  // Debug_LF();
  // Debug_LFs();
}
