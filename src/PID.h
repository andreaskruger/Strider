#include<Arduino.h>

#define basePosition 2500

double Kp = 0.5;  
double Kd = 2;
double ki = 0;
double currentTime=0;
double lastTime = 0;
double lastError = 0;
double eTime = 0;
double cum = 0;

int PID_speed(int position){
    int error = position - basePosition;
    currentTime = millis();
    eTime = currentTime - lastTime;
    cum =cum + error*eTime;
    int motorSpeed = Kp * error + Kd * ((error - lastError)/(eTime))+ ki*(cum);
    lastError = error;
    lastTime = currentTime;
    if(motorSpeed < 0){motorSpeed = -1*motorSpeed;}
    if(motorSpeed >255){motorSpeed = 255;}
    return motorSpeed;
}