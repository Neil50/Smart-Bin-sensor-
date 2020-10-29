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

char displaybat = V10;


// There must be one global SimpleTimer object.
SimpleTimer timer;
const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

const int led0 = 7; // Led
const int led1 = 8;

const int led2 = 9;
const int buzzer = 3;
const int switch1 = 12;
const int transwitch = 10;



int buttonState = 0;  
//2,4 for rx,tx
//output for gate

// Analog in
const int CarbonPin = 5;
const int BatteryPin = 4;


long high = 80;
long medium = 50;
long low = 10;
int total = 100;


int hour = 0;
int sensorValue;

void repeatHour(){
  //wifi_setup();
  long percentage = 0;
  digitalWrite(led0,LOW);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  green.off();
  orange.off();
  red.off();
 
  //Need to calibrate measurements 
  //for ( int i = 0; i < 2; i++){
  //  percentage = percentage + measureDistance(pingPin, echoPin);
  //  
  //}
  //percentage = percentage/(total*2);
  percentage = measureDistance(pingPin, echoPin)/total;

  if(percentage >= 0.8){
    =
    digitalWrite(led0,HIGH);
    green.on();
    delay(10000);
 
  }else if( 0.5 < percentage & percentage < 0.75){
    digitalWrite(led1,HIGH);
  ;
    orange.on();
    delay(10000);
  
  }else{
    digitalWrite(led2,HIGH);  
  
    red.on();
    delay(10000);
  }
  
  
  hour++;
  if(hour == 24){
    hour = 0;
    long level = batteryMonitoring(BatteryPin);
    Blynk.virtualWrite(displaybat,level);
    
  }
  // battery monitoring and wifi
}

void setup() {
    Serial.begin(9600); // Starting Serial Terminal
    pinMode(led0,OUTPUT);
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    pinMode(switch1, INPUT);
    pinMode(buzzer,OUTPUT); 
    // need to fix simple timer 
    //timer.setInterval(1, repeatHour);
    wifi_setup();

}

void wifi_setup(){
    EspSerial.begin(ESP8266_BAUD);
    Blynk.begin(auth, wifi, ssid, pass);
    Blynk.run();
}

// looping
void loop(){
    //repeatHour();
    if (fireDetection(CarbonPin)){
      tone(buzzer,1000);
      fireled.on();
      delay(2000);    
    }else{
      noTone(buzzer);
      fireled.off();
    }
   //Serial.print(buttonState);
   Serial.print(measureDistance(pingPin, echoPin));
    buttonState = digitalRead(switch1);
    //Serial.print(buttonState);
    if ( buttonState == HIGH){
      total = measureDistance(pingPin, echoPin);
      

      Serial.print("HIGH");
    }

    if (buttonState== LOW){
      Serial.print("LOW");
    }
 
}




  
