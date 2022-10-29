#include<Arduino.h>

double Kp = 0.5;  
double Kd = 2;
double ki = 0;
double currentTime=0;
double lastTime = 0;
double lastError = 0;
double eTime = 0;
double cum = 0;

int PID_speed(int position){
    int error = position - 2500;
    currentTime = millis();
    eTime = currentTime - lastTime;
    cum =cum + error*eTime;
    int motorSpeed = Kp * error + Kd * ((error - lastError)/(eTime))+ ki*(cum);
    lastError = error;
    lastTime = currentTime;
    return motorSpeed;
}