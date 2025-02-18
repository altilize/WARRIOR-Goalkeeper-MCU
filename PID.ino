///////////////////////////////////DEKLARASI////////////////////////////////
//0,=.00038
//kp = 0.03
//ki = 0.01
//kd = 0.015
//kp = 0.008
//ki = 0.0005
//kd = 0.035
//new set
// KpA = 0.02,
// KiA = 0.004,
// KdA = 0.035;
float KpA = 0.1,
      KiA = 0.05,
      KdA = 0.055;
float errorA = 0, PIDvalueA = 0;
float PA = 0, IA = 0, DA = 0;
float previousIA = 0, previousErrorA = 0;

float KpB = 0.1,
      KiB = 0.05,
      KdB = 0.055;
float errorB = 0, PIDvalueB = 0;
float PB = 0, IB = 0, DB = 0;
float previousIB = 0, previousErrorB = 0;

float KpC = 0.1,
      KiC = 0.05,
      KdC = 0.055;
float errorC = 0, PIDvalueC = 0;
float PC = 0, IC = 0, DC = 0;
float previousIC = 0, previousErrorC = 0;

float KpD = 0.1,
      KiD = 0.05,
      KdD = 0.055;
float errorD = 0, PIDvalueD = 0;
float PD = 0, ID = 0, DD = 0;
float previousID = 0, previousErrorD = 0;

/////////////////////////////////END DEKLARASI/////////////////////////////////

void pid() {
  /*//////////////////////////////////////////////////////////
     MOTOR A
  *//////////////////////////////////////////////////////////
  errorA = setpoint1 - rpmA;

  PA = errorA;
  IA = IA + previousIA;
  DA = errorA - previousErrorA;

  PIDvalueA = (KpA * PA) + (KiA * IA) + (KdA * DA);

  Pa += PIDvalueA;
  if (Pa > 255) Pa = 255;
  else if (Pa < 0) Pa = 0;

  speedA = Pa;
  if (flagPID1)speedA *= -1;

  previousErrorA = errorA;
  previousIA = IA;

  /*////////////////////////////////////////////////////////////
     MOTOR B
  *////////////////////////////////////////////////////////////
  errorB = setpoint2 - rpmB;

  PB = errorB;
  IB = IB + previousIB;
  DB = errorB - previousErrorB;

  PIDvalueB = (KpB * PB) + (KiB * IB) + (KdB * DB);

  Pb += PIDvalueB ;
  if (Pb > 255) Pb = 255;
  else if (Pb < 0) Pb = 0;

  speedB = Pb;
  if (flagPID2)speedB *= -1;

  previousErrorB = errorB;
  previousIB = IB;

  /*/////////////////////////////////////////////////////////////
     MOTOR C
  */////////////////////////////////////////////////////////////
  errorC = setpoint3 - rpmC;

  PC = errorC;
  IC = IC + previousIC;
  DC = errorC - previousErrorC;

  PIDvalueC = (KpC * PC) + (KiC * IC) + (KdC * DC);

  Pc += PIDvalueC ;
  if (Pc > 255) Pc = 255;
  else if (Pc < 0) Pc = 0;

  speedC = Pc;
  if (flagPID3)speedC *= -1;

  previousErrorC = errorC;
  previousIC = IC;

  /*/////////////////////////////////////////////////////////////
     MOTOR D
  */////////////////////////////////////////////////////////////
  errorD = setpoint4 - rpmD;

  PD = errorD;
  ID = ID + previousID;
  DD = errorD - previousErrorD;

  PIDvalueD = (KpD * PD) + (KiD * ID) + (KdD * DD);

  Pd += PIDvalueD;
  if (Pd > 255) Pd = 255;
  else if (Pd < 0) Pd = 0;

  speedD = Pd;
  if (flagPID4)speedD *= -1;

  previousErrorD = errorD;
  previousID = ID;
}
