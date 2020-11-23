
  long batteryMonitoring(int pin){
    
    float batterycent = 0;
    // read analog input pin 0
    float batterylevel = analogRead(pin);
  
    float batterylevel1 = batterylevel/1024*5;
    batterylevel = batterylevel1*3; // converts to origina

    if(batterylevel >= 9){
        batterycent = 95;
    }else if ( 9 >= batterylevel && batterylevel >= 7.2){
        batterycent = batterylevel/9*100;
        
    } else if (7 <= batterylevel && batterylevel <= 7.4){
       batterycent = 50;
        
    }else if (5.4 <= batterylevel && batterylevel <= 7){
       batterycent = 40;
    }else{
      batterycent = 0;
    }
    
    // Note volatge is divider by 3
    // map values 
    
    delay(100);  
    return batterycent;
  }
  
