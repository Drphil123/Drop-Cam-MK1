// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constants
#define FULLSTEP 4

// Creates two instances
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
//AccelStepper stepper1(FULLSTEP, 8, 10, 9, 11); (don't need other stepper)
  AccelStepper stepper2(FULLSTEP, 4, 6, 5, 7); 

  int lightrelay = 10;

void setup() {
  Serial.begin(9600);

  pinMode(lightrelay, OUTPUT);

  digitalWrite(lightrelay, HIGH);

  //configuring the stepper motor's speed, acceleration and how much it will turn
  stepper2.setMaxSpeed(20.0);
  stepper2.setAcceleration(20.0);
  stepper2.setSpeed(1);
  stepper2.moveTo(500);
}

void loop() {
  //defining when the light will be on and off (time is in milliseconds here)
  const long lighton = 300000; //light will turn on after 5 minutes
  const long lightoff = 7200000; //light will turn off after 2 hours
  unsigned long  previoustime = 0; //just some value we need to turn the light off

  //calculating how much further the stepper needs to go before turning the other way
  if (stepper2.distanceToGo() == 0) 
    stepper2.moveTo(-stepper2.currentPosition());

  //this needs to be here otherwise the stepper won't run
  stepper2.run();

  //our variable to hold the current time elapsed since the start of the program
  unsigned long currenttime = millis();

  Serial.println(currenttime);

  //checking if 5 minutes have passed to turn the light on
  if (currenttime >= lighton){
    digitalWrite(lightrelay, LOW);
  }

  //for some reason this has to be an equation otherwise the light will not turn back off
  //checking if 2 hours have passed to turn the light off
  if (currenttime - previoustime >= lightoff) {
    previoustime = currenttime; //this may or may not be necessary but it works so no need to change
    digitalWrite(lightrelay, HIGH);
  }
}
