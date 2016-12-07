

void singleTone(unsigned char divisor, unsigned char octave, unsigned long duration,int light_1,int light_2,int light_3){
  
  
  TCCR1 = 0x90 | (8-octave); // for 1MHz clock
  // TCCR1 = 0x90 | (11-octave); // for 8MHz clock
  OCR1C = divisor-1;         // set the OCR
  
  if(light_1==1) digitalWrite(LED_PIN_1,HIGH);
  if(light_2==1) digitalWrite(LED_PIN_2,HIGH);
  if(light_3==1) digitalWrite(LED_PIN_3,HIGH);
 
  delay(duration);
  
  if(light_1==1) digitalWrite(LED_PIN_1,LOW);
  if(light_2==1) digitalWrite(LED_PIN_2,LOW);
  if(light_3==1) digitalWrite(LED_PIN_3,LOW);
  
  TCCR1 = 0x90;              // stop the counter
  
}

void playTone(){
  
  singleTone(NOTE_C, 4, 500, 1,0,0);
  singleTone(NOTE_D, 4, 500, 0,1,0);
  singleTone(NOTE_E, 4, 500, 0,0,1);
  singleTone(NOTE_F, 4, 500, 0,1,0);
  singleTone(NOTE_G, 4, 500, 1,0,0);
  singleTone(NOTE_A, 4, 500, 0,1,0);
  singleTone(NOTE_B, 4, 500, 0,0,1);
  singleTone(NOTE_C, 5, 500, 1,1,1);  
  
}

