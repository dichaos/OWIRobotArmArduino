#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS1 = Adafruit_MotorShield(0x61);
Adafruit_DCMotor *myMotor5 = AFMS1.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS1.getMotor(3);
Adafruit_DCMotor *myMotor1 = AFMS1.getMotor(3);

Adafruit_MotorShield AFMS2 = Adafruit_MotorShield(0x62); 
Adafruit_DCMotor *myMotor3 = AFMS2.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS2.getMotor(4);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("OWI robot arm test");

  Serial.println("Begin motor shield 1");
  Serial.flush();
  AFMS1.begin();
  Serial.println("Begin motor shield 2");
  Serial.flush();
  AFMS2.begin();
  Serial.println("Ready");
  Serial.flush();
}

void MoveForward(class Adafruit_DCMotor &motor) {
  motor.run(FORWARD);
  motor.setSpeed(255); 
  delay(100); 
  motor.run(RELEASE);
}

void MoveBackwords(class Adafruit_DCMotor &motor) {
  uint8_t i;
  motor.run(BACKWARD);
  motor.setSpeed(255);

  
  delay(100); 
  motor.run(RELEASE);
}

void Stop(class Adafruit_DCMotor &motor) {
  motor.setSpeed(0);  
  motor.run(RELEASE);
}

void loop() {

  if (Serial.available() > 0) {
   
    // read the incoming byte:
    byte incomingByte = Serial.read();
    int command = incomingByte;
    Serial.print(command);
    
    switch(command){
      case 1:
        Serial.println(" Received - Motor 1 forward");
        MoveForward(*myMotor1);
        break;
      case 2:
        Serial.println(" Received - Motor 1 backward");
        MoveBackwords(*myMotor1);
        break;
      case 3:
        Serial.println(" Received - Motor 2 forward");
        MoveForward(*myMotor2);
        break;
      case 4:
        Serial.println(" Received - Motor 2 backward");
        MoveBackwords(*myMotor2);
        break;
      case 5:
        Serial.println(" Received - Motor 3 forward");
        MoveForward(*myMotor3);
        break;
      case 6:
        Serial.println(" Received - Motor 3 backward");
        MoveBackwords(*myMotor3);
        break;
      case 7:
        Serial.println(" Received - Motor 4 forward");
        MoveForward(*myMotor4);
        break;
      case 8:
        Serial.println(" Received - Motor 4 backward");
        MoveBackwords(*myMotor4);
        break;
      case 9:
        Serial.println(" Received - Motor 5 forward");
        MoveForward(*myMotor5);
        break;
      case 10:
        Serial.println(" Received - Motor 5 backward");
        MoveBackwords(*myMotor5);
        break;
      default:
        Serial.println("Stop all");
        Stop(*myMotor1);
        Stop(*myMotor2);
        Stop(*myMotor3);
        Stop(*myMotor4);
        Stop(*myMotor5);
        break;
    }
  }

  delay(10);
}
