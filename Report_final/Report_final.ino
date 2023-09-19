#include "MeMCore.h"

/* MBOT LIBRARY FUNCTION DECLARATIONS */
MeBuzzer buzzer; // create the buzzer object to play the sound
MeLineFollower lineFinder(PORT_1); // assigning the black lineFinder to RJ25 port 1
MeDCMotor leftMotor(M1); // assigning leftMotor to port M1
MeDCMotor rightMotor(M2); // assigning RightMotor to port M2
MeRGBLed led(0,30);


/* PID CONTROL CONSTANTS */
#define kp 15
#define kd 3
float last_error = 0;


/* COLOUR SENSOR CONSTANTS */
#define RGBWait 250
#define LDRWait 10 
#define LDR A3 // reading LDR from port 4 (A3 pin)


/* ULTRASONIC CONSTANTS */
#define TIMEOUT 2000 
#define SPEED_OF_SOUND 340 // Update according to your own experiment
#define ULTRASONIC 10 // ultrasonic assigned to pin 10 as we are using port 2
#define THRESHOLD 11; // ultrasonic threshold for wall tracking aka distance from wall


/* MOVEMENT CONSTANTS */
uint8_t targetSpeed = 225; // max target speed = 255, lowered so PD corrections are easier to execute
#define TURNING_TIME_MS 440 // adjust time taken to turn here


void setup() {
 Serial.begin(9600);
 delay(1000);
 pinMode(ULTRASONIC, OUTPUT);
 led.setpin(13); // declare onboard LED pin
}

/* read line sensor, if both on black, stop, activate colour sensor and turn/stop accordingly, else move forward */
void loop()
{
  int sensorState = lineFinder.readSensors();
  if (sensorState == S1_IN_S2_IN)
  {
    stop(300);
    int colour = detect_colour();
    setColor(colour);
    turn(colour);
  }
  else
  {
    move_maze(targetSpeed, last_error);
  }
}
