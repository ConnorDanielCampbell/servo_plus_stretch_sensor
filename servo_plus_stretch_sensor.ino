#include <Servo.h> 

Servo myservo;

const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

const int sensorPin = A0;  

int sensorValue = 0;         // the sensor value
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value


void setup() {
  myservo.attach(9);
  
  Serial.begin(9600);                   
      
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // calibrate during the first five seconds 
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  // signal the end of the calibration period
  digitalWrite(13, LOW);
}

void loop() {
  // read the sensor:
  sensorValue = analogRead(sensorPin);

  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 100);
//
//  // in case the sensor value is outside the range seen during calibration
  sensorValue = constrain(sensorValue, 0, 100);

  if(sensorValue > 50)
    {
      myservo.write(180);  
    }
    
  if(sensorValue <= 50)
    {
      myservo.write(0);
    }
  
  delay(100);   
}
