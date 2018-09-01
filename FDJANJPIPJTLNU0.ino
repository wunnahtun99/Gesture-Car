//Written by Ahmet Burkay KIRNIK
//TR_CapaFenLisesi
//Measure Angle with a MPU-6050(GY-521)

#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;
 
#include<SPI.h>
#include<RF24.h>
#include"nRF24L01.h"
RF24 radio(7,8);
const byte address[6] = "00001";

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop(){
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
    int xAng = map(AcX,minVal,maxVal,-90,90);
    int yAng = map(AcY,minVal,maxVal,-90,90);
    int zAng = map(AcZ,minVal,maxVal,-90,90);

       x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
       y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
       z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

    if((x>345 || x<10) && (y>345 || y<10)){
      Serial.println("stop");
      const char text[] = "s";
      radio.write(&text,sizeof(text));
    }
    else if (x<310 && x>270){
      Serial.println("Forward");
      const char text[] = "f";
      radio.write(&text,sizeof(text));
    }
    else if (x>60 && x<100){
       Serial.println("backward");
       const char text[] = "b";
      radio.write(&text,sizeof(text));
    }
    else if (y<275 && y>255){
      Serial.println("right");
      const char text[] = "r";
      radio.write(&text,sizeof(text));
    }
    else if (y>45 && y<90){
       Serial.println("left");
       const char text[] = "l ";
      radio.write(&text,sizeof(text));
    }
    

    
   Serial.print("AngleX= ");
   Serial.println(x);

  Serial.print("AngleY= ");
  Serial.println(y);

   //Serial.print("AngleZ= ");
   //Serial.println(z);
   Serial.println("-----------------------------------------");
     delay(500);
}
