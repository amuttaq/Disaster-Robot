//Baseline Code rev. 2
//Created by Colin Steplowski
//9-29-2020

#include <PS2X_lib.h>
#include <A4990MotorShield.h>
A4990MotorShield motors;
//^^^^^
//This is the ps2 motor library

#include <Servo.h>
#include <math.h>

#define CONE_SERVO 3 //servo on pin 3

#define SLEEP_MS 50 // Milliseconds to sleep on step
#define STEP 2 // Number of degrees per-move

#define MIN_ANGLE 0
#define MAX_ANGLE 180

struct Servo servo;
float angle = 0.0;



//^^^^^
//Cone Dropper initial

//Created by JohnKhoi Huu Nguyen for water level sensor

const int full = 1000;
const int middle = 500;
const int low = 100;
int depthSensor = 2; //Set depthSensor input pin to Analog 2.
int lastValue = 2;
char printBuffer[128];

/* The following line sets the LED pin to the corresponding digital pin of the
  Arduino.  You can set these to any digital pin as needed
*/

const int whiteLED = 39;
const int YellowLED = 41;
const int RedLED = 43;

//^^^^^^^
//Water level sensor

PS2X ps2x;

int rightX, rightY, leftX, leftY; //initialize integer variables to store the position of the analog sticks - note that rightX and leftX are unused in this sketch
int rightMotorSpeed, leftMotorSpeed; //initialize integer variables to store the motor speeds

void rotate(float degrees){
  
  int steps;
  float nextAngle = angle;
  Serial.print("Rotating ");
  Serial.print(degrees);
  Serial.print(" Degrees to ");
  nextAngle += degrees;
  Serial.print(nextAngle);
  Serial.println(" Degrees");
  
  steps = floor(degrees/(float)STEP);
  for(int x = 0; x < steps; x++)
  {
    angle += STEP;
    servo.write(angle);
    delay(SLEEP_MS);
  }
  
  angle = nextAngle;
  servo.write(angle);
  
}//void rotate


void setup(){
  Serial.begin(9600);
  ps2x.config_gamepad(22, 23, 24, 25, true, true); //configure the gamepad setup (clk, cmd, att, dat, enable pressure, enable rumble)
  pinMode(7, OUTPUT); //set pins used for PWM motor control as outputs
  pinMode(8, OUTPUT); 
  pinMode(16, OUTPUT); //PSAB_SQUARE      16
 pinMode(26,OUTPUT); //water pump
  pinMode(27,OUTPUT); // fan
  pinMode(14,OUTPUT); //define PSAB_CIRCLE      14
  pinMode(15,OUTPUT);//define PSAB_CROSS       15

   pinMode(whiteLED, OUTPUT); // Set LED pin to OUTPUT mode.
  pinMode(YellowLED, OUTPUT); // Set LED pin to OUTPUT mode.
  pinMode(RedLED, OUTPUT); // Set LED pin to OUTPUT mode.
  
  servo.attach(CONE_SERVO);//Puts servo on pin 3
  servo.write(0.0);
  delay(100);
  Serial.println("Setup Complete.");
}

void loop() {
  ps2x.read_gamepad(false, false); //read the states of the gamepad inputs

   if (ps2x.Analog(PSAB_SQUARE)) {
Serial.println("Detected Button Push");
    rotate(12); //Rotate!
}else {
  Serial.println("No Moving Servo Detected");
}//if & else for servo

if(ps2x.Analog(PSAB_CROSS)){
digitalWrite(26,HIGH);
delay(1000);            // waits for a second
digitalWrite(26,LOW);
delay(1000);            // waits for a second
}
/*else{
digitalWrite(26,LOW);
delay(1000);            // waits for a second
}//if statement for Pump
*/
if(ps2x.Analog(PSAB_CIRCLE)){
digitalWrite(27,HIGH);
delay(1000);            // waits for a second
 digitalWrite(27,LOW);
  delay(1000);            // waits for a second
}
/*else{ 
  digitalWrite(27,LOW);
  delay(1000);            // waits for a second
} //if statemnt for fan
*/

 int value = analogRead(depthSensor); // Read the sensor values.
  if (((lastValue >= value) && ((lastValue - value) > 10)) || (lastValue = 10)) /* If the delta
  between last and current value is > 10, display the current value. */
  {
    // Displays depth sensor value to serial port.
    sprintf(printBuffer, "ADC%d level is %d\n", depthSensor, value);
    Serial.print(printBuffer);
    Serial.println();
    //Serial.println(value);
    //Serial.println();
    // Set last value to current value for next loop.
    lastValue - value;
  }
  if (value >= full)
  {
    // FULL
    for (int x = 2; x < 15; x++) {
      digitalWrite(RedLED, HIGH);
      delay(1000);
      digitalWrite(RedLED, LOW);
  delay(100);

    }
  }
  if (value >= middle)
  {
    //middle
    for (int x = 2; x < 10; x++) {
      digitalWrite(YellowLED, HIGH);
      delay(500);
      digitalWrite(YellowLED, LOW);
  delay(100);

    }
  }
  if (value >= low)
  {
    //LOW
    for (int x = 2; x < 5; x++) {
      digitalWrite(whiteLED, HIGH);
      delay(100);
      digitalWrite(whiteLED, LOW);
  delay(100);

    }
  }


  leftMotorSpeed = (800/255) * (ps2x.Analog(PSS_LY) - 127); //calculate motor speeds based on the Y axis positions of the analog sticks
  rightMotorSpeed = (800/255) * (ps2x.Analog(PSS_RY) - 127);
  motors.setSpeeds(leftMotorSpeed, rightMotorSpeed); //set speed of motors

  delay(100); //slow down read and write refresh frequency to 10 Hz.
  if (motors.getFault()) { //check motor driver for faults
    motors.setSpeeds(0, 0); //stop motors indefinitely if true
    while (true) {
      Serial.println("Fault");
      delay(1000);
    }//loop for motor
  }//if statement for motor fault
}//void loop
