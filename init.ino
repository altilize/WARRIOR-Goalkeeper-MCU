void inisiasimode() {
  inisiasimotor();
  inisiasiencoder();
  inisiasiinterupsi();
  inisiasitimer();
  //inisiasimpu();
  init_oled();
  initkompas();
  inisiasiLF();
}
void inisiasiLF() {
  // pinMode(LF_Pins_Vertikal[0], INPUT_PULLDOWN);
  // pinMode(LF_Pins_Vertikal[1], INPUT_PULLDOWN);
  // pinMode(LF_Pins_Vertikal[2], INPUT_PULLDOWN);
  // pinMode(LF_Pins_Vertikal[3], INPUT_PULLDOWN);
  // pinMode(LF_Pins_Vertikal[4], INPUT_PULLDOWN);
  // pinMode(LF_Pins_Vertikal[5], INPUT_PULLDOWN);
  // pinMode(LF_Pins_Vertikal[6], INPUT_PULLDOWN);
  // pinMode(LF_Pins_Vertikal[7], INPUT_PULLDOWN);

// ---------- LF Multiplexer ----------
  pinMode(LF_INPUT, INPUT_PULLDOWN);
  pinMode(LF_Selektor_0, OUTPUT);
  pinMode(LF_Selektor_1, OUTPUT);
  pinMode(LF_Selektor_2, OUTPUT);
  pinMode(LF_Selektor_3, OUTPUT);
}
void inisiasitimer() {
#if defined(TIM5)
  TIM_TypeDef *Instance = TIM5;
#else
  TIM_TypeDef *Instance = TIM5;
#endif
  HardwareTimer *MyTim = new HardwareTimer(Instance);
  MyTim->setOverflow(10, HERTZ_FORMAT);
  MyTim->attachInterrupt(updateoverflow);
  MyTim->resume();
}
void inisiasimotor() {
  pinMode(enableMotor, OUTPUT);

  pinMode(LMotor1, OUTPUT);
  pinMode(RMotor1, OUTPUT);
  pinMode(LMotor2, OUTPUT);
  pinMode(RMotor2, OUTPUT);
  pinMode(LMotor3, OUTPUT);
  pinMode(RMotor3, OUTPUT);
  pinMode(LMotor4, OUTPUT);
  pinMode(RMotor4, OUTPUT);
}
void inisiasiencoder() {
  pinMode(encodermotor1, INPUT);
  pinMode(encodermotor2, INPUT);
  pinMode(encodermotor3, INPUT);
  pinMode(encodermotor4, INPUT);

  pinMode(encoderodometry1A, INPUT_PULLUP);
  pinMode(encoderodometry1B, INPUT_PULLUP);
  pinMode(encoderodometry2A, INPUT_PULLUP);
  pinMode(encoderodometry2B, INPUT_PULLUP);
  pinMode(encoderodometry3A, INPUT_PULLUP);
  pinMode(encoderodometry3B, INPUT_PULLUP);
}

void inisiasiinterupsi() {
  attachInterrupt(digitalPinToInterrupt(encodermotor1), ISR_encoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(encodermotor2), ISR_encoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(encodermotor3), ISR_encoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(encodermotor4), ISR_encoder4, RISING);

  attachInterrupt(digitalPinToInterrupt(encoderodometry1A), encA, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderodometry2A), encB, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderodometry3A), encC, RISING);

  // attachInterrupt(digitalPinToInterrupt(LF_Pins[0]), sensor1_ISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(LF_Pins[1]), sensor2_ISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(LF_Pins[2]), sensor3_ISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(LF_Pins[3]), sensor4_ISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(LF_Pins[4]), sensor5_ISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(LF_Pins[5]), sensor6_ISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(LF_Pins[6]), sensor7_ISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(LF_Pins[7]), sensor8_ISR, CHANGE);
}
void init_oled() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;)
      ;
  }
  delay(1);
}
void initkompas() {
  RCC->APB1ENR |= (1 << 21);                // enable I2C CLOCK
  RCC->AHB1ENR |= (1 << 1);                 // Enable GPIOB CLOCK
  GPIOB->MODER |= (2 << 16) | (2 << 18);    // Bits (17:16)= 1:0 --> Alternate Function for Pin PB8; Bits (19:18)= 1:0 --> Alternate Function for Pin PB9
  GPIOB->OTYPER |= (1 << 8) | (1 << 9);     //  Bit8=1, Bit9=1  output open drain
  GPIOB->OSPEEDR |= (3 << 16) | (3 << 18);  // Bits (17:16)= 1:1 --> High Speed for PIN PB8; Bits (19:18)= 1:1 --> High Speed for PIN PB9
  GPIOB->PUPDR |= (1 << 16) | (1 << 18);    // Bits (17:16)= 0:1 --> Pull up for PIN PB8; Bits (19:18)= 0:1 --> pull up for PIN PB9
  GPIOB->AFR[1] |= (4 << 0) | (4 << 4);     // Bits (3:2:1:0) = 0:1:0:0 --> AF4 for pin PB8;  Bits (7:6:5:4) = 0:1:0:0 --> AF4 for pin PB9
  I2C1->CR1 |= (1 << 15);                   // reset the I2C
  I2C1->CR1 &= ~(1 << 15);                  // Normal operation
  I2C1->CR2 |= (45 << 0);                   // PCLK1 FREQUENCY in MHz
  I2C1->CCR = 225 << 0;                     // check calculation in PDF
  I2C1->TRISE = 46;                         // check PDF again
  I2C1->CR1 |= (1 << 0);                    // Enable I2C
  compass.init();
  //compass.setCalibration(838, 2861, -841, 1368, -63, 157);
  //utama()
  // compass.setCalibration(2762, 4798, 1783, 3920, 2510, 2697);
  // compass.setCalibration(-697, 3071, -1297, 1498, -1091, -117);
  // sudah nol di lap nasional
  compass.setCalibration(293, 3076, -975, 1665, 1407, 2850);
  // compass.setCalibration(807, 2791, -782, 1427, -11, 213);
  //cobaa
  // compass.setCalibration(657, 2925, -1015, 1537, -1088, -711);
  // compass.setCalibration(652, 2908, -993, 1511, -1165, -698);
  // compass.setCalibration(720, 2848, -920, 1445, -1106, -837);
  // compass.setCalibration(573, 2870, -1791, -512, -1283, 1020);

  compass.setSmoothing(20, true);
}