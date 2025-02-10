/*
  Board Line Follower Vertikal dipasang di ujung kanan robot dengan posisi menyilang terhadap garis lapangan.
  Board Line Follower Horizontal dipasang di tengah robot dengan posisi sejajar terhadap garis lapangan.

*/

// ============= Fungsi LF Vertikal =================
float LF_WeightedAverage() {
  float TotalWeight = 0;
  int TotalActiveSensor = 0;

  // ---------- READ SENSOR MUX ----------
  LF_Sensor(0);
  delayMicroseconds(20);
  LF_Vertikal[0] = analogRead(LF_INPUT);

  LF_Sensor(1);
  delayMicroseconds(20); //10
  LF_Vertikal[1] = analogRead(LF_INPUT);

  LF_Sensor(2);
  delayMicroseconds(20);
  LF_Vertikal[2] = analogRead(LF_INPUT);

  LF_Sensor(3);
  delayMicroseconds(20);
  LF_Vertikal[3] = analogRead(LF_INPUT);

  LF_Sensor(4);
  delayMicroseconds(20);
  LF_Vertikal[4] = analogRead(LF_INPUT);

  LF_Sensor(5);
  delayMicroseconds(20);
  LF_Vertikal[5] = analogRead(LF_INPUT);

  LF_Sensor(6);
  delayMicroseconds(20);
  LF_Vertikal[6] = analogRead(LF_INPUT);


  if (LF_Vertikal[0] >= 650) {
    TotalWeight += weights[0];
    TotalActiveSensor++;
  }
  if (LF_Vertikal[1] >= 650) {
    TotalWeight += weights[1];
    TotalActiveSensor++;
  }
  if (LF_Vertikal[2] >= 650) {
    TotalWeight += weights[2];
    TotalActiveSensor++;
  }
  if (LF_Vertikal[3] >= 650) {
    TotalWeight += weights[3];
    TotalActiveSensor++;
  }
  if (LF_Vertikal[4] >= 650) {
    TotalWeight += weights[4];
    TotalActiveSensor++;
  }
  if (LF_Vertikal[5] >= 650) {
    TotalWeight += weights[5];
    TotalActiveSensor++;
  }
  if (LF_Vertikal[6] >= 650) {
    TotalWeight += weights[6];
    TotalActiveSensor++;
  }
  // ------------------------------

  // Jika tidak ada garis
  if (TotalActiveSensor == 0) {
    return 0;
  }

  return TotalWeight / TotalActiveSensor;
}

// ================ PID Weighted Average =================
float LF_PID() {
  float LF_Kp = 1;
  float LF_Ki = 0;
  float LF_Kd = 0;
  
  LF_position = LF_WeightedAverage();

  // ----- Rumus PID ----------
  LF_error = LF_position;               // Propotional
  LF_totalError += LF_error;            // Integral
  LF_dError = LF_error - LF_lastError;  // Derrivative

  if (LF_totalError >= 50) {
    LF_totalError = 50;
  }else if(LF_totalError <= -50) {
    LF_totalError = -50;
  }
  LF_lastError = LF_error;

  float LF_PID_VALUE = (LF_Kp * LF_error) + (LF_Ki * LF_totalError) + (LF_Kd * LF_dError);

  if (LF_PID_VALUE >= 30) {
    LF_PID_VALUE = 30;
  }else if(LF_PID_VALUE <= -30) {
    LF_PID_VALUE = -30;
  }

  return LF_PID_VALUE;
}



// ================ Fungsi LF Horizontal =======================
// bool LF_Horizontal() {
//   for (int i = 0; i < 5; i++) {
//     LF_Read_Horizontal[i] = digitalRead(LF_Pins_Horizontal[i]);
//   }
//   // ------------- Semua Sensor nyentuh putih --------------------
//   if (LF_Read_Horizontal[0] == 1 && LF_Read_Horizontal[1] == 1 && LF_Read_Horizontal[2] == 1 && LF_Read_Horizontal[3] == 1
//       && LF_Read_Horizontal[4] == 1 && LF_Read_Horizontal[5] == 1) {
//     offside = 0;
//     return false;
//   }

//   // ------------- Semua putih kecuali ujung ------------
//   else if (LF_Read_Horizontal[0] == 0 || LF_Read_Horizontal[5] == 0 && LF_Read_Horizontal[1] == 1 && LF_Read_Horizontal[2] == 1 && LF_Read_Horizontal[3] == 1 && LF_Read_Horizontal[4] == 1) {
//     offside = 0;
//     return true;
//   }

//   // ------------- Semua Sensor tidak nyentuh putih --------------------
//   else if (LF_Read_Horizontal[0] == 0 && LF_Read_Horizontal[1] == 0 && LF_Read_Horizontal[2] == 0 && LF_Read_Horizontal[3] == 0
//            && LF_Read_Horizontal[4] == 0 && LF_Read_Horizontal[5] == 0) {
//     // 1 kemajuan, 2 kemunduran, 0 onside
//     if (Ypos >= 1000) {
//       offside = 1;
//     } else if (Ypos <= -1000) {
//       offside = 2;
//     } else {
//       offside = 0;
//     }
//     return false;
//   } else {
//     return true;
//   }
// }