#include <Servo.h>
const int trigPin1 = 5;      // Define trigger and echo pins of Ultrasonic Sensors
const int echoPin1 = 4;
const int trigPin2 = 7;
const int echoPin2 = 6;
const int trigPin3 = 9;
const int echoPin3 = 8;
Servo servoMotor;
Servo servoLeft;            // Declare left and right servos
Servo servoRight;
int info = 0;         //variable for the information comming from the bluetooth module
int state = 0;       //simple variable for displaying the state
int fsr1 = A0;  // Analog Pins for FSR Sensors
int fsr2 = A1;
int fsr3 = A2;
int fsrReading1 = 0;
int fsrReading2 ;
int fsrReading3 ;
long duration1, duration2, duration3 ;
int distance1, distance2, distance3;
void setup()
{
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
void loop() {

  if (Serial.available() > 0) { //if there is any information comming from the serial lines...
    info = Serial.read();
    state = 0;   //...than store it into the "info" variable
  }


  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance 1 = ");
  Serial.print(distance1);
  Serial.print(" cm");
  Serial.print("|");
  delay(300);


  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance 2 = ");
  Serial.print(distance2);
  Serial.print(" cm");
  Serial.print("|");
  delay(300);

  // Clears the trigPin
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration3 = pulseIn(echoPin3, HIGH);
  // Calculating the distance
  distance3 = duration3 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance 3 = ");
  Serial.print(distance3);
  Serial.println(" cm");
  delay(300);

  fsrReading1 = analogRead(fsr1);
  //delay (100);
  fsrReading2 = analogRead(fsr2);
  //delay (100);
  fsrReading3 = analogRead(fsr3);
  //delay (100);

  Serial.print("FSR1 = ");
  Serial.print(fsrReading1);
  Serial.print(" \t ");
  Serial.print("FSR2 = ");
  Serial.print(fsrReading2);
  Serial.print(" \t ");
  Serial.print("FSR2 = ");
  Serial.print(fsrReading3);
  Serial.println("|");
  delay (300);

  if (distance1 < 10 || distance2 < 10) {
    Serial.print("Obstacle Detected");
    Serial.println(" \t ");
    servoLeft.attach(3);                      // Attach left signal to pin 3
    servoRight.attach(2);                     // Attach right signal to pin 2
    servoLeft.writeMicroseconds(1700);         // Move Right
    servoRight.writeMicroseconds(1500);
    delay (2000);
    servoLeft.detach();       //Stop Sending Signal to Servo Pin
    servoRight.detach();
  }

  else if (distance3 < 10) {
    Serial.print("Obstacle Detected");
    Serial.println(" \t ");
    servoLeft.attach(3);
    servoRight.attach(2);
    servoLeft.writeMicroseconds(1500);         // Move Left
    servoRight.writeMicroseconds(1300);
    delay (2000);
    servoLeft.detach();
    servoRight.detach();
  }
  else {
    Serial.print(" No Obstacle Detected");
    Serial.println(" \t ");
  }

  // Full speed forward
  if (fsrReading1 > 100) {
    servoLeft.attach(3);
    servoRight.attach(2);
    servoLeft.writeMicroseconds(1700);         // Left wheel  clockwise
    servoRight.writeMicroseconds(1300);        // Right wheel clockwise
    //delay(2000);
  }

  //Pivot forward-left
  else if (fsrReading2 > 100) {
    servoLeft.attach(3);
    servoRight.attach(2);
    servoLeft.writeMicroseconds(1500);         // Left wheel stop
    servoRight.writeMicroseconds(1300);        // Right wheel clockwise
    //delay(2000);
  }

  // Pivot forward-right
  else if (fsrReading3 > 100) {
    servoLeft.attach(3);                      // Attach left signal to pin 13
    servoRight.attach(2);
    servoLeft.writeMicroseconds(1700);         // Left wheel clockwise
    servoRight.writeMicroseconds(1500);        // Right wheel stop
    //delay(2000);
  }

  else {
    servoLeft.detach();
    servoRight.detach();
  }
}
