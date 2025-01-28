void ISR_encoder1 () {
  hasilencoder1++;
}
void ISR_encoder2 () {
  hasilencoder2++;
}
void ISR_encoder3 () {
  hasilencoder3++;
}
void ISR_encoder4 () {
  hasilencoder4++;
}

void encA() {
  (digitalRead(encoderodometry1A) == digitalRead(encoderodometry1B)) ? hasilencoderodometry1-- : hasilencoderodometry1++;}
void encB() {
  (digitalRead(encoderodometry2A) == digitalRead(encoderodometry2B)) ? hasilencoderodometry2++ : hasilencoderodometry2--;}
void encC() {
  (digitalRead(encoderodometry3A) == digitalRead(encoderodometry3B)) ? hasilencoderodometry3++ : hasilencoderodometry3--;}

void updateoverflow () {
  encoder1RPM = hasilencoder1;
  encoder2RPM = hasilencoder2;
  encoder3RPM = hasilencoder3;
  encoder4RPM = hasilencoder4;

  hasilencoder1 = 0;
  hasilencoder2 = 0;
  hasilencoder3 = 0;
  hasilencoder4 = 0;

  rpmA = (encoder1RPM * 60 * 10) / 134;
  rpmB = (encoder2RPM * 60 * 10) / 134;
  rpmC = (encoder3RPM * 60 * 10) / 134;
  rpmD = (encoder4RPM * 60 * 10) / 134;
/*
  Serial.print(rpmA);
  Serial.print("|");
  Serial.print(rpmB);
  Serial.print("|");
  Serial.print(rpmC);
  Serial.println();
  */
}