#include <AFMotor.h> // See https://learn.adafruit.com/adafruit-motor-shield/af-dcmotor-class for docs on this library
#include <SoftwareSerial.h>

AF_DCMotor motorL(1); 
AF_DCMotor motorR(2);

SoftwareSerial wireless (A0,A1);

void setup() {
  wireless.begin(9600); // Enable wireless communications over Bluetooth
  wireless.print("wireless comms established.");
  
  motorR.setSpeed(0);
  motorR.run(FORWARD);
  motorL.setSpeed(0);
  motorL.run(FORWARD);
  
  wireless.println("Robot booted.");
}

void loop() {
  while(wireless.available()) {
    int input = wireless.read();
    if(input == 'w' || input == 'W') { 
        drive(255, 255);  // w = forward
    }
    else if(input == 's' || input == 'S') { 
      drive(-255, -255);  // s = back
    }
    else if(input == 'a' || input == 'A') { 
      drive(-255, 255);  // a = hard left (both wheels)
    }
    else if(input == 'd' || input == 'D' ) { 
      drive(255, -255);  // d = hard right (both wheels)
    }
  }
}

void drive(int speedL, int speedR) {
  wireless.print("Driving motor: ");
  wireless.print(speedL);
  wireless.print(", ");
  wireless.println(speedR);
  
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
