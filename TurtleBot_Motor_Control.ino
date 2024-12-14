#include <Adafruit_MotorShield.h>

int PWM_PIN1 = 2;     // Left joystick up/down
int PWM_PIN2 = 3;     // Right joystick left/right
int PWM_PIN3 = 4;     // Right joystick up/down
int PWM_PIN4 = 5;     // Left Joystick left/right (currently unused)

Adafruit_MotorShield AFMSbot = Adafruit_MotorShield(0x61);    // Motor shield for DC motors
Adafruit_MotorShield AFMStop = Adafruit_MotorShield(0x60);    // Motor shield for stepper motors

Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 2);

Adafruit_DCMotor *myMotor1 = AFMSbot.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMSbot.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMSbot.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMSbot.getMotor(4);


void setup() {
  pinMode(PWM_PIN1, INPUT);
  pinMode(PWM_PIN2, INPUT);
  pinMode(PWM_PIN3, INPUT);
  pinMode(PWM_PIN4, INPUT);

  Serial.begin(9600);

  AFMSbot.begin();
  AFMStop.begin();
}

void loop() {
  int pwm1 = pulseIn(PWM_PIN1, HIGH);     // Left joystick up/down for DC motors
  int pwm2 = pulseIn(PWM_PIN2, HIGH);     // Right joystick left/right for DC motors
  int pwm3 = pulseIn(PWM_PIN3, HIGH);     // Right joystick up/down for stepper motors
  int pwm4 = pulseIn(PWM_PIN4, HIGH);     // Left joystick left/right (unused)
  
  // Print joystick values for debugging 
  Serial.print("PRM CH1: ");
  Serial.print(pwm1);
  Serial.print("PRM CH2: ");
  Serial.print(pwm2);
  Serial.print("PRM CH3: ");
  Serial.print(pwm3);
  Serial.print("PRM CH4: ");
  Serial.println(pwm4);

  // Move motors based on joystick input
  motorMove(pwm1, pwm2, pwm3, pwm4);
}

// Function to make both stepper motors (front fins) move forward simultaneously 
void forwardStep(int steps){
  for (int i = 0; i < 600; i++) {
    myStepper1->step(1, FORWARD, DOUBLE);
    myStepper2->step(1, FORWARD, DOUBLE);
  }
}

// Function to make both stepper motors (front fins) to move backward simultaneously 
void backwardStep(int steps){
  for (int i = 0; i < 600; i++) {
    myStepper1->step(1, BACKWARD, DOUBLE);
    myStepper2->step(1, BACKWARD, DOUBLE);
  }
}

// Function to control motor movements based on joystick inputs 
void motorMove(int pwm1, int pwm2, int pwm3, int pwm4){
  // Control for DC motors 2 and 3 (Back fins) (left joystick up/down)
  if (pwm1 <= 1255) {  // Joystick moved down
    myMotor2->setSpeed(200);
    myMotor3->setSpeed(200);
    myMotor2->run(BACKWARD);
    myMotor3->run(BACKWARD);
  } else if (pwm1 >= 1821) {  // Joystick moved up
    myMotor2->setSpeed(200);
    myMotor3->setSpeed(200);
    myMotor2->run(FORWARD);
    myMotor3->run(FORWARD);
  } else { // Joystick neutral
    myMotor2->run(RELEASE);
    myMotor3->run(RELEASE);
  }

  // Control for DC motors 1 and 4 (Water pumps) (right joystick left/right)
  if (pwm2 >= 1712) {   // Joystick moved left
    myMotor1->setSpeed(200);
    myMotor1->run(FORWARD);
  } else if (pwm2 <= 1300) { // Joystick moved right
    myMotor4->setSpeed(200);
    myMotor4->run(FORWARD);
  } else { // Joystick neutral
    myMotor1->run(RELEASE);
    myMotor4->run(RELEASE);
  }

  // Control for Stepper motors 1 and 2 (Front fins) (right joystick up/down)
  if (pwm3 <= 1359) {   // Joystick moved down 
    myStepper1->setSpeed(300);  // Set stepper speeds to 300 rpm
    myStepper2->setSpeed(300);
    forwardStep(600);           // Calling forwardStep function to move stepper motors forward 600 steps
    delay(10);
  } else if (pwm3 >= 1835) {    //Joystick moved up
    myStepper1->setSpeed(300);  // Set stepper speeds to 300 rpm
    myStepper2->setSpeed(300);
    backwardStep(600);           // Calling backwardStep function to move stepper motors backward 600 steps
    delay(10);

  }
}



