
#include "song_1.h"
#include "song_2.h"
#include "song_3.h"
#include "song_4.h"


#define SPEAKER_PIN 1
#define SENSOR_PIN 0

#define MSONG 4
#define SENSOR_DELAY 3000

int LED_PIN[]={4,3,2};

int _step=200;
int _rest=120;
int _blink=20;


int _song_order[]={1,2,3,4};
int _song_index=0;

unsigned char _freq[]={239,  213,  201,  190,
                      179,  169,  159,  150, 
                      142,  134,  127,  239,  
                      225,  213,  201,  159};

int _sensor_stage=0; // 0: null, 1: water, 2: dry, 3:sing


unsigned long _sensed_time;

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
  
}

void loop(){
  
  bool _high=(digitalRead(SENSOR_PIN)==HIGH);


  switch(_sensor_stage){
     case 0: //null
        if(_high){
          _sensor_stage=1;
          _sensed_time=millis();
#ifndef __AVR_ATtiny85__
          Serial.println("water!");
#endif
        }
        break;
     case 1: //water
        if(!_high && millis()-_sensed_time>SENSOR_DELAY){
            _sensor_stage=2;
            _sensed_time=millis();
#ifndef __AVR_ATtiny85__
            Serial.println("dry!");
#endif          
        }
        break;
     case 2: //dry
        if(millis()-_sensed_time>SENSOR_DELAY){
            _sensor_stage=3;
#ifndef __AVR_ATtiny85__
          Serial.println("sing!");
#endif
        }
        break;
     case 3: //sing
        playSong();

        _step=constrain(_step-10,80,240);
        _rest=_step/2;
        break;
  }
  
}

void shuffleSongOrder(){

  for(int a=0;a<MSONG;a++){
    int r=random(a,MSONG);
    int temp=_song_order[a];
    _song_order[a]=_song_order[r];
    _song_order[r]=temp;
  }
}

