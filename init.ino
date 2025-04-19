void inisiasimode() {
  //inisiasiI2C();
  //initkompas();
  inisiasimotor();
  inisiasiencoder();
  inisiasiinterupsi();
  inisiasitimer();
  init_oled();
  inisiasiLF();
  inisiasiLidar();
}

void inisiasiI2C() {
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
}

void inisiasiLidar() {
  for (uint8_t i = 0; i < 2; i++) {
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);
  }
  for (uint8_t i = 0; i < 2; i++) {
    pinMode(xshutPins[i], INPUT);
    delay(10);
    lidar[i].setTimeout(500);
    if (!lidar[i].init()) {
      Serial.print("Gagal Membaca Sensor ");
      Serial.println(i);
    }
    lidar[i].setAddress(0x2A + i);
    lidar[i].startContinuous(50);
  }
}

void inisiasiLF() {
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
}

void init_oled() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;)
      ;
  }
  delay(1);
}

void initkompas() {

  byte status = mpu.begin();
  while (status != 0) {
    Serial.println("Ga Siap");
    delay(1000);
  } 

  mpu.calcOffsets(true, true);
}