
#include <PS2X_lib.h>

#include <A4990MotorShield.h>

#include <Servo.h>
#include <math.h>

#define CONE_SERVO 3

#define SLEEP_MS 50 // Milliseconds to sleep on step
#define STEP 2 // Number of degrees per-move

#define MIN_ANGLE 0
#define MAX_ANGLE 180

struct Servo servo;
float angle = 0.0;

PS2X ps2x;

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

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  ps2x.config_gamepad(22, 23, 24, 25, true, true); //configure the gamepad setup (clk, cmd, att, dat, enable pressure, enable rumble)

   servo.attach(CONE_SERVO);
  pinMode(16, OUTPUT); //PSAB_SQUARE      16
    servo.write(0.0);
  delay(100);
  Serial.println("Setup Complete.");

}//void setup

void loop() {
  // put your main code here, to run repeatedly:
 ps2x.read_gamepad(false, false); //read the states of the gamepad inputs

 if (ps2x.Analog(PSAB_SQUARE)) {
Serial.println("Detected Button Push");
    rotate(22.5); //Rotate!
   

}else {
  Serial.println("No Moving Servo Detected");
}
Serial.println("Statement no work");


}// void loop
