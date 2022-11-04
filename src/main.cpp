#include <Arduino.h>
#include <Sparkfun_TB6612.h>
#include <QTRSensors.h>
#include <PID.h>


#define AIN1 4
#define BIN1 2
#define AIN2 5
#define BIN2 0
#define PWMA 6
#define PWMB 1
#define STBY 3

#define MaxSpeed 255
#define BaseSpeed 255 
#define speedturn 180

const int offsetA = 1;
const int offsetB = 1;
int position;
int direction;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

QTRSensors qtr;

const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];


void move(int motor, int speed, int direction){
  if(motor == 1){
    motor1.drive(speed,10);
  }
  if(motor == 2){
    motor2.drive(speed,10);
  }
}

void calibrateQTR(){
  // configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){7, 8, 9, 10}, SensorCount);
  delay(500);

  // 2.5 ms RC read timeout (default) * 10 reads per calibrate() call
  // = ~25 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  Serial.println("Calibration done, printing calibration values(Minimum): ");

  // print the calibration minimum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println("Calibration done, printing calibration values(Maximum): ");
  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}
int readQTR(){
  
}

void setup() {
  //Define motor pins
  Serial.begin(115200);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH); 
  Serial.println("Starting calibration: ");
  delay(1000);
  calibrateQTR();
  Serial.println("Starting loop: ");
}

void loop() {
  
  position = qtr.readLineBlack(sensorValues);
  float speed = PID_speed(position);
  Serial.print("Speed: ");
  Serial.println(speed);
  //if(position > 0){ move(0,255-speed,1); }else{ move(1,255-speed,1);};
  move(1,255,1);
  move(2,255,1);
  delay(25);
}