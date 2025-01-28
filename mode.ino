// ---------------- RESET (Set Zero All) -----------------------
void setzeroall() {
  valuevx = 0, valuevy = 0, valuevz = 0;
  Pa = 0, Pb = 0, Pc = 0, Pd = 0;
  setpoint1 = 0, setpoint2 = 0, setpoint3 = 0, setpoint4 = 0;
  speedA = 0, speedB = 0, speedC = 0, speedD = 0;
  /*  paramKpa = 0;
  paramKia = 0;
  paramKda = 0;

  paramKpb = 0;
  paramKib = 0;
  paramKdb = 0;

  paramKpc = 0;
  paramKic = 0;
  paramKdc = 0;

  paramKpd = 0;
  paramKid = 0;
  paramKdd = 0;
*/
}

// ------------------- Fungsi Play ----------
void play() {
  if (statusbutton) {
    if (receiveddata[1]) {
      playauto();
    } else {
      digitalWrite(enableMotor, LOW);
      speedrobot = 0;
      heading = 0;
      valuevx = 0;
      valuevy = 0;
      valuevz = 0;
      setzeroall();
    }

  } else if (!statusbutton) {
    digitalWrite(enableMotor, LOW);
    speedrobot = 0;
    heading = 0;
    valuevx = 0;
    valuevy = 0;
    valuevz = 0;
    setzeroall();
  }
}

// ---------------- Play Auto --------------------------
void playauto() {

  /*
    Heading 0 robot maju;
    Heading 180 robot mudur;
    Heading 90 robot kanan;
    heading -90 robot kiri;
  */


  // ------------------------------------------------------
  speedrobot = 100;
  if (gridX == 0) {
    heading = 90;
  } else if (gridX == 3) {
    heading = -90;
  }
  // if ((gridX == 2 && heading == 90) || (gridX == 1 && heading == -90)) {
  //   speedrobot = 50;
  // }
  // -------------------------------------------------------

  if (receiveddata[4]) {
    heading *= -1;
  } else if (!receiveddata[4]) {
    heading = heading;
  }
  valuevx = speedrobot * sin(radians(heading));
  valuevy = speedrobot * cos(radians(heading));
  valuevz = ((receiveddata[7] << 8) + receiveddata[8]);

  if (receiveddata[6]) {
    valuevz *= -1;
  } else {
    valuevz = valuevz;
  }

  holonomic(valuevx, valuevy, valuevz);


  // ------- Coba LF tanpa Holonomic -----------
  // float LF_Value = LF_Vertikal();

  // if (gridX == 0) {
  //   kecepatan_motor1 = -1 * (speedrobot * 35 / 100) + LF_Value;
  //   kecepatan_motor2 = -1 * (speedrobot * 35 / 100) + LF_Value;
  //   kecepatan_motor3 = (speedrobot * 35 / 100) + LF_Value;
  //   kecepatan_motor4 = (speedrobot * 35 / 100) + LF_Value;
  // } else if (gridX == 3) {
  //   kecepatan_motor1 = (speedrobot * 35 / 100) + LF_Value;
  //   kecepatan_motor2 = (speedrobot * 35 / 100) + LF_Value;
  //   kecepatan_motor3 = -1 * (speedrobot * 35 / 100) + LF_Value;
  //   kecepatan_motor4 = -1 * (speedrobot * 35 / 100) + LF_Value;
  // }

  // setpoint1 = kecepatan_motor1;
  // setpoint2 = kecepatan_motor2;
  // setpoint3 = kecepatan_motor3;
  // setpoint4 = kecepatan_motor4;

  // // speedA = kecepatan_motor1;
  // // speedB = kecepatan_motor2;
  // // speedC = kecepatan_motor3;
  // // speedD = kecepatan_motor4;

  // if (setpoint1 < 0) {
  //   setpoint1 *= -1;
  //   flagPID1 = true;
  // } else if (setpoint1 > 0) {
  //   flagPID1 = false;
  // } else if (setpoint1 == 0) {
  //   setpoint1 = 0;
  // }

  // if (setpoint2 < 0) {
  //   setpoint2 *= -1;
  //   flagPID2 = true;
  // } else if (setpoint2 > 0) {
  //   flagPID2 = false;
  // } else if (setpoint2 == 0) {
  //   setpoint2 = 0;
  // }

  // if (setpoint3 < 0) {
  //   setpoint3 *= -1;
  //   flagPID3 = true;
  // } else if (setpoint3 > 0) {
  //   flagPID3 = false;
  // } else if (setpoint3 == 0) {
  //   setpoint3 = 0;
  // }

  // if (setpoint4 < 0) {
  //   setpoint4 *= -1;
  //   flagPID4 = true;
  // } else if (setpoint4 > 0) {
  //   flagPID4 = false;
  // } else if (setpoint4 == 0) {
  //   setpoint4 = 0;
  // }

  // pid();
  // motorauto();
}