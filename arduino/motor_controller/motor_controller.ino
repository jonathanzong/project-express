#include <SoftwareSerial.h>
#include "DynamixelMotor.h"

// clearpath vars
int enable = 9;
int dirpin = 10;
int steppin = 11;

//dynamixel vars
int16_t speed=256;

DynamixelInterface &interface=*createSoftSerialInterface(2,3);

int cwlimit1 = 65;
int ccwlimit1 = 915;
int cwlimit2 = 870;
int ccwlimit2 = 880;
int cwlimit3 = 1;
int ccwlimit3 = 262;

DynamixelMotor motor1(interface, 1);
DynamixelMotor motor2(interface, 2);
DynamixelMotor motor3(interface, 3);

void setup() {
  Serial.begin(9600);

  //clearpath init
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);
  pinMode(enable, OUTPUT);
  digitalWrite(enable, HIGH);
  delay(100);

  //dynamixel init
  interface.begin(57142);
  delay(100);
  
  motor1.init();
  motor1.enableTorque();
  motor1.speed(speed);
  motor1.jointMode(cwlimit1, ccwlimit1);
  
  for (int i = 0; i < 3; i++) {
    motor1.led(true);
    delay(200);
    motor1.led(false);
    delay(200);
  }
  
  motor2.init();
  motor2.enableTorque();
  motor2.speed(speed);
  motor2.jointMode(cwlimit2, ccwlimit2);
  
  for (int i = 0; i < 3; i++) {
    motor2.led(true);
    delay(200);
    motor2.led(false);
    delay(200);
  }
  
  motor3.init();
  motor3.enableTorque();
  motor3.speed(speed);
  motor3.jointMode(cwlimit3, ccwlimit3);
  
  for (int i = 0; i < 3; i++) {
    motor3.led(true);
    delay(200);
    motor3.led(false);
    delay(200);
  }
  
  delay(1000);
}

// dynamixel functions
void paintEnable(boolean on) {
  if (on) {
    motor2.position(ccwlimit2); 
  }
  else {
    motor2.position(cwlimit2);
  }
}

void colorSelect(int index) {
  if (index < 0 || index >= 17) return;
  motor1.position(cwlimit1 + (index * ((ccwlimit1 - cwlimit1)/16)));
}

void flowSet(int percent) {
  if (percent < 0 || percent > 100) return;
  if (percent == 0) {
    motor3.position(ccwlimit3);
  }
  else {
    motor3.position(ccwlimit3 - (percent * (ccwlimit3 - cwlimit3)/100));
  }
}
//

void loop() {

  while (Serial.available() > 0) {
    // parse out values
    int xdir = Serial.parseInt();
    int ydir = Serial.parseInt();
    int dx = Serial.parseInt();
    int dy = Serial.parseInt();
    int colorIdx = Serial.parseInt();
    int flow = Serial.parseInt();

    if (Serial.read() == '\n') {
      // clearpath signals
      if (xdir) {
        digitalWrite(dirpin, HIGH);
      }
      else {
        digitalWrite(dirpin, LOW);
      }
      for (int i = 0; i < dx; i++) {
        digitalWrite(steppin, LOW);
        digitalWrite(steppin, HIGH);
      }
      // TODO ydir

      // dynamixel signals
      motor1.led(true);
      delay(100);
      motor1.led(false);
      delay(100);
      colorSelect(colorIdx);
      delay(100);
      paintEnable(flow > 0);
      delay(100);
      flowSet(flow);
      delay(100);
    }
  }
}
