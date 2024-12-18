#include"Wire.h"
#include"MPU6050.h"//the library is from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
#include<Servo.h>

//the customize function list
void calibratetozero (int32_t outputpin);//using to calibrate gyro to zero
int32_t PIDcontrol(int32_t fx,int32_t x,int32_t total);//using to gave servo motor stable signal
int32_t outputpin=5;//pin of indicator light

//variable or name for servo and senser 
MPU6050 mpu;//name MPU6050 mpu
Servo Xservo;//name X axis servo Xservo
Servo Yservo;//name Y axis servo Yservo
Servo Zservo;//name Z axis servo Zservo
int16_t servopin[3]={3,5,6};//the servo pin in Arduino,definition is x,y,z

//variable for input and calculation angle
//the definition of the Array is {x,y,z}
int16_t Input[3]={};//Receive x axis rotation information
double CalibrationValue;//Recording error value using to correct calibration
double RotationAnglePerSecond[3]={};//xInput translate to 0~+/-2000 degrees/sec
double RotationAngle[3]={};//RotationAnglePerSecond calculate to 0~180 degrees
int64_t totalAngle[3]={};//Recevie sum angle 
int32_t rotate[3]={};//the rotation signal of servo moter

//variable for time 
int32_t totalTime;//Receive how many time(microsecond) in some loop
uint64_t timepoint=0;//the time that the loop was implemented
uint64_t timepointBefore=0;//the time that the loop was finish
uint64_t deltaTime;//Difference between timepoint and timepointBefore
int64_t detecttime=10000;//when totaltime large than that,the microcontroller will calculate the angle that the servo need

void setup() {
  Serial.begin(9600);//set baud of Serial Moniter
  mpu.initialize();
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);//set gyro detect range to 2000 degrees/sec from 20 degrees/sec
  pinMode(outputpin,OUTPUT);//define pin of indicator light
  calibratetozero(outputpin);//calibrate mpu6050

  //set Servo pin address
  Xservo.attach(servopin[0]);
  Yservo.attach(servopin[1]);
  Zservo.attach(servopin[2]);
  
  //initailize the servo pointing to angle to 90 degrees
  Xservo.write(90);
  Yservo.write(90);
  Zservo.write(90);
}

void loop() {
  timepoint=micros();//log the time that the loop start
  
  if(totalTime>=detecttime){
    for(int i=0;i<3;i++){
      rotate[i]=90+totalAngle[i]/1000000;//translate unit to second from micro second 
      rotate[i]=PIDcontrol(rotate[i],deltaTime,totalAngle[i]/1000000);//
    }
    
    //write the angle
    Xservo.write(rotate[0]);
    Yservo.write(rotate[1]);
    Zservo.write(rotate[2]);
    totalTime=0;//return to zero
  }

  //calculate Rotation angle
  mpu.getRotation(&Input[0],&Input[1],&Input[2]);//input the angular velocity
  for(int i=0;i<3;i++){
    RotationAnglePerSecond[i]=map(Input[i],-32767,32767,-2000,2000);//transform the angular velocity from +/-32767 to +/-2000
    RotationAngle[i]=RotationAnglePerSecond[i]*deltaTime;//integral RotationAnglePerSecond (transform to RotationAngle from RotationAnglePerSecond)
    totalAngle[i]+=RotationAngle[i];//Add up RotationAngle to totalAngle
  }
  
  //calculate using time and log time point
  deltaTime=timepoint-timepointBefore;//calculate deltatime in this loop
  totalTime+=deltaTime;//Add up deltaTime to totalTime
  timepointBefore=timepoint;//memery the timepoint in this loop
}

void calibratetozero (int32_t outputpin){//time is using to limit inplement time of loop in this function,its unit is microsecond
  //set all offset zero
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);

  //array about output calculation,definition={x,y,z}
  int16_t GyroOutput[3]={};//save input information from MPU6050
  int32_t OutputTotal[3]={};//calculate the sum of GyroOutput
  int16_t OutputAverage[3]={};//calculate the average of GyroOutput in some 

  //find the average of output 
  for(int t=0;t<75;t++){
    mpu.getRotation(&GyroOutput[0],&GyroOutput[1],&GyroOutput[2]);//get input of mpu6050
    for(int i=0;i<3;i++){//calculate the output average
      OutputTotal[i]+=GyroOutput[i];//calculate the sum of GyroOutput
      OutputAverage[i]=OutputTotal[i]/(t+1);//calculate the average of GyroOutput in some time
      Serial.print(OutputAverage[i]);Serial.print("\t");
      Serial.print(GyroOutput[i]);Serial.print("\t");
    }
    Serial.print(t+1);Serial.println("\t");
  }

  //set new offset
  mpu.setXGyroOffset(-2*OutputAverage[0]);
  mpu.setYGyroOffset(-2*OutputAverage[1]);
  mpu.setZGyroOffset(-2*OutputAverage[2]);

  //output signal that mean calibration to zero finished
  digitalWrite(outputpin,HIGH);
  delay(3000);
  digitalWrite(outputpin,LOW);
}

int32_t PIDcontrol(int32_t fx,int32_t x,int32_t total){//warning:the x need infinitely near 0,which is the using restriction
  //constant
  int32_t kp=1;//it using to control the proportion of proportion part
  int32_t ki=0;//it using to control the proportion of intergal part
  int32_t kd=0;//it using to control the proportion of differential part

  //proportion
  int32_t p=kp*fx;

  //intergal
  int32_t i=ki*total;

  //differential
  int32_t d=kd*(fx/x);

  return(p+i+d);
}