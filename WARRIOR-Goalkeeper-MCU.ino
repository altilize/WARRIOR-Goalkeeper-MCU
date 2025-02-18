/*
  ------------------------
    Kalau port ga kebaca 
  -----------------------
  Colokin port
  ls -l /dev/ttyACM0
  sudo usermod -a -G dialout $USER


  newgrp dialout (opsional)

  Matiin 5v, cabut port c
  Nyalain 5v, colokin port


  ------------------------
        push github
  -----------------------
  open in terminal file ini
  git add -A
  git commit -m "Pesan commit"
  git push
  
*/

//------------ Variabel Serial PC ------------------
unsigned char totalchecksum;
byte receiveddata[14];
unsigned char dataSTM[16], totalChecksum;

// ======== Line Follower ===============
/* 
  Multiplexer 0 - 6   = LF Vertikal
  Multiplexer 7 - 11  = LF Horizontal
  Multiplexer 12 - 15 = Belum Dipake
*/
float weights[] = { 30, 20, 10, 0, -10, -20, -30 };
//------ LF_PID----------
int LF_position = 0;
int LF_error = 0;
int LF_totalError = 0;
int LF_dError = 0;
int LF_lastError;
// -------- LF_Multiplexer-------------
const int LF_Selektor_0 = PE15;
const int LF_Selektor_1 = PD12;
const int LF_Selektor_2 = PD10;
const int LF_Selektor_3 = PD11;
const int LF_INPUT = PB1;

volatile int LF_Vertikal[8];
int LF_Read_Horizontal[5];

// ------- Fungsi untuk membaca Mux (0-15) --------
void LF_Sensor(int port) {
  if (port < 0 || port > 15) return;

  digitalWrite(LF_Selektor_0, port & 1);
  digitalWrite(LF_Selektor_1, (port >> 1) & 1);
  digitalWrite(LF_Selektor_2, (port >> 2) & 1);
  digitalWrite(LF_Selektor_3, (port >> 3) & 1);
}




// ========== Pin Motor =================
#define enableMotor PE7
#define RMotor1 PE13
#define LMotor1 PB10
#define LMotor2 PB6
#define RMotor2 PE6
#define RMotor3 PC8
#define LMotor3 PC9
#define LMotor4 PB7
#define RMotor4 PE5
// -------- Encoder Motor -------
#define encodermotor1 PC15
#define encodermotor2 PE4
#define encodermotor3 PE3
#define encodermotor4 PE2

#define pulse_mm (float)0.04567  //0.455


// =========== Pin Encoder Odometry ==============
#define encoderodometry3A PC1
#define encoderodometry3B PC0
#define encoderodometry2A PD9
#define encoderodometry2B PD5
#define encoderodometry1A PC10
#define encoderodometry1B PD2


// ------------- VARIABEL MOTOR, HOLONOMIC dan PID -------------------
float kecepatan_motor1, kecepatan_motor2, kecepatan_motor3, kecepatan_motor4;
float setpoint1, setpoint2, setpoint3, setpoint4;
bool flagPID1 = false, flagPID2 = false, flagPID3 = false, flagPID4 = false;
float Pa = 0, Pb = 0, Pc = 0, Pd = 0;
int speedA = 0, speedB = 0, speedC = 0, speedD = 0;
//----------------------------------------------------
int valuevx, valuevy, valuevz;
int speedrobot, heading;

//mode tes
bool tesauto = true;

// ---------------- VARIABEL ENCODER MOTOR ------------------------
volatile int encoder1RPM = 0, encoder2RPM = 0, encoder3RPM = 0, encoder4RPM = 0;
float rpmA = 0, rpmB = 0, rpmC = 0, rpmD = 0;
// ------------------ parameter setiap encoder -------------------
volatile int hasilencoder1 = 0, hasilencoder2 = 0, hasilencoder3 = 0, hasilencoder4 = 0;
float paramKpa = 0.01, paramKpb = 0.01, paramKpc = 0.01, paramKpd = 0.01;
float paramKia = 0, paramKib = 0, paramKic = 0, paramKid = 0;
float paramKda = 0.3, paramKdb = 0.3, paramKdc = 0.3, paramKdd = 0.3;
int arah = 90, cepat = 0;


//---------- VARIABEL ENCODER PADA ODOMETRY ----------------
#define kelilingroda (float)18.212  //(2*pi*r)cm
volatile int hasilencoderodometry1 = 0, hasilencoderodometry2 = 0, hasilencoderodometry3 = 0;
float Da = 0.0, Db = 0.0, Dc = 0.0;
float vx = 0, vy = 0, vteta = 0;
float L = 117;
float Xpos = 0, Ypos = 0, Tpos;
float Ypos_last = 0;
int gridX = 0, gridY = 0;
int gridsize = 50;
int statusbutton = 0;
int sendposX, sendposY;
int signsendposY, signsendposX;


//------------- VARIABEL DAN LBIRARY OLED ---------------
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


//----------- VARIABEL DAN LBIRARY KEYPAD ---------------
#include <Keypad.h>
int KEY, ButtonPress = 0;

const byte ROWS = 4, COLS = 5;
unsigned char customKey;
char hexaKeys[ROWS][COLS] = {
  { 1, 2, 3, 4, 5 },
  { 6, 7, 8, 9, 10 },
  { 11, 12, 13, 14, 15 },
  { 16, 17, 18, 19, 20 },
};
byte rowPins[ROWS] = { PA2, PA4, PA6, PC4 }, colPins[COLS] = { PC5, PA7, PB0, PA3, PA1 };
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



//---------------- VARIABEL KICKER -------------------
const int ledtendang = PD14;
const int kick = PE11;
const int charge = PB1;
int count = 0;


//------------- VARIABEL KOMPAS ---------------
#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
byte signPosX, signPosY;
int posX, posY;
bool resetHeading = false;
int sudut = 0;
int signSudut = 0;
int yaw = 0;

byte negasi;
#define SWITCH PA0

int encoderHAValue;
int encoderHBValue;

const float pi = 3.14159265358979323846;

// ----------- Kalman Filter -----------------------
#include <ArduinoEigenDense.h>
#include <math.h>

// Define the state dimension and measurement dimension
const int STATE_DIM = 3;        // [x, y, theta]
const int MEASUREMENT_DIM = 3;  // [x, y, theta]

// UKF parameters
const float alpha = 0.001f;
const float beta = 2.0f;
const float kappa = 0.0f;
const float lambda = alpha * alpha * (STATE_DIM + kappa) - STATE_DIM;

// State and covariance matrices
Eigen::VectorXf x(STATE_DIM);                         // State vector
Eigen::MatrixXf P(STATE_DIM, STATE_DIM);              // State covariance matrix
Eigen::MatrixXf Q(STATE_DIM, STATE_DIM);              // Process noise covariance matrix
Eigen::MatrixXf R(MEASUREMENT_DIM, MEASUREMENT_DIM);  // Measurement noise covariance matrix

// Sigma points and weights
Eigen::MatrixXf sigmaPoints(STATE_DIM, 2 * STATE_DIM + 1);
Eigen::VectorXf weightsMean(2 * STATE_DIM + 1);
Eigen::VectorXf weightsCov(2 * STATE_DIM + 1);
