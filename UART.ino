unsigned long tungguKir = 0;
void UART_send() {
  dataSTM[0] = 255;          // HEADING
  dataSTM[1] = signSudut;    // KOMPAS SIGN
  dataSTM[2] = sudut;        //sudut;// + 20;           // KOMPAS
  dataSTM[3] = ButtonPress;  // + 20; // KEYPAD
  // dataSTM[4] = !digitalRead(IRmusuh1);   // IR MUSUH 1
  // dataSTM[5] = !digitalRead(IRmusuh2);   // IR MUSUH 2
  // dataSTM[6] = !digitalRead(IRmusuh3);   // IR MUSUH 3
  // dataSTM[7] = !digitalRead(IRbola);   // IR BOLA
  dataSTM[8] = gridX;  // GRID X
  dataSTM[9] = gridY;  // + 20; // GRID Y
  dataSTM[10] = signsendposX;
  dataSTM[11] = sendposX >> 8;
  dataSTM[12] = sendposX;
  dataSTM[13] = signsendposY;
  dataSTM[14] = sendposY >> 8;
  dataSTM[15] = sendposY;
  Serial.write(dataSTM, 16);
}

bool sending = false;
void UART_receive() {
  if (ButtonPress != 0) UART_send();
  if (Serial.available()) {
    receiveddata[0] = Serial.read();

    if (receiveddata[0] == 254) {
      byte total_checksum = 0;

      for (int i = 1; i < 12; i++) {
        receiveddata[i] = Serial.read();
        total_checksum = total_checksum + receiveddata[i];
      }

      receiveddata[12] = Serial.read();
      byte negasi = ~total_checksum;

      if (negasi == receiveddata[12]) {
        UART_send();
        ButtonPress = 0;
      }


    } else if (receiveddata[0] == 250) {
      byte total_checksum = 0;
      for (int i = 1; i < 12; i++) {
        receiveddata[i] = Serial.read();
        total_checksum = total_checksum + receiveddata[i];
      }
      receiveddata[12] = Serial.read();
      byte negasi = ~total_checksum;

      if (negasi == receiveddata[12]) {
        UART_send();
        ButtonPress = 0;
        gridX = receiveddata[1];
        gridY = receiveddata[2];
        ubahposisi(gridX, gridY);
        if (receiveddata[3] == 1) {
          //heading = 0;
          //yaw = mpu.getAngleZ();
          //heading = yaw;
          receiveddata[3] = false;
        }
      }
    } else Serial.flush();
  }
}
