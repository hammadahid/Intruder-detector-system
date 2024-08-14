#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

const int ledPin1 = 3;// the number of the LED pin
const int ledPin2 = 4;

// Ultrasonic sensor
const int trig_Pin = 6;
const int echo_Pin = 5;
int distance = 0;
long duration = 0;

// Variables will change:
int ledState = LOW;            

unsigned long previousMillis = 0;        
const long interval = 450000;
int N_detect = 0;


void setup() {
  // set the digital pin as output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(trig_Pin, OUTPUT);
  pinMode(echo_Pin, INPUT);
  // For GSM Module
  Serial.begin(9600);
  while (!Serial.available()){
    Serial.println("AT");
    delay(1000);
    Serial.println("Connecting....");
  }
  Serial.println("Connected!");
  Serial.println("AT+CMGF=1"); // Set to sms mode
  delay(1000);
  Serial.println("AT+CNMI=1,2,0,0,0");
  delay(1000);
  Serial.println("AT+CMGL = \"REC UNREAD\"");

  // GSM NUMBER SETUP
  Serial.print("AT+CMGS=\"+2348181265913\"\r\n");
  delay(1000);
  String dataMessage = ("INTRUDER DETECTION SYSTEM ACTIVE");
  Serial.print(dataMessage);
  delay(100);
  Serial.print((char)26);
  delay(1000);


}

void loop() {
   // Ultrasonic Sensor
  digitalWrite(trig_Pin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_Pin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo_Pin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 50){
   Serial.println("INTRUDER DETECTED");
   digitalWrite(ledPin1, HIGH);
   N_detect += 5;
   if (N_detect == 10){
    digitalWrite(ledPin2, HIGH);
    String dataMessage = ("INTRUDER DETECTED");
    Serial.print(dataMessage);
    delay(100);
    Serial.print((char)26);
    delay(1000);
   }
   digitalWrite(ledPin2, LOW);
  }
  if (distance > 50){
    digitalWrite(ledPin1,LOW);
    N_detect = 5;
  }

 delay(1000);
  
}


