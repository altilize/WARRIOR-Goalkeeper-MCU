void UART_send()
{
  dataSTM[0] = 255;                       // HEADING
  dataSTM[1] = signSudut;             // KOMPAS SIGN
  dataSTM[2] = sudut;// + 20;           // KOMPAS
  dataSTM[3] = ButtonPress;// + 20; // KEYPAD
  dataSTM[4] = !digitalRead(PB12);   // IR MUSUH 1
  dataSTM[5] = !digitalRead(PB14);   // IR MUSUH 2
  dataSTM[6] = !digitalRead(PE15);   // IR MUSUH 3
  dataSTM[7] = !digitalRead(PB11);   // IR BOLA
  dataSTM[8] = gridX; // GRID X
  dataSTM[9] = gridY;// + 20; // GRID Y
  dataSTM[10] = signPosX;
  dataSTM[11] = posX >> 8;
  dataSTM[12] = posX;
  dataSTM[13] = signPosY;
  dataSTM[14] = posY >> 8;
  dataSTM[15] = posY;
  Serial.write(dataSTM, 16);
}

bool sending = false;
void UART_receive()
{
  if (ButtonPress != 0) UART_send();
    if (Serial.available())
    {
      receiveddata[0] = Serial.read();

      if (receiveddata[0] == 254)
      {
        byte total_checksum = 0;

        for (int i = 1; i < 12; i++)
        {
          receiveddata[i] = Serial.read();
          total_checksum = total_checksum + receiveddata[i];
        }

        receiveddata[12] = Serial.read();
        byte negasi = ~total_checksum;

        if (negasi == receiveddata[12])
        {
          UART_send(); ButtonPress = 0;
          if (receiveddata[11] == 1 || receiveddata[11] == 2)
          {
            //KICKer();
            //digitalWrite(LED_TENDANG, HIGH);
          }
          else
          {
            //digitalWrite(LED_TENDANG, LOW);
          }
        }


      }
      else if (receiveddata[0] == 250)
      {
        byte total_checksum = 0;
        for (int i = 1; i < 12; i++)
        {
          receiveddata[i] = Serial.read();
          total_checksum = total_checksum + receiveddata[i];
        }
        receiveddata[12] = Serial.read();
        byte negasi = ~total_checksum;

        if (negasi == receiveddata[12])
        {
          UART_send(); ButtonPress = 0;
          gridX = receiveddata[1];
          gridY = receiveddata[2];
          ubahposisi(gridX,gridY);
          if (receiveddata[3]!=0) {
            heading = receiveddata[3];
            int signcom  = receiveddata[4];
            if(signcom == 1){
              heading = heading*-1;
            }
            else{
              heading = heading;
            }
            yaw = 0;
            yaw = mpu.getAngleZ()*-1;
            heading += yaw;
            receiveddata[3] = 0;
          }
        }
      }
      else Serial.flush();
    }
}
