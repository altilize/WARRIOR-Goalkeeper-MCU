// ================= Baca Kompas ======================
void runkompas() {

  mpu.update();
  yaw = (int)mpu.getAngleZ() % 360 * -1;
  yaw -= heading;
  if (yaw < 0) yaw += 360;
  if (yaw > 180) yaw -= 360;

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