
#define BLYNK_PRINT Serial
#define ESP8266_BAUD 9600
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>

#include <SimpleTimer.h>
#include "BatteryMonitoring.h"
#include "ultrasonic.h"
#include "fireDetection.h"


// Wifi set up
char auth[] = "RSx1KIq8WZ-0qZdtU9JJ8uN4_aDP8alD";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi";
char pass[] = "12345678";

//esp8266 set up
SoftwareSerial EspSerial(2, 4); // RX, TX
ESP8266 wifi(&EspSerial);
WidgetLED green(V1);
WidgetLED orange(V2);
WidgetLED red(V3);
WidgetLED fireled(V4);

char displaybat = V5;
char displaytrash = V11;
char resettime = V9;

char lengthbin = V12;
long previoustime = 2000;
long defaulttime = 2000;
long currTime = 2000;

// There must be one global SimpleTimer object.
SimpleTimer timer;
int timerid;
const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

const int redled = 7; // Led
const int orangeled = 8;

const int greenled = 9;
const int buzzer = 3;
const int resetswitch = 12;
const int transwitch = 10;


int buttonState = 0;  
//2,4 for rx,tx
//output for gate

// Analog in
const int CarbonPin = 5;
const int BatteryPin = 4;
const int temp = 3;

int hour = 0;
long total = 100;
int sensorValue;

void repeatHour(){
  float percentage = 0;
  digitalWrite(redled,LOW);
  digitalWrite(orangeled,LOW);
  digitalWrite(greenled,LOW);
  green.off();
  orange.off();
  red.off();
  
  long x = measureDistance(pingPin, echoPin);
  percentage = (float)x/total*100;
  percentage = 100 - percentage;

  // Map percentages
  if(percentage >= 80){
    digitalWrite(redled,HIGH);
    red.on();
    delay(10000);
  }else if( 50 < percentage && percentage < 80){
    digitalWrite(orangeled,HIGH);
    orange.on();
    delay(10000);
  }else if (percentage <= 50){
    digitalWrite(greenled,HIGH);  
    green.on();
    delay(10000);
  }

  if(percentage < 0) percentage = 0;
  Blynk.virtualWrite(displaytrash,percentage);
  hour++;

  // If counter hits 24 it gets battery reading daily
  if(hour == 24){
    hour = 0;
    digitalWrite(transwitch ,HIGH);
    delay(2000);
    long level = batteryMonitoring(BatteryPin);
    
    digitalWrite(transwitch,LOW);
    delay(1000);
    Blynk.virtualWrite(displaybat,level);
  }

}


void setup() {
    Serial.begin(9600); // Starting Serial Terminal
    pinMode(redled,OUTPUT);
    pinMode(orangeled,OUTPUT);
    pinMode(greenled,OUTPUT);
    pinMode(resetswitch, INPUT);
    pinMode(transwitch, INPUT);
    pinMode(buzzer,OUTPUT); 
    pinMode(LED_BUILTIN, OUTPUT);
    timerid = timer.setInterval(defaulttime, repeatHour);
    wifi_setup();
    Blynk.virtualWrite(lengthbin,100);
   

}

void wifi_setup(){
    EspSerial.begin(ESP8266_BAUD);
    Blynk.begin(auth, wifi, ssid, pass);
    Blynk.run();
}

// looping
void loop(){   
    Blynk.run();
    timer.run();
    
    if (fireDetection(CarbonPin)){
      tone(buzzer,4000);
      fireled.on();
      delay(2000);    
    }else{
      noTone(buzzer);
      fireled.off();
    }
    
 
    // Calibration bin level code 
    if(currTime != previoustime){
        timer.deleteTimer(timerid);
        timerid = timer.setInterval(currTime,repeatHour);
        previoustime = currTime;
    }
    
    buttonState = digitalRead(resetswitch);
    if ( buttonState == HIGH){
      delay(1);
      tone(buzzer, 1000);
      total =  measureDistance(pingPin, echoPin);
      Blynk.virtualWrite(lengthbin,total);
      noTone(buzzer);
    } 
}


BLYNK_WRITE(V9)
{
    currTime = (param.asInt());
    currTime = currTime*defaulttime; 

}



  
