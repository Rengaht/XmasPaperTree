#define SPEAKER_PIN 1
#define SENSOR_PIN 0

#define LED_PIN_1 2
#define LED_PIN_2 3
#define LED_PIN_3 4

#define NOTE_C  239
#define NOTE_CS 225
#define NOTE_D  213
#define NOTE_DS 201
#define NOTE_E  190
#define NOTE_F  179
#define NOTE_FS 169
#define NOTE_G  159
#define NOTE_GS 150
#define NOTE_A  142
#define NOTE_AS 134
#define NOTE_B 127

bool _sing=false;
bool _water=false;

void setup(){

  pinMode(SPEAKER_PIN,OUTPUT);
  pinMode(LED_PIN_1,OUTPUT);
  pinMode(LED_PIN_2,OUTPUT);
  pinMode(LED_PIN_3,OUTPUT);

  pinMode(SENSOR_PIN,INPUT);

  
  
}

void loop(){

  if(!_sing){
    bool _high=(digitalRead(SENSOR_PIN)==HIGH);
    if(!_water && _high){
      _water=true;    
      return;
    }
    if(_water && !_high) _sing=true;
  }else{
    playTone();
    delay(500);    
  }
  
}
