#include "Wire.h"
#include "MPU6050.h"

MPU6050 mpu;



void calibratetozero (){//time is using to limit inplement time of loop in this function,its unit is microsecond
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
}

  int16_t GyroOutput[3]={};
  int32_t OutputTotal[3]={};
  int16_t OutputAverage[3]={};
  int32_t times=1;

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
  calibratetozero();
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

int32_t integral_dt(int32_t* fx){
  int64_t timepointbefore=0;
  int64_t timepoint=micros();

}

int32_t PIDcontrol(int32_t fx,int32_t x,int32_t total){//warning:the x need infinitely near 0,which is the using restriction
  //constant
  int32_t kp=0;//it using to control the proportion of proportion part
  int32_t ki=0;//it using to control the proportion of intergal part
  int32_t kd=0;//it using to control the proportion of differential part

  //proportion
  int32_t p=kp*fx;

  //intergal
  total+=fx*x;
  int32_t i=ki*total;

  //differential
  int32_t d=kd*(fx/x);

  return(p+i+d);
}