
#include "song_1.h"
#include "song_2.h"
#include "song_3.h"
//#include "song_4.h"


#define SPEAKER_PIN 1
#define SENSOR_PIN 0

#define MSONG 3
unsigned long SENSOR_DELAY=2000;

int LED_PIN[]={4,3,2};

int _step=200;
int _rest=120;
int _blink=20;


int _song_order[]={0,1,2};
int _song_index=0;

unsigned char _freq[]={239,  213,  201,  190,
                      179,  169,  159,  150, 
                      142,  134,  127,  239,  
                      225,  213,  201,  159};

int _sensor_stage=0; // 0: null, 1: water, 2: dry, 3:sing


//int _sensed_time;
//unsigned long _last_millis;


void setup(){

  pinMode(SPEAKER_PIN,OUTPUT);
  pinMode(LED_PIN[0],OUTPUT);
  pinMode(LED_PIN[1],OUTPUT);
  pinMode(LED_PIN[2],OUTPUT);

  pinMode(SENSOR_PIN,INPUT);

#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
#endif

  shuffleSongOrder();
  _sensor_stage=0;  

//  _last_millis=millis();
//  _sensed_time=0;
}

void loop(){

 

  bool _high=(digitalRead(SENSOR_PIN)==HIGH);

  switch(_sensor_stage){
     case 0: //null
        if(_high){
          _sensor_stage=1;
          delay(SENSOR_DELAY);
        }
        break;
     case 1: //water     
        if(!_high){
          _sensor_stage=2;  
          delay(SENSOR_DELAY);
        }
        break;
     case 2: //dry
        if(!_high){
          _sensor_stage=3;     
        }
        break; 
    case 3:
        playSong();

        _step=constrain(_step-10,80,240);
        _rest=_step/2;
        break;
     
  }
  
    


}

void shuffleSongOrder(){

  randomSeed(analogRead(0));
  
  for(int a=0;a<MSONG;a++){
    int r=random(MSONG);
    //if(r==a) continue;
    int temp=_song_order[a];
    _song_order[a]=_song_order[r];
    _song_order[r]=temp;
  }
  _song_index=0;
  
//#ifndef __AVR_ATtiny85__
//  for(int a=0;a<MSONG;++a) Serial.print(_song_order[a]);
//  Serial.println();
//#else
//  for(int a=0;a<MSONG;++a){
//    digitalWrite(LED_PIN[_song_order[a]],HIGH);    
//    delay(1000);    
//    digitalWrite(LED_PIN[_song_order[a]],LOW);
//  }
//  delay(2000);   
//#endif
}

