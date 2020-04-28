#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("OWI robot arm test");

  AFMS.begin();

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


    switch(command){
      case 1:
        Serial.write("Motor 1 forward");
        MoveForward(*myMotor1);
        break;
      case 2:
        Serial.write("Motor 1 backward");
        MoveBackwords(*myMotor1);
        break;
      case 3:
        Serial.write("Motor 2 forward");
        MoveForward(*myMotor2);
        break;
      case 4:
        Serial.write("Motor 2 backward");
        MoveBackwords(*myMotor2);
        break;
      case 5:
        Serial.write("Motor 3 forward");
        MoveForward(*myMotor3);
        break;
      case 6:
        Serial.write("Motor 3 backward");
        MoveBackwords(*myMotor3);
        break;
      case 7:
        Serial.write("Motor 4 forward");
        MoveForward(*myMotor4);
        break;
      case 8:
        Serial.write("Motor 4 backward");
        MoveBackwords(*myMotor4);
        break;
      default:
        Serial.write("Stop all");
        Stop(*myMotor1);
        Stop(*myMotor2);
        Stop(*myMotor3);
        Stop(*myMotor4);
        break;
    }
  }

  delay(10);
}
