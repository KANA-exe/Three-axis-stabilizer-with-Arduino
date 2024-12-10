#include"Wire.h"
#include"MPU6050.h"//the library is from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
#include<Servo.h>

//the customize function list
void calibrate-to-zero (int64_t time);//using to calibrate gyro to zero

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
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);//set gyro detect range to 500 degrees/sec from 2000 degrees/sec
  mpu.setZGyroOffset(29);//the function use for calibratiom(value:x=114,y=-77,z=3)
  Xservo.attach(servopin);//set Servo pin address
  Xservo.write(90);//initailize the servo pointing to angle to 90 degrees
}

void loop() {
  timepoint=micros();//log the time that the loop start
  
  if(totalTime>=detecttime>0){
    int32_t rotationangle=totalAngle/(1000000);
    totalTime=0;
  }

  //calculate Rotation angle
  xInput=mpu.getRotationZ();//input the angular velocity
  RotationAnglePerSecond=map(xInput,-32767,32767,-2000,2000);//transform the angular velocity from +/-32767 to +/-2000
  Serial.print(xInput);Serial.println("\t");
  RotationAngle=RotationAnglePerSecond*deltaTime;//integral RotationAnglePerSecond (transform to RotationAngle from RotationAnglePerSecond)
  
  //calculate using time and log time point
  totalAngle+=RotationAngle;//Add up RotationAngle to totalAngle
  deltaTime=timepoint-timepointBefore;//calculate deltatime in this loop
  totalTime+=deltaTime;//Add up deltaTime to totalTime
  timepointBefore=timepoint;//memery the timepoint in this loop
}

void calibrate-to-zero (int64_t time){//time is using to limit inplement time of loop in this function 
  //set all offset to zero
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);

  //array about output calculation
  int16_t GyroOutput[3]={};//save input information from MPU6050{x,y,z}
  int32_t OutputTotal[3]={};//calculate the sum of GyroOutput
  int16_t OutputAverage[3]={};//calculate the average of GyroOutput in some time
  
  //value about time and lap of loop
  int64_t origin=micros();//memer the origintime
  int32_t times=0;//log the lap of the loop

  while(1){
    times++;
    mpu.getRotation(&GyroOutput[0],&GyroOutput[1],&GyroOutput[2]);//get input of mpu6050
    for(int i=0;i<3;i++){//calculate the output average
      OutputTotal[i]+=GyroOutput[i];//calculate the sum of GyroOutput
      OutputAverage[i]=OutputTotal[i]/times;//calculate the average of GyroOutput in some time
    }

    int64_t time=micros();//get the time point of the loop that was been implement finish
    
    if(time-origin>=time){//condition of to break the while loop
      break;
    }
  }

  //set new offset
  mpu.setXGyroOffset(-2*OutputAverage[0]);
  mpu.setYGyroOffset(-2*OutputAverage[1]);
  mpu.setZGyroOffset(-2*OutputAverage[2]);
}