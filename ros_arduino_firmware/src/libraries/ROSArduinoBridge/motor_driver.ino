/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE
   
#ifdef POLOLU_VNH5019
  /* Include the Pololu library */
  #include "DualVNH5019MotorShield.h"

  /* Create the motor driver object */
  DualVNH5019MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined POLOLU_MC33926
  /* Include the Pololu library */
  #include "DualMC33926MotorShield.h"

  /* Create the motor driver object */
  DualMC33926MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined ARDUINO_MOTOR_SHIELD_R3
  /* Include the pin definitions for the shield */
  #include "arduino_motor_shield_r3.h"
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    // Set up Channel A - LEFT
    pinMode(LEFT_MOTOR_PIN_DIR, OUTPUT); // Initiates Motor Channel A pin
    pinMode(LEFT_MOTOR_PIN_BRAKE, OUTPUT); // Initiates Brake Channel A pin

    // Set up Channel B - RIGHT
    pinMode(RIGHT_MOTOR_PIN_DIR, OUTPUT); // Initiates Motor Channel B pin
    pinMode(RIGHT_MOTOR_PIN_BRAKE, OUTPUT);  // Initiates Brake Channel B pin
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) {
      if (spd < 0) digitalWrite(LEFT_MOTOR_PIN_DIR, LOW);
      else digitalWrite(LEFT_MOTOR_PIN_DIR, HIGH);

      if (spd == 0) digitalWrite(LEFT_MOTOR_PIN_BRAKE, HIGH);
      else digitalWrite(LEFT_MOTOR_PIN_BRAKE, LOW);

      analogWrite(LEFT_MOTOR_PIN_SPEED, spd);
    }
    else {
      if (spd < 0) digitalWrite(RIGHT_MOTOR_PIN_DIR, LOW);
      else digitalWrite(RIGHT_MOTOR_PIN_DIR, HIGH);
      
      if (spd == 0) digitalWrite(RIGHT_MOTOR_PIN_BRAKE, HIGH);
      else digitalWrite(RIGHT_MOTOR_PIN_BRAKE, LOW);
      
      analogWrite(RIGHT_MOTOR_PIN_SPEED, spd);
    }
  }

  /* A convenience function for setting both motor speeds */
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }

/* For testing only! */
#elif defined(NO_MOTOR_CONTROLLER)
  /* Wrap the motor driver initialization */
  void initMotorController() { }
  
  /* A convenience function for setting both motor speeds */
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) {}
    else {}
  }
#else
  //#error A motor driver must be selected!
#endif

#endif

