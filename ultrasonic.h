

long microsecondsToCentimeters(long microseconds) {
   return microseconds *340/20000*2;
   
}

long measureDistance(int pingPin, int echoPin){
   long duration,cm, percentage;
   long length = 0;

   pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);
   for(int i = 0; i < 3; i++){
     digitalWrite(pingPin, LOW);
     delayMicroseconds(2);
     digitalWrite(pingPin, HIGH);
     delayMicroseconds(10);
     digitalWrite(pingPin, LOW);
     duration =pulseIn(echoPin, HIGH);
     length = length + microsecondsToCentimeters(duration);
     delay(100);
   }

   //Serial.print(length/4);
  
   return length/6;
}
