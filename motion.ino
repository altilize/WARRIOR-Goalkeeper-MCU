// ============= Hitung Holonomic ================
void holonomic(float vx, float vy, float vz) {
// ======== Line Follower ============
  // vz = LF_PID();
  // float LF_vy = 0;
  // LF_vy = LF_PID() / 15;
  // Serial.println(vy); Serial.print("   vz ="); Serial.println(vz);

  kecepatan_motor1 = (-0.35 * vx) + (0.35 * vy) + (0.25 * vz);
  kecepatan_motor2 = (-0.35 * vx) + (-0.35 * vy) + (0.25 * vz);
  kecepatan_motor3 = (0.35 * vx) + (-0.35 * vy) + (0.25 * vz);
  kecepatan_motor4 = (0.35 * vx) + (0.35 * vy) + (0.25 * vz);

  setpoint1 = kecepatan_motor1;
  setpoint2 = kecepatan_motor2;
  setpoint3 = kecepatan_motor3;
  setpoint4 = kecepatan_motor4;

  if (setpoint1 < 0) {
    setpoint1 *= -1;
    flagPID1 = true;
  } else if (setpoint1 > 0) {
    flagPID1 = false;
  } else if (setpoint1 == 0) {
    setpoint1 = 0;
  }

  if (setpoint2 < 0) {
    setpoint2 *= -1;
    flagPID2 = true;
  } else if (setpoint2 > 0) {
    flagPID2 = false;
  } else if (setpoint2 == 0) {
    setpoint2 = 0;
  }

  if (setpoint3 < 0) {
    setpoint3 *= -1;
    flagPID3 = true;
  } else if (setpoint3 > 0) {
    flagPID3 = false;
  } else if (setpoint3 == 0) {
    setpoint3 = 0;
  }

  if (setpoint4 < 0) {
    setpoint4 *= -1;
    flagPID4 = true;
  } else if (setpoint4 > 0) {
    flagPID4 = false;
  } else if (setpoint4 == 0) {
    setpoint4 = 0;
  }
  pid();
  //speedA = setpoint1;
  //speedB = setpoint2;
  //speedC = setpoint3;
  //speedD = setpoint4;
  motorauto();
}

void motorauto() {
  digitalWrite(enableMotor, HIGH);
  if (digitalRead(SWITCH) == LOW) {
    speedA = 0;
    speedB = 0;
    speedC = 0;
    speedD = 0;
  }
  // if(signSudut == 1){
  // speedA = speedA * -1;
  // speedB = speedB * -1;
  // speedC = speedC * -1;
  // speedD = speedD * -1;
  // }


  // -------- motor A ------------
  if (speedA > 0) {
    analogWrite(LMotor1, 0);
    analogWrite(RMotor1, speedA);
  } else if (speedA < 0) {
    speedA *= -1;
    analogWrite(LMotor1, speedA);
    analogWrite(RMotor1, 0);
  } else if (speedA == 0) {
    speedA = 0;
    analogWrite(LMotor1, 0);
    analogWrite(RMotor1, 0);
  }


  // -------- motor B ------------
  if (speedB > 0) {
    analogWrite(LMotor2, speedB);
    analogWrite(RMotor2, 0);
  }

  else if (speedB < 0) {
    speedB *= -1;
    analogWrite(LMotor2, 0);
    analogWrite(RMotor2, speedB);
  } else if (speedB == 0) {
    speedB = 0;
    analogWrite(LMotor2, 0);
    analogWrite(RMotor2, 0);
  }


  // -------- motor C ------------
  if (speedC > 0) {
    analogWrite(LMotor3, 0);
    analogWrite(RMotor3, speedC);
  }

  else if (speedC < 0) {
    speedC *= -1;
    analogWrite(LMotor3, speedC);
    analogWrite(RMotor3, 0);
  } else if (speedC == 0) {
    speedC = 0;
    analogWrite(LMotor3, 0);
    analogWrite(RMotor3, 0);
  }


  // -------- motor D ------------
  if (speedD > 0) {
    analogWrite(LMotor4, speedD);
    analogWrite(RMotor4, 0);
  }

  else if (speedD < 0) {
    speedD *= -1;
    analogWrite(LMotor4, 0);
    analogWrite(RMotor4, speedD);
  } else if (speedD == 0) {
    speedD = 0;
    analogWrite(LMotor4, 0);
    analogWrite(RMotor4, 0);
  }
}


void rpm_track() {
  int rpmtot = (abs(rpmA) + abs(rpmB) + abs(rpmC) + abs(rpmD)) / 4;
  float vtot = (rpmtot * (0.1 * pi)) / 60;
  Serial.print(vtot);
  Serial.println("m/s");
}