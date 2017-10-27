#include <AFMotor.h> // See https://learn.adafruit.com/adafruit-motor-shield/af-dcmotor-class for docs on this library

AF_DCMotor motorL(1); // Left motor on shield port 1
AF_DCMotor motorR(2); // Right motor on shield port 2
// This creates two motors objects, called motorL and motorR and assigns them to their ports.
// To create motors, do: AF_DCMotor myMotorName(portThatMyMotorIsOn);
// Motor port numbers can be found next to each port on the motor shield.

// Helper variables for autostop
int delayTime = 230;
float wPressTime;
float aPressTime;
float sPressTime;
float dPressTime;

float matchStartTime;

boolean teleopOnlyMode = true;

int driveSpeed = 255;

float leftCoefficient = 1.0;
float rightCoefficient = 1.0;

float AUTONOMOUS_LENGTH = 15000;
float TELEOP_LENGTH = 135000;
boolean matchOver = false;

// The setup method runs when the Arduino boots up.
void setup() {
  Serial.begin(9600); // Enable serial communications over the USB cable
  // This allows the Arduino to talk to the computer. The 9600 is called the "baud rate".
  // More on this method here: https://www.arduino.cc/en/Serial/Begin 
  
  Serial.println("Serial comms established.");
  // This is a print statement. It writes the string (a series of characters) onto the computer screen.
  // The quotes are required.
  
  
  // Start with motors off
  motorR.setSpeed(0); // Make sure right motor speed is 0
  motorR.run(FORWARD); // Make sure right motor is set to go forward
  motorL.setSpeed(0); // Make sure left motor speed is 0
  motorL.run(FORWARD); // Make sure right motor is set to go forward
  // Above, we make certain that the motors aren't moving.
  // The first method, setSpeed, takes a positive value between 0 and 255, with 0 being off and 255 being the fastest.
  // This means setSpeed cannot control the direction, only the speed.
  // Usage: myMotor.setSpeed(aNumberBetween0and255);
  // The second method, run, sets the direction that the motor moves.
  // Usage: myMotor.run(FORWARD) or myMotor.run(BACKWARD)
  
  Serial.println("Robot booted."); // Setup Complete
  
  if(!teleopOnlyMode) { // If in match mode
    waitForMatchStart(); // Wait until the button is pressed to start the match.
    autonomous(); // Now that the match has started, begin autonomous.
    waitForAutonomousEnd(); // Once the autonomous routine has finished, wait until the 15 seconds are up
  }
} // End of setup method

// The loop method runs over and over after the setup method is complete.
void loop() {
  if(!matchOver) {
    while(Serial.available()) { // Check to see if there is a new character on the serial port (check if the driver has pressed a button). If there is...
      // Above is a while loop. It exectutes all code in its block until its condition becomes false.
      // This one will repeat until there are no more new characters on the serial port.
      // Its condition is Serial.available(), which equals true if there are new characters, and false if there aren't
      // To create a while loop, do: while(condition) {stuff to do}
      
      int input = Serial.read(); // assign the character to the variable input
      // Above, we assigned the int variable input to a character.
      // In Arduino and many other programming languages, characters can be stored as numbers.
      // The number that each character turns into can be found here: http://www.danshort.com/ASCIImap/ 
      
      // Drive the motors based on the character.
      if(input == 'w' || input == 'W') { 
        wPressTime = millis();
        drive(driveSpeed, driveSpeed);  // w = forward
      }
      else if(input == 's' || input == 'S') { 
        sPressTime = millis();
        drive(-driveSpeed, -driveSpeed);  // s = back
      }
      else if(input == 'a' || input == 'A') { 
        aPressTime = millis();
        drive(-driveSpeed, driveSpeed);  // a = hard left (both wheels)
      }
      else if(input == 'd' || input == 'D' ) { 
        dPressTime = millis();
        drive(driveSpeed, -driveSpeed);  // d = hard right (both wheels)
      }
      // Above, we use if and else if statements to determine which character input is.
      // The "==" means "is equal to". The "||" means "or".
      // Therefore, if(input == 'w' || input == 'W') {stuff} means "if input is equal to w or W, do stuff."
      // If an else if statement executes, all else if statements after it will be skipped. This doesn't happen with if statements.
    }
    // Checks to see if any keys have been hit for delayTime. If not, stop the bot.
    if(wPressTime+delayTime < millis() && sPressTime+delayTime < millis() && aPressTime+delayTime < millis() && dPressTime+delayTime < millis()) {
      drive(0, 0);
    }
    if(isTeleopOver() && !teleopOnlyMode) { matchOver = true; }
  }
  else {
    drive(0, 0);
  }
  Serial.println(matchOver);
}

// The autonomous method should run once the match start button is pressed.
void autonomous() {
  // Use the driveTimed method here to create an autonomous routine.
}

// Do not edit the methods below without permission, they're critical to make sure your robot works as intended.

// drive method: sets left motor to speedL and right motor to speedR
// speedL: -255...255 - speed to set left motor to
// speedR: -255...255 - speed to set right motor to
// Usage: drive(speed to set left motor to, speed to set right motor to);
void drive(int speedL, int speedR) {
  speedL = speedL * leftCoefficient;
  speedR = speedR * rightCoefficient;
  // Debug print: "Driving motors: speedL, speedR"
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

// Just like the drive method, except you can set it to stop after a number of seconds.
// Remember that the speeds have to be between -255 and 255.
// Usage: driveTimed(leftMotorSpeed, rightMotorSpeed, secondsToRunBeforeStopping);
void driveTimed(byte speedL, byte speedR, float seconds) {
  drive(speedL, speedR);
  delay(seconds*1000);
  drive(0, 0);
}

// Helper method to wait until the key to start the match is pressed.
void waitForMatchStart() {
  Serial.flush();
  int input;
  while(input != 'p') {
    if(Serial.available()) {
      input = Serial.read();
    }
  }
  matchStartTime = millis();
}

// Helper method to wait until autonomous mode is over.
void waitForAutonomousEnd() {
  while(matchStartTime + AUTONOMOUS_LENGTH > millis()) { }
}

boolean isTeleopOver() {
  if(matchStartTime + AUTONOMOUS_LENGTH + TELEOP_LENGTH < millis()) { return true; }
  return false;
}
