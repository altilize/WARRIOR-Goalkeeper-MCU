// ============== Debug Motor ===============
void DebugRPM() {
  Serial.print(rpmA);
  Serial.print(" ");
  Serial.print(rpmB);
  Serial.print(" ");
  Serial.print(rpmC);
  Serial.print(" ");
  Serial.print(rpmD);
  Serial.print(" ");
  Serial.println();
}

void Debug_ValueVxy() {
  Serial.print(valuevx);
  Serial.print(" ");
  Serial.print(valuevy);
  Serial.print(" ");
  Serial.println();
}

void Debug_PosXY() {
  Serial.print("pos X = ");
  Serial.print(Xpos);
  Serial.print(" ");
  Serial.print("pos Y = ");
  Serial.print(Ypos);
  Serial.println();
}
void Debug_GridPosXY() {
  Serial.print("grid X = ");
  Serial.print(gridX);
  Serial.print(" ");
  Serial.print("pos X = ");
  Serial.print(Xpos);
  Serial.print(" ");
  Serial.print("grid Y = ");
  Serial.print(gridY);
  Serial.print(" ");
  Serial.print("pos Y = ");
  Serial.print(Ypos);

  Serial.println();
}

void Debug_GridXY() {
  Serial.print("grid X = ");
  Serial.print(gridX);
  Serial.print(" ");
  Serial.print("grid Y = ");
  Serial.print(gridY);

  Serial.println();
}

void AllMotorHIGH() {
  digitalWrite(enableMotor, HIGH);
  analogWrite(RMotor1, 100);
  analogWrite(LMotor1, 0);
  analogWrite(RMotor2, 100);
  analogWrite(LMotor2, 0);
  analogWrite(RMotor4, 100);
  analogWrite(LMotor4, 0);
  analogWrite(RMotor3, 100);
  analogWrite(LMotor3, 0);
}


// =============== Debug Line Follower =================
void Debug_LF_Vertikal() {
  float weighted_average = LF_WeightedAverage();
  float HasilPID = LF_PID();
  Serial.print(LF_Vertikal[0]);
  Serial.print(" ");
  Serial.print(LF_Vertikal[1]);
  Serial.print(" ");
  Serial.print(LF_Vertikal[2]);
  Serial.print(" ");
  Serial.print(LF_Vertikal[3]);
  Serial.print(" ");
  Serial.print(LF_Vertikal[4]);
  Serial.print(" ");
  Serial.print(LF_Vertikal[5]);
  Serial.print(" ");
  Serial.print(LF_Vertikal[6]);

  Serial.print(" ");
  Serial.print("  Hasil Hitungan = ");
  Serial.print(weighted_average);
  Serial.print("  Hasil PID = ");
  Serial.println(HasilPID);
}
