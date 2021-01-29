//Baseline Code rev. 2
//Created by Colin Steplowski
//9-29-2020

#include <A4990MotorShield.h>
A4990MotorShield motors;
#include <PS2X_lib.h>

PS2X ps2x;

int rightX, rightY, leftX, leftY; //initialize integer variables to store the position of the analog sticks - note that rightX and leftX are unused in this sketch
int rightMotorSpeed, leftMotorSpeed; //initialize integer variables to store the motor speeds

void setup() {
  Serial.begin(9600);
  ps2x.config_gamepad(22, 23, 24, 25, true, true); //configure the gamepad setup (clk, cmd, att, dat, enable pressure, enable rumble)
  pinMode(11, OUTPUT); // PSAB_PAD_UP      11    set pins used for PWM motor control as outputs
  pinMode(12, OUTPUT); //PSAB_PAD_DOWN    12
  pinMode(10, OUTPUT); //PSAB_PAD_LEFT    10
  pinMode(9, OUTPUT); //PSAB_PAD_RIGHT   9
}

void loop() {
  ps2x.read_gamepad(false, false); //read the states of the gamepad inputs

  //leftMotorSpeed = (800 / 255) * (ps2x.Analog(PSAB_PAD_LEFT)); //calculate motor speeds based on the Y axis positions of the analog sticks

  //rightMotorSpeed = (800 / 255) * (ps2x.Analog(PSAB_PAD_RIGHT));

  if(PSAB_PAD_UP == true){
    leftMotorSpeed = (800 / 255);
    rightMotorSpeed = (800 / 255);
    
  }else if (PSAB_PAD_DOWN == true){
    leftMotorSpeed = (800 / 255);
    rightMotorSpeed = (800 / 255);
    
  }else if(PSAB_PAD_LEFT == true){
    leftMotorSpeed = (800 / 255) * .1;
    rightMotorSpeed = (800 / 255);
      
  }else if(PSAB_PAD_RIGHT == true){
    leftMotorSpeed = (800 / 255);
    rightMotorSpeed = (800 / 255) * .1;
  }


  motors.setSpeeds(leftMotorSpeed, rightMotorSpeed); //set speed of motors




  delay(100); //slow down read and write refresh frequency to 10 Hz.
  if (motors.getFault()) { //check motor driver for faults
    motors.setSpeeds(0, 0); //stop motors indefinitely if true
    while (true) {
      Serial.println("Fault");
      delay(1000);
    }
  }
}

/*An analog stick rests at the coordinates (127,127)



*/
