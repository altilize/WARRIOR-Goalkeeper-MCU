// =================== KAMUS SEND DATA ================================ //
// dataSTM[0] = Awalan (255) untuk kirim
// dataSTM[1] = Sign Kompas
// dataSTM[2] = Kompas
// dataSTM[3] = Keypad
// dataSTM[4] = belum dipake
// dataSTM[5] = belum dipake
// dataSTM[6] = belum dipake
// dataSTM[7] = belum dipake
// dataSTM[8] = Grid X
// dataSTM[9] = Grid Y
// dataSTM[10] = Sign Pos X
// dataSTM[11] = Pos X Data pertama
// dataSTM[12] = Pos X Data Kedua
// dataSTM[13] = Sign pos Y
// dataSTM[14] = Pos Y Data Pertama
// dataSTM[15] = Pos Y Data Kedua
// ============================================================== //

// ================= KAMUS RECEIVED DATA ======================== //
// receiveddata[0] = Awalan, 250 buat change grid // 254 buat nerima normal
// receiveddata[1] =
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
  dataSTM[11] = (posX >> 8) & 0xFF; // coba di AND sama (FF)16 alias (11111111)2
  dataSTM[12] = posX & 0xFF;
  dataSTM[13] = signPosY;
  dataSTM[14] = (posY >> 8) & 0xFF;
  dataSTM[15] = posY & 0xFF;
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
