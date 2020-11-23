  
  boolean fireDetection(int pin){
    int sensorValue = analogRead(pin); 
    // read analog input pin 0
    delay(100);  
    Serial.println(sensorValue, DEC);
    if (sensorValue > 400){
      return true;
    }else{
      return false;
    }
  }
  
