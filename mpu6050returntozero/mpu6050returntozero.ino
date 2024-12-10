#include "Wire.h"
#include "MPU6050.h"

MPU6050 mpu;

int16_t GyroOutput[3]={};
int32_t OutputTotal[3]={};
int16_t OutputAverage[3]={};
int32_t times=1;

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
    
    if(time-origin>=time){
      break;
    }
  }

  //set new offset
  mpu.setXGyroOffset(-2*OutputAverage[0]);
  mpu.setYGyroOffset(-2*OutputAverage[1]);
  mpu.setZGyroOffset(-2*OutputAverage[2]);
}

void setup() {
  Serial.begin(9600);
  mpu.initialize();
  if(mpu.testConnection()==false){
    Serial.print("Connection Failed");
    while(true);
  }
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
  zero();
}

void loop() {
  mpu.getRotation(&GyroOutput[0],&GyroOutput[1],&GyroOutput[2]);
  for(int i=0;i<3;i++){
    OutputTotal[i]+=GyroOutput[i];
    OutputAverage[i]=OutputTotal[i]/times;
    Serial.print(GyroOutput[i]);Serial.print("\t");
    Serial.print(OutputAverage[i]);Serial.print("\t");
  }
  Serial.print("\n");
  times++;
}

