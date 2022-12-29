#include <L298N.h>

#include <Servo.h>
const int lower_switch = 14;
const int upper_switch = 15;
const int dispatch = 32;
const int drop = 34;
const int latch_on = 115;
const int latch_off = 130;
const int m1 = 4;
const int m2 = 5;

Servo latch;

// Set motor control pins as outputs
L298N motor(m1,m2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  


  // Tell motor how fast to turn
  motor.setSpeed(255);
  
  // Create Servo. In our case, we have two but they share a cable
  latch.attach(6);
  
  // Set limit switches to be pull up resistors
  // This eliminates erroneous data
  pinMode(lower_switch,INPUT_PULLUP);
  pinMode(upper_switch,INPUT_PULLUP);

  // Set buttons to be pull up as well
  pinMode(dispatch,INPUT_PULLUP);
  pinMode(drop,INPUT_PULLUP);

  // Set servos to default positions
  latch.write(latch_on);

  // Descend motor until limit switch is tripped
  while(digitalRead(lower_switch)==HIGH){
    Serial.println("Homing");
    motor.backward();
  }
  motor.stop();
  delay(2000);
  // Repeat to ensure the car has reached the bottom
  while(digitalRead(lower_switch)==HIGH){
    Serial.println("Homing");
    motor.backward();
  }
  motor.stop();
  // Tell user setup is complete
  Serial.println("Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(digitalRead(dispatch)==HIGH){
    // wait for signal
  }
  while(digitalRead(upper_switch)==HIGH){
    motor.forward();
    Serial.println("Running UP");
  }
  Serial.println("Waiting To Drop!");
  motor.stop();
  while(digitalRead(drop)==HIGH){
    // wait for signal
    Serial.println("Waiting To Drop!");
  }
  latch.write(latch_off);
  Serial.println("DROPPING");
  delay(3000);
  while(digitalRead(lower_switch)==HIGH){
    motor.backward();
  }
  motor.stop();
  delay(2500);
  latch.write(latch_on);
  Serial.println("Cycle Complete");
}
