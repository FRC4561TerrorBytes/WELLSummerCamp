#include <AFMotor.h> // See https://learn.adafruit.com/adafruit-motor-shield/af-dcmotor-class for docs on this library

AF_DCMotor motorL(1);
AF_DCMotor motorR(2);

// The setup method runs when the Arduino boots up.
void setup() {
  Serial.begin(9600);
  Serial.println("Serial comms established");
  
  motorR.setSpeed(0);
  motorR.run(FORWARD);
  motorL.setSpeed(0);
  motorL.run(FORWARD);
  
  Serial.println("Robot booted.");
  
  drive(255, 255);
}

// The loop method runs over and over after the setup method is complete.
void loop() {
}

// drive method: sets left motor to speedL and right motor to speedR
// speedL: -255...255 - speed to set left motor to
// speedR: -255...255 - speed to set right motor to
// usage: drive(speed to set left motor to, speed to set right motor to);
void drive(int speedL, int speedR) {
  // Debug print: format: "Driving motors: speedL, speedR"
  Serial.print("Driving motor: ");
  Serial.print(speedL);
  Serial.print(", ");
  Serial.println(speedR);
  
  // For the left motor...
  if (speedL > 0) {       // If speedL is positive, then...
    motorL.run(FORWARD);  // set the left motor to run forward.
  } else {                // Otherwise it must be negative or 0, so...
    speedL = -speedL;     // make speedL positive instead and...
    motorL.run(BACKWARD); // set the left motor to run backward.
  }
  motorL.setSpeed(speedL); // Either way, set the speed based on the number given.
  
  
  // For the right motor...
  if (speedR > 0) {       // If speedR is positive, then...
    motorR.run(FORWARD);  // set the right motor to run forward.
  } else {                // Otherwise it must be negative or 0, so...
    speedR = -speedR;     // make speedR positive instead and...
    motorR.run(BACKWARD); // set the right motor to run backward.
  }
  motorR.setSpeed(speedR); // Either way, set the speed based on the number given.
}
