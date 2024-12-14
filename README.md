# TurtleBot Motor Control
## Description
This Arduino sketch, TurtleBot_Motor_Control.ino, is designed to control the motors of a turtle-inspired robot. The robot uses joystick inputs to manage the movement of its front fins, back fins, and water pumps, enabling it to navigate and perform tasks in an aquatic environment. The code leverages the Adafruit Motor Shield library to interact with both stepper motors and DC motors.

## Hardware Components
1. Adafruit Motor Shields:
  * Two shields are used, one at I2C address 0x60 for stepper motors and the other at 0x61 for DC motors.
2. Motors:
  * Stepper Motors:
    * myStepper1: Front fin motor (port 1 on the stepper motor shield).
    * myStepper2: Front fin motor (port 2 on the stepper motor shield).
  * DC Motors:
    * myMotor1 and myMotor4: Control water pumps.
    * myMotor2 and myMotor3: Control back fins.
3. Joystick Input Pins:
  * PWM_PIN1: Left joystick vertical axis (back fins).
  * PWM_PIN2: Right joystick horizontal axis (water pumps).
  * PWM_PIN3: Right joystick vertical axis (front fins).
  * PWM_PIN4: Left joystick horizontal axis (unused).
 
## Features
1. Joystick Control:
  * Reads PWM signals from two joysticks to control motor movements.
  * Uses the pulseIn() function to measure joystick inputs.
2. DC Motor Control:
  * Moves the back fins (motors 2 and 3) based on the left joystick's vertical axis.
  * Controls water pumps (motors 1 and 4) based on the right joystick's horizontal axis.
3. Stepper Motor Control:
  * Controls the front fins using the right joystick's vertical axis.
  * Implements synchronized movement for the two stepper motors (front fins) with forward and backward step functions.

## Code Structure
1. Setup:
  * Configures the joystick input pins.
  * Initializes serial communication for debugging.
  * Begins communication with motor shields.
2. Loop:
  * Continuously reads joystick inputs.
  * Prints the values for debugging.
  * Calls the motorMove() function to process joystick inputs and move the motors.
3. Functions:
  * forwardStep(int steps): Moves the front fins forward by stepping both motors in sync.
  * backwardStep(int steps): Moves the front fins backward by stepping both motors in sync.
  * motorMove(int pwm1, int pwm2, int pwm3, int pwm4): Processes joystick inputs to control DC and stepper motors.
