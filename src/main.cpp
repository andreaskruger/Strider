#include <Arduino.h>
#include <Sparkfun_TB6612.h>


#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 3
#define PWMB 6
#define STBY 9

#define MaxSpeed 255
#define BaseSpeed 255 
#define speedturn 180

const int offsetA = 1;
const int offsetB = 1;
int position;
int direction;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void move(int motor, int speed, int direction){
   digitalWrite(STBY, HIGH); 
   boolean inPin1=HIGH;
   boolean inPin2=LOW;
  
  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }  
  if(direction == 0){
    inPin1 = LOW;
    inPin2 = HIGH;
  }
   if(motor == 0){
      digitalWrite(AIN1, inPin1);
      digitalWrite(AIN2, inPin2);
      analogWrite(PWMA, speed);
   }
   if(motor == 1){
      digitalWrite(BIN1, inPin2);
      digitalWrite(BIN2, inPin1);
      analogWrite(PWMB, speed);
   }
}

void setup() {
  //Define motor pins
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
}

void loop() {
  position = 1;
  move(0,255,1);
  move(1,255,1);
  speed = PID_speed(position);
  if(position > 0 :move(1,255-speed,1) ? move(2,255-speed,1));
}