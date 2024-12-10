#include "Wire.h"
#include "MPU6050.h"

MPU6050 mpu;

int16_t GyroOutput[3]={};
int32_t OutputTotal[3]={};
int16_t OutputAverage[3]={};
int32_t times=1;

void zero(){
  mpu.getRotation(&GyroOutput[0],&GyroOutput[1],&GyroOutput[2]);
  for(int t=1;t<31;t++){
     for(int i=0;i<3;i++){
      OutputTotal[i]+=GyroOutput[i];
      OutputAverage[i]=OutputTotal[i]/t;
      Serial.print(GyroOutput[i]);Serial.print("\t");
      Serial.print(OutputAverage[i]);Serial.print("\t");
    }
    Serial.print("\n");
  }
  mpu.setXGyroOffset(-2*OutputAverage[0]);
  mpu.setYGyroOffset(-2*OutputAverage[1]);
  mpu.setZGyroOffset(-2*OutputAverage[2]);
  delay(12000);
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

