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
  speedrobot = ((receiveddata[2] << 8) + receiveddata[3]);
  heading = receiveddata[5];
  // -------------------------------------------------------

    if (receiveddata[4]) {
    heading *= -1;
  }  else if (!receiveddata[4]) {
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
}