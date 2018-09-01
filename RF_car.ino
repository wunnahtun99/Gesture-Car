
#include<SPI.h>
#include<RF24.h>
#include "nRF24L01.h"
RF24 radio(7,8);
const byte address[6] = "00001";
int active=200;
int off=5;
int Motor1A = 3;
int Motor1B = 4;
int Motor2A = 5;
int Motor2B = 6;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode( Motor1A, OUTPUT );
  pinMode( Motor1B, OUTPUT );
  pinMode( Motor2A, OUTPUT );
  pinMode( Motor2B, OUTPUT );
}

void loop() {
 
if(radio.available())
  {
   Serial.println("hi");
    char data  = "";
    radio.read(&data,sizeof(data));
    Serial.println(data);
    
  

  
          
      Serial.print("\n");        
      if(data == 'f')     {  
        forward();
        Serial.println("Forward");
    
        }
        else if(data == 'b')       {  
          backward();

      }
      else if(data == 'l')       {  
        left();
      }
      else if(data == 'r')       {
        right();
      }
      else if(data == 's')       {
        stop();
      }
      
      
      
   
     
   }  
   
 }



void backward(){

  digitalWrite( Motor1A, HIGH );
  digitalWrite( Motor1B, LOW );
  digitalWrite( Motor2A, HIGH );
  digitalWrite( Motor2B, LOW );
  delay(active);
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor2B, LOW );
  delay(off);
  digitalWrite( Motor1A, LOW );
  digitalWrite( Motor1B, LOW );
  delay(off);


}
void forward(){

  digitalWrite( Motor1A, LOW );
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor1B, HIGH );

 
  digitalWrite( Motor2B, HIGH );
  delay(active);
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor2B, LOW );

  
  digitalWrite( Motor1B, LOW );
  delay(off);
}

void left(){

  digitalWrite( Motor1A, HIGH );
  digitalWrite( Motor1B, HIGH );
  delay(active);
  digitalWrite( Motor1A, LOW );
  digitalWrite( Motor1B, LOW );
  delay(off);
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor2B, HIGH );
  delay(active);
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor2B, LOW );
  delay(off);
}

void right(){

  digitalWrite( Motor1A, LOW );
  digitalWrite( Motor1B, HIGH );
  delay(active);
  digitalWrite( Motor1A, LOW );
  digitalWrite( Motor1B, LOW );
  delay(off);   
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor2B, LOW );
  delay(active);
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor2B, LOW );
  delay(off);
}
void stop(){
  digitalWrite( Motor1A, LOW );
  digitalWrite( Motor1B, LOW );
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor2B, LOW );
}

