
  long batteryMonitoring(int pin){
    
    float batterycent = 0;
    float batterylevel = analogRead(pin);       // read analog input pin 0
     
   //Serial.println(batterylevel, DEC);

    float batterylevel1 = batterylevel/1024*5;
    //Serial.println(batterylevel1);
    //return (long) batterylevel1;
    //Serial.println(batterylevel1, DEC);  // prints the value read

    batterylevel = batterylevel1*3; // converts to origina
    //Serial.println(batterylevel);
    if(batterylevel >= 9){
        //Serial.println("hgfds");
        batterycent = 95;
    }else if ( 9 >= batterylevel && batterylevel >= 7.2){
        batterycent = batterylevel/9*100;
        //(long)(batterylevel/9);

        
      
    } else if (7 <= batterylevel && batterylevel <= 7.4){
       batterycent = 50;
        
       
      
    }else if (5.4 <= batterylevel && batterylevel <= 7){
       batterycent = 40;
    }else{
      batterycent = 0;
      Serial.println("batterylevel");
    }
    
    
    
    //Serial.println(batterycent, DEC);

    // 
    // Note volatge is divider by 3
    // 
    
    // map values 
    
    delay(100);  
    //Serial.println(batterycent, DEC);
    return batterycent;
  }
  
