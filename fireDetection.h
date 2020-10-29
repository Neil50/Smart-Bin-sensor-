  
  boolean fireDetection(int pin){
    int sensorValue = analogRead(pin); 
    // read analog input pin 0
    //Serial.println(sensorValue, DEC);  // prints the value read
    delay(100);  

    if (sensorValue > 300){
      return true;
    }else{
      return false;
    }
  }
  
