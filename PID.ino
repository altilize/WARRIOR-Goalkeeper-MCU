// ============== Deklarasi Value PID ==================
float KpA = 0.0027,
      KiA = 0.00001,
      KdA = 0.00055;
float errorA = 0, PIDvalueA = 0;
float PA = 0, IA = 0, DA = 0;
float previousIA = 0, previousErrorA = 0;

float KpB = 0.0067,
      KiB = 0.00033,
      KdB = 0.00009;
float errorB = 0, PIDvalueB = 0;
float PB = 0, IB = 0, DB = 0;
float previousIB = 0, previousErrorB = 0;

float KpC = 0.0051,
      KiC = 0.0033,
      KdC = 0.00009;
float errorC = 0, PIDvalueC = 0;
float PC = 0, IC = 0, DC = 0;
float previousIC = 0, previousErrorC = 0;

float KpD = 0.0017,
      KiD = 0.0000145,
      KdD = 0.00058;
float errorD = 0, PIDvalueD = 0;
float PD = 0, ID = 0, DD = 0;
float previousID = 0, previousErrorD = 0;
// ===========================================

void pid() {
  // ------- Motor A ---------------
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


  // ------- Motor B ---------------
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


  // ------- Motor C ---------------
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


  // ------- Motor D ---------------
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
