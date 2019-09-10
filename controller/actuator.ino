// set the currentColors variable
void setColor(long colors[]) {
  currentColors[0] = colors[0];
  currentColors[1] = colors[1];
  currentColors[2] = colors[2];
  sendColor();
}

// calculate the intensity and send the current color out via the output pins
void sendColor()
{
  if (customLoop == false) {
    long red = currentColors[0];
    long green = currentColors[1];
    long blue = currentColors[2];

    long mappedIntensity = map(intensity, 0, 10, 0, 4095);
    long redComputed = map(red, 0, 255, 0, mappedIntensity);
    long blueComputed = map(blue, 0, 255, 0, mappedIntensity);
    long greenComputed = map(green, 0, 255, 0, mappedIntensity);

    setColorAllSteps(redComputed,greenComputed,blueComputed);
  }
}


int redVal = 0;
int grnVal = 0;
int bluVal = 0;

int prevR = redVal;
int prevG = grnVal;
int prevB = bluVal;

int calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero,
    step = 256 / step;            //   divide by 1020
  }
  return step;
}
 

void mapear(){
  
 while (Serial.available()) {
  
      inChar = (char)Serial.read();
      Serial.println(inChar);
      
      if (inChar == '1') {
        for (uint8_t pos = 0; pos < 48; pos++) {
          setIntensity(pos, 0);
        }
        Serial.println(cont);
        setIntensity(cont, 4095);
        cont++;
      }
      else if(inChar == 'r'){setColorAllSteps(4095,0,0);}
      else if(inChar == 'g'){setColorAllSteps(0,4095,0);}
      else if(inChar == 'b'){setColorAllSteps(0,0,4095);}
      else if(inChar == 'n'){setColor(BROWN_COLOR);}
      else if(inChar == 'a'){
        for (uint8_t servonum = 0; servonum < 16; servonum++) {
          board1.setPWM(servonum, 0, 4095);
          board2.setPWM(servonum, 0, 4095);
          board3.setPWM(servonum, 0, 4095);
        }
      }
      else if(inChar == '\n'){}
      else if(inChar == 'x'){
        for (uint8_t servonum = 0; servonum < 16; servonum++) {
          board1.setPWM(servonum, 0, 0);
          board2.setPWM(servonum, 0, 0);
          board3.setPWM(servonum, 0, 0);
        }
      }
      else{
        Serial.println("else");
        cont=0;
      }
  }
}
