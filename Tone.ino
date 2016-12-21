

void singleTone(int note, int duration,unsigned int rest,int light_mode){


  unsigned char octave=(note>10)?5:4;  
  unsigned char divisor=_freq[note];

#ifdef __AVR_ATtiny85__
  TCCR1 = 0x90 | (8-octave); // for 1MHz clock
  // TCCR1 = 0x90 | (11-octave); // for 8MHz clock
  OCR1C = divisor-1;         // set the OCR
#else
    Serial.println(divisor);    
#endif

  int num=(int)(duration/_step);
  
  //light_mode=8;
  
  switch(light_mode){
    case 1:
      digitalWrite(LED_PIN[0],HIGH);
      delay(duration*_step);
      digitalWrite(LED_PIN[0],LOW);
//      delay(duration/2);
      break;
    case 2:    
      digitalWrite(LED_PIN[1],HIGH);
      delay(duration*_step);
      digitalWrite(LED_PIN[1],LOW);
//      delay(duration/2);
      break;
    case 4:
      digitalWrite(LED_PIN[2],HIGH);
      delay(duration*_step);
      digitalWrite(LED_PIN[2],LOW);
//      delay(duration/2);
      break;


    case 3:
      digitalWrite(LED_PIN[0],HIGH);
      digitalWrite(LED_PIN[1],HIGH);
      delay(duration*_step);
      digitalWrite(LED_PIN[0],LOW);
      digitalWrite(LED_PIN[1],LOW);
//      delay(duration/2);
      break;
   case 6:
      digitalWrite(LED_PIN[1],HIGH);
      digitalWrite(LED_PIN[2],HIGH);
      delay(duration*_step);
      digitalWrite(LED_PIN[1],LOW);
      digitalWrite(LED_PIN[2],LOW);
//      delay(duration/2);
      break;
   case 5:
      digitalWrite(LED_PIN[0],HIGH);
      digitalWrite(LED_PIN[2],HIGH);
      delay(duration*_step);
      digitalWrite(LED_PIN[0],LOW);
      digitalWrite(LED_PIN[2],LOW);
//      delay(duration/2);
      break;
   
    
    case 7:
      digitalWrite(LED_PIN[0],HIGH);
      digitalWrite(LED_PIN[1],HIGH);
      digitalWrite(LED_PIN[2],HIGH);
      delay(duration*_step);
      digitalWrite(LED_PIN[0],LOW);
      digitalWrite(LED_PIN[1],LOW);
      digitalWrite(LED_PIN[2],LOW);
//      delay(duration/2);      
      break;
    case 8:
      for(int i=0;i<duration*2;++i){      
       
        digitalWrite(LED_PIN[0],LOW);
        digitalWrite(LED_PIN[1],LOW);
        digitalWrite(LED_PIN[2],LOW);
        delay(_step/4); 

        digitalWrite(LED_PIN[0],HIGH);
        digitalWrite(LED_PIN[1],HIGH);
        digitalWrite(LED_PIN[2],HIGH);
        delay(_step/4);
      }
      
      delay((duration*_step)%(_step/2));
      digitalWrite(LED_PIN[0],LOW);
      digitalWrite(LED_PIN[1],LOW);
      digitalWrite(LED_PIN[2],LOW);
      break;
  }
 
  
  
#ifdef __AVR_ATtiny85__
  TCCR1 = 0x90;              // stop the counter
#endif
  
  delay(rest);
  
}

void playSong(){
    
    int len_=0;
    
    switch(_song_order[_song_index]){
      case 0:         
        len_=27;
        for(int i=0;i<len_;++i){
          singleTone(int(_song_1[i]&0xF0)/16,int(_due_1[i]&0xF0)/16,_rest,int(_light_1[i]&0xF0)/16);      
          singleTone(int(_song_1[i]&0x0F),int(_due_1[i]&0x0F),_rest,int(_light_1[i]&0x0F));      
        } 
        break;
      case 1:
   
        len_=26;
        for(int i=0;i<len_;++i){
          singleTone(int(_song_2[i]&0xF0)/16,int(_due_2[i]&0xF0)/16,_rest,int(_light_2[i]&0xF0)/16);      
          singleTone(int(_song_2[i]&0x0F),int(_due_2[i]&0x0F),_rest,int(_light_2[i]&0x0F));      
        }
        break;
      case 2:
        len_=29;
        for(int i=0;i<len_;++i){
            singleTone(int(_song_3[i]&0xF0)/16,int(_due_3[i]&0xF0)/16,_rest,int(_light_3[i]&0xF0)/16);      
            singleTone(int(_song_3[i]&0x0F),int(_due_3[i]&0x0F),_rest,int(_light_3[i]&0x0F));  
        }
        break; 
//     case 3:
//        len_=55;
//        for(int i=0;i<len_;++i){
//            singleTone(int(_song_4[i]&0xF0)/16,int(_due_4[i]&0xF0)/16*_step,_rest,int(_light_4[i]&0xF0)/16);      
//            singleTone(int(_song_4[i]&0x0F),int(_due_4[i]&0x0F)*_step,_rest,int(_light_4[i]&0x0F));  
//        }
//        break;
    }
   
    delay(100);

    if(_song_index==MSONG-1) shuffleSongOrder();  
    _song_index=(_song_index+1)%MSONG;
   
}

