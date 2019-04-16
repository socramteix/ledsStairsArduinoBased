#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver board3 = Adafruit_PWMServoDriver(0x42);

uint8_t servonum = 0;
char inChar = '0';

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  board1.begin();
  board2.begin();
  board3.begin();

  board1.setPWMFreq(490);  // Analog servos run at ~60 Hz updates
  board2.setPWMFreq(490);
  board3.setPWMFreq(490);

  delay(10);
}

void loop() {
  // Drive each servo one at a time
    while (Serial.available()) {
      inChar = (char)Serial.read();
      // add it to the inputString:
      //inputString += inChar;
      // if the incoming character is a newline, set a flag so the main loop can
      // do something about it:
      if (inChar == '1') {
        //stringComplete = true;

        Serial.println(inChar);
        for (uint8_t servonum = 0; servonum < 16; servonum++) {
          board1.setPWM(servonum, 0, 4095);
          board2.setPWM(servonum, 0, 4095);
          board3.setPWM(servonum, 0, 4095);
        }
      }
      else if(inChar == '\n'){}
      else{
        Serial.println("else");
          for (uint8_t servonum = 0; servonum < 16; servonum++) {
          board1.setPWM(servonum, 0, 0);
          board2.setPWM(servonum, 0, 0);
          board3.setPWM(servonum, 0, 0);
        }
      }
  }

//  delay(500);
//  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
//    pwm.setPWM(servonum, 0, pulselen);
//  }

  delay(500);

 // servonum ++;
 // if (servonum > 7) servonum = 0;
}
