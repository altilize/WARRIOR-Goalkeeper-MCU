// ================= Baca Kompas ======================
void runkompas() {

  int a;
  int baw;


  compass.read();
  a = compass.getAzimuth();

  // Ensure azimuth is positive
  if (a < -180) {
    a = 360 + a;
  }
  // Check if button is pressed to reset the yaw
  if (ButtonPress == 5) {
    resetyaw = a;
  }

  // Calculate the yaw relative to the reset yaw
  baw = a - resetyaw;

  // Normalize the relative yaw to be within -180 to 180 degrees
  if (baw < -180) {
    baw += 360;
  } else if (baw > 180) {
    baw -= 360;
  }

  // yaw = 0;
  
  // int a;
  // Read compass values
  compass.read();

  // Return Azimuth reading
  yaw = compass.getAzimuth();
  if(a<180){
    a=360 + a;
  }
  if(ButtonPress == 5){

    resetyaw = a;
  } 
  baw = a-resetyaw;
  if(baw<0){
    baw = 360 + baw;
  }
  yaw = baw;
  if(yaw>180){
    yaw = baw-360;
  }

  sudut = 0;
  if (sudut <= 0) {
    signSudut = 1;
    sudut = 0 * -1;
  }
  else {
    signSudut = 0;
    sudut = 0;
  }
}

/*void pidkompas(){
  errorS = setPointS - sudut;

  PS = errorS;
  IS = IS + previousIS;g
  DD = errorD - previousErrorD;

  PIDvalueD = (KpD * PD) + (KiD * ID) + (KdD * DD);

  Pd += PIDvalueD;
  if (Pd > 255) Pd = 255;
  else if (Pd < 0) Pd = 0;

  speedD = Pd;
  if (flagPID_D)speedD *= -1;

  previousErrorD = errorD;
  previousID = ID
}*/