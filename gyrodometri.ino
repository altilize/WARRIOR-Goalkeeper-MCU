void hitungposisi() {
  Da = (hasilencoderodometry1 * kelilingroda) / 400;  //800
  Db = (hasilencoderodometry2 * kelilingroda) / 400;
  Dc = (hasilencoderodometry3 * kelilingroda) / 400;

  hasilencoderodometry1 = 0;
  hasilencoderodometry2 = 0;
  hasilencoderodometry3 = 0;

  vx = (Da * cos(radians(60)) + Db * cos(radians(60)) - Dc);
  vy = (Da * sin(radians(30)) - Db * sin(radians(30)));
  vteta = ((Da / L) + (Db / L) + (Dc / L));

  Xpos -= ((sin(radians(yaw)) * vy) + (cos(radians(yaw)) * vx));
  Ypos -= ((cos(radians(yaw)) * vy) + (sin(radians(yaw)) * vx));
  Tpos += 1 * vteta;

  sendposX = (int)Xpos;
  sendposY = (int)Ypos;

  if (sendposX < 0) {
    signsendposX = 1;
    sendposX *= -1;
  } else {
    signsendposX = 0;
  }

  if (sendposY < 0) {
    signsendposY = 1;
    sendposY *= -1;
  } else {
    signsendposY = 0;
  }

  hitunggrid();
}

void hitunggrid() {
  gridX = Xpos / gridsize;
  gridY = Ypos / gridsize;

  if (gridX <= 0) {
    gridX = 0;
  }

  if (gridY <= 0) {
    gridY = 0;
  }
}

void ubahposisi(int gridX, int gridY) {
  Xpos = ((int)gridX * gridsize) + (gridsize / 2);
  Ypos = ((int)gridY * gridsize) + (gridsize / 2);
}
