#include <Wire.h>
#include <Servo.h>
#include "MPU6050.h" // Source: https://github.com/TKJElectronics/KalmanFilter

//I2C i2c;
MPU6050 myMPU;
Servo servoX;
int pos = 0;
double angleX = 0;
double angleY = 0;
int setPos = 0;
int a=0;
int b=0;
double dif;
int sign;
/* IMU Data */
double p; // p constant for PID
double i; // i constant for PID
double d; // d constant for PID
void setup() {  
  Serial.begin(115200);
  servoX.attach(9);
  myMPU.initialize();
  delay(1000); // Wait for sensor to stabilize
  
  /* Set kalman and gyro starting angle */
   //myMPU.getData();
  while(fabs(angleX-180)>5)
  {
     servoX.write(pos);
     myMPU.readData();
     angleX = myMPU.getXangle();
     Serial.print("MPU angle: ");
     Serial.println(angleX); 
     //setPos = pos;
     Serial.print("Servo position: ");
     Serial.println(pos);
     delay(15);
     pos = pos + 1;
       
  }
  setPos = pos;
  Serial.print("set position: ");
  Serial.println(setPos);
  servoX.write(setPos);
  //timer = micros();
}

void loop() {
  /* Update all the values */ 
  myMPU.readData();
  angleX = myMPU.getXangle();
  dif = angleX - 180;
  Serial.println(dif);
  if(dif > 7) sign = 1;
  else if(dif < -7) sign = 2;
  else sign = 3;
  switch(sign)
  {
    case 1:
      a = a + 1;
      //b = 0;
      servoX.write(setPos + a);
      Serial.print("increase to ");
      Serial.println(setPos + a);
      delay(15);
      break;
    case 2:
      a = a - 1;
      //a = 0;
      servoX.write(setPos + a);
      Serial.print("decrease to ");
      Serial.println(setPos - a);
      delay(15);
      break;
    case 3:
      //a = 0;
      //b = 0;
      Serial.println("it is fine.");
      //servoX.write(setPos);
      delay(15);
  }
  
  
  /* Print Data */
  //myMPU.getFilteredData();
  delay(1);
}
