#include"Wire.h"
#include"MPU6050.h"//the library is from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
#include<Servo.h>

//variable or name for servo and senser 
MPU6050 mpu;//name MPU6050 mpu
Servo Xservo;//name X axis servo Xservo
int16_t servopin=3;//the servo pin in Arduino

//variable for input and calculation angle
int16_t xInput;//Receive x axis rotation information
double CalibrationValue;//Recording error value using to correct calibration
double RotationAnglePerSecond;//xInput translate to 0~+/-2000 degrees/sec
double RotationAngle;//RotationAnglePerSecond calculate to 0~180 degrees
int32_t totalAngle=90000000;//Recevie sum angle 
int32_t totalTime;//Receive how many time(microsecond) in some loop

//variable for time 
uint64_t timepoint=0;//the time that the loop was implemented
uint64_t timepointBefore=0;//the time that the loop was finish
uint64_t deltaTime;//Difference between timepoint and timepointBefore
int64_t detecttime=10000;//when totaltime large than that,the microcontroller will calculate the angle that the servo need

void setup() {
  Serial.begin(38400);//set baud of Serial Moniter
  mpu.initialize();
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);//set gyro range to 500 degrees/sec from 2000 degrees/sec
  mpu.setZGyroOffset(29);//the function use for calibratiom(value:x=114,y=-77,z=3)
  Xservo.attach(servopin);//set Servo pin address
  Xservo.write(90);//initailize the servo pointing to angle to 90 degrees
}

void loop() {
  timepoint=micros();//log the time that the loop start
  
  if(totalTime>=detecttime>0){
    int32_t rotationangle=totalAngle/(1000000);
    //Xservo.write(rotationangle);
    //Serial.print(rotationangle);Serial.println("\t");
    totalTime=0;
  }

  xInput=mpu.getRotationZ();//input the angular velocity
  RotationAnglePerSecond=map(xInput,-32767,32767,-2000,2000);//transform the angular velocity from +/-32767 to +/-2000
  Serial.print(xInput);Serial.println("\t");
  RotationAngle=RotationAnglePerSecond*deltaTime;//integral RotationAnglePerSecond (transform to RotationAngle from RotationAnglePerSecond)
  totalAngle+=RotationAngle;//Add up RotationAngle to totalAngle
  deltaTime=timepoint-timepointBefore;//calculate deltatime in this loop
  totalTime+=deltaTime;//Add up deltaTime to totalTime
  timepointBefore=timepoint;//
}