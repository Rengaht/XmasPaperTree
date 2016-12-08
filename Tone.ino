

void singleTone(int note, unsigned int duration,unsigned int rest,int light_mode){


  unsigned char octave=(note>10)?5:4;  
  unsigned char divisor=_freq[note];

#ifdef __AVR_ATtiny85__
  TCCR1 = 0x90 | (8-octave); // for 1MHz clock
  // TCCR1 = 0x90 | (11-octave); // for 8MHz clock
  OCR1C = divisor-1;         // set the OCR
#else
    Serial.println(divisor);    
#endif

  int num=duration/_blink;
  
  switch(light_mode){
    case 1:
      digitalWrite(LED_PIN[0],HIGH);
      delay(duration);
      digitalWrite(LED_PIN[0],LOW);
//      delay(duration/2);
      break;
    case 2:    
      digitalWrite(LED_PIN[1],HIGH);
      delay(duration);
      digitalWrite(LED_PIN[1],LOW);
//      delay(duration/2);
      break;
    case 4:
      digitalWrite(LED_PIN[2],HIGH);
      delay(duration);
      digitalWrite(LED_PIN[2],LOW);
//      delay(duration/2);
      break;


    case 3:
      digitalWrite(LED_PIN[0],HIGH);
      digitalWrite(LED_PIN[1],HIGH);
      delay(duration);
      digitalWrite(LED_PIN[0],LOW);
      digitalWrite(LED_PIN[1],LOW);
//      delay(duration/2);
      break;
   case 6:
      digitalWrite(LED_PIN[1],HIGH);
      digitalWrite(LED_PIN[2],HIGH);
      delay(duration);
      digitalWrite(LED_PIN[1],LOW);
      digitalWrite(LED_PIN[2],LOW);
//      delay(duration/2);
      break;
   case 5:
      digitalWrite(LED_PIN[0],HIGH);
      digitalWrite(LED_PIN[2],HIGH);
      delay(duration);
      digitalWrite(LED_PIN[0],LOW);
      digitalWrite(LED_PIN[2],LOW);
//      delay(duration/2);
      break;
   
    
    case 7:
      digitalWrite(LED_PIN[0],HIGH);
      digitalWrite(LED_PIN[1],HIGH);
      digitalWrite(LED_PIN[2],HIGH);
      delay(duration);
      digitalWrite(LED_PIN[0],LOW);
      digitalWrite(LED_PIN[1],LOW);
      digitalWrite(LED_PIN[2],LOW);
//      delay(duration/2);      
      break;
    case 8:
      for(int i=0;i<num;++i){      
        digitalWrite(LED_PIN[0],HIGH);
        digitalWrite(LED_PIN[1],HIGH);
        digitalWrite(LED_PIN[2],HIGH);
        delay(_blink/2);
        digitalWrite(LED_PIN[0],LOW);
        digitalWrite(LED_PIN[1],LOW);
        digitalWrite(LED_PIN[2],LOW);
        delay(_blink/2);      
      }
      break;
  }
 
  
  
#ifdef __AVR_ATtiny85__
  TCCR1 = 0x90;              // stop the counter
#endif
  
  delay(rest);
  
}

void playSong(){
    
    int len_=0;
    
    switch(_song_index){
      case 0:      
        len_=27;
        for(int i=0;i<len_;++i){
          singleTone(int(_song_1[i]&0xF0)/16,int(_due_1[i]&0xF0)/16*_step,_rest,int(_light_1[i]&0xF0)/16);      
          singleTone(int(_song_1[i]&0x0F),int(_due_1[i]&0x0F)*_step,_rest,int(_light_1[i]&0x0F));      
        } 
        break;
      case 1:
        len_=26;
        for(int i=0;i<len_;++i){
          singleTone(int(_song_2[i]&0xF0)/16,int(_due_2[i]&0xF0)/16*_step,_rest,int(_light_2[i]&0xF0)/16);      
          singleTone(int(_song_2[i]&0x0F),int(_due_2[i]&0x0F)*_step,_rest,int(_light_2[i]&0x0F));      
        }
        break;
      case 2:
        len_=29;
        for(int i=0;i<len_;++i){
            singleTone(int(_song_3[i]&0xF0)/16,int(_due_3[i]&0xF0)/16*_step,_rest,int(_light_3[i]&0xF0)/16);      
            singleTone(int(_song_3[i]&0x0F),int(_due_3[i]&0x0F)*_step,_rest,int(_light_3[i]&0x0F));  
        }
        break; 
     case 3:
        len_=55;
        for(int i=0;i<len_;++i){
            singleTone(int(_song_4[i]&0xF0)/16,int(_due_4[i]&0xF0)/16*_step,_rest,int(_light_4[i]&0xF0)/16);      
            singleTone(int(_song_4[i]&0x0F),int(_due_4[i]&0x0F)*_step,_rest,int(_light_4[i]&0x0F));  
        }
        break;
    }
    delay(100);

    _song_index=(_song_index+1)%MSONG;
    if(_song_index==MSONG-1) shuffleSongOrder();
}

