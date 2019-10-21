
// raise the intensity of light or the speed of animation
void raiseIntensity() {
  if (!customLoop) {
    if (intensity <= 9) {
      intensity++;
    }
  } else if (speedValue <= 9) {
    speedValue++;
  }
}

// lower the intensity of light or the speed of animation
void lowerIntensity() {
  if (!customLoop) {
    if (intensity >= 2) {
      intensity--;
    }
  } else if (speedValue >= 2) {
    speedValue--;
  }
}

void efeito_ligando2(){
  for(int j=0;j<16;j++){
    setIntensity(degraus[j][0],4095);
    setIntensity(degraus[j][1],4095);
    setIntensity(degraus[j][2],4095);
    delay(25);
    setIntensity(degraus[j][0],0);
    setIntensity(degraus[j][1],0);
    setIntensity(degraus[j][2],0);
  }
  for(int j=14;j>=0;j--){
    setIntensity(degraus[j][0],4095);
    setIntensity(degraus[j][1],4095);
    setIntensity(degraus[j][2],4095);
    delay(25);
    setIntensity(degraus[j][0],0);
    setIntensity(degraus[j][1],0);
    setIntensity(degraus[j][2],0);
  }
}

void efeito_ligando1(){

  for(int i=0;i<3;i++){
    setColorAllSteps(4095,4095,4095);
    delay(100);
    setColorAllSteps(0,0,0);
    delay(100);
  }
  
}

void efeito_desligando(){

  for(int i=1000;i>=0;i=i-10){
    setColorAllSteps(i,0,0);
    delay(2);
  }
  //setColor(BLACK_COLOR);
  
}

void efeito_desligando2(){

  int aux = 100;
  int tim = 40;
  setColorAllSteps(intensity*aux,intensity*aux,intensity*aux);
  delay(tim);
  setColorAllSteps(0,0,0);
  delay(tim);
  setColorAllSteps(intensity*aux,intensity*aux,intensity*aux);
  delay(tim);
  setColorAllSteps(0,0,0);
  delay(tim);
  setColorAllSteps(intensity*aux,intensity*aux,intensity*aux);
  delay(tim);
  setColorAllSteps(0,0,0);
  delay(tim);
  
  //setColor(BLACK_COLOR);
  
}

// custom flashing function
void flash() {
  customLoop = true; // set the variable so that the program knows we are in a custom animation loop
  unsigned long previousMillis = 0;
  while (customLoop) { // while we are still in the custom animation loop
    if (irrecv.decode(&results)) { // check for incomming ir code and if found exit the loop and interpret the code
      if (existsInArray(results.value, AVAILABLE_CODES, 24) && results.value != INTENSITY_UP_CODE && results.value !=  INTENSITY_DN_CODE && results.value != FLASH_CODE) {
        Serial.println("return break");
        return; break;
        interpretRemoteCode(results.value);
      } else if (results.value == INTENSITY_UP_CODE) { // if the code is to raise or lower the speed
        raiseIntensity();                               // raise the speed
      } else if (results.value == INTENSITY_DN_CODE) {
        lowerIntensity();                               // or lower the speed
      }
      irrecv.resume();
    }
    long randomNumber = random(16); // get a random number from 0 to 16
    
    // set temporary variales for the red, green and blue values
    long red = AVAILABLE_COLORS[randomNumber][0];
    long green = AVAILABLE_COLORS[randomNumber][1];
    long blue = AVAILABLE_COLORS[randomNumber][2];
    unsigned long currentMillis = millis();
    
    // set a X animation delay from 200 to 3000 milliseconds based on the speed variable
    long mappedSpeed = map(speedValue, 10, 1, 200, 3000);
    
    // every X milliseconds
    if (currentMillis - previousMillis >= mappedSpeed) {
      previousMillis = currentMillis;

      long mappedRed = map(red, 0, 255, 0, 4095);
      long mappedGreen = map(green, 0, 255, 0, 4095);
      long mappedBlue = map(blue, 0, 255, 0, 4095);

      setColorAllSteps(mappedRed,mappedGreen,mappedBlue);

//      for (uint8_t servonum = 0; servonum < 16; servonum++) {
//        board1.setPWM(servonum, 0, mappedRed);
//        board2.setPWM(servonum, 0, mappedGreen);
//        board3.setPWM(servonum, 0, mappedBlue);
//      }
    }
  }
}

void strobe() {
  customLoop = true;
  unsigned long previousMillis = 0;
  int i = 1;
  while (customLoop) {
    if (irrecv.decode(&results)) {
      if (existsInArray(results.value, AVAILABLE_CODES, 24) && results.value != INTENSITY_UP_CODE && results.value !=  INTENSITY_DN_CODE && results.value != STROBE_CODE) {
        Serial.println("return break");
        return; break;
        interpretRemoteCode(results.value);
      } else if (results.value == INTENSITY_UP_CODE) {
        raiseIntensity();
      } else if (results.value == INTENSITY_DN_CODE) {
        lowerIntensity();
      }
      irrecv.resume();
    }
    long randomNumber = random(16);
    long red = AVAILABLE_COLORS[randomNumber][0];
    long green = AVAILABLE_COLORS[randomNumber][1];
    long blue = AVAILABLE_COLORS[randomNumber][2];
    unsigned long currentMillis = millis();
    long mappedSpeed = map(speedValue, 10, 1, 50, 1500);
    long mappedRed;
    long mappedGreen;
    long mappedBlue;
    if (currentMillis - previousMillis >= mappedSpeed) {
      previousMillis = currentMillis;
      if ( (i % 2) == 0) {
        
        mappedRed = map(red, 0, 255, 0, 4095);
        mappedGreen = map(green, 0, 255, 0, 4095);
        mappedBlue = map(blue, 0, 255, 0, 4095);

        setColorAllSteps(mappedRed,mappedGreen,mappedBlue);
        
//        for (uint8_t servonum = 0; servonum < 16; servonum++) {
//          board1.setPWM(servonum, 0, mappedRed);
//          board2.setPWM(servonum, 0, mappedGreen);
//          board3.setPWM(servonum, 0, mappedBlue);
//        }
      } else {
          setColorAllSteps(0,0,0);
//          for (uint8_t servonum = 0; servonum < 16; servonum++) {
//            board1.setPWM(servonum, 0, 0);
//            board2.setPWM(servonum, 0, 0);
//            board3.setPWM(servonum, 0, 0);
//          }
      }
      i++;
    }
  }
}

void fade() {
  customLoop = true;
  unsigned long previousMillis = 0;
  int i = 1;
  long randomNumber = random(16);
  long red = AVAILABLE_COLORS[randomNumber][0];
  long green = AVAILABLE_COLORS[randomNumber][1];
  long blue = AVAILABLE_COLORS[randomNumber][2];
  Serial.println("final colors");
  Serial.println(red);
  Serial.println(green);
  Serial.println(blue);
  Serial.println("-----------");
  while (i < 255) {
    if (irrecv.decode(&results)) {
      if (existsInArray(results.value, AVAILABLE_CODES, 24) && results.value != INTENSITY_UP_CODE && results.value !=  INTENSITY_DN_CODE && results.value != FADE_CODE) {
        Serial.println("return break");
        return; break;
        interpretRemoteCode(results.value);
      } else if (results.value == INTENSITY_UP_CODE) {
        raiseIntensity();
      } else if (results.value == INTENSITY_DN_CODE) {
        lowerIntensity();
      }
      irrecv.resume();
    }

    unsigned long currentMillis = millis();
    long mappedSpeed = map(speedValue, 10, 1, 10, 100);
    if (currentMillis - previousMillis >= mappedSpeed) {
      previousMillis = currentMillis;
      long mappedRedIntensity = map(i, 0, 255, 0, red);
      long mappedRed = red != 0 ? map(red, 0, red, 0, mappedRedIntensity) : 0;
      long mappedGreenIntensity = map(i, 0, 255, 0, green);
      long mappedGreen = green != 0 ? map(green, 0, green, 0, mappedGreenIntensity) : 0;
      long mappedBlueIntensity = map(i, 0, 255, 0, blue);
      long mappedBlue = blue != 0 ? map(blue, 0, blue, 0, mappedBlueIntensity) : 0;
      i++;
      
      mappedRed = map(mappedRed, 0, 255, 0, 4095);
      mappedGreen = map(mappedGreen, 0, 255, 0, 4095);
      mappedBlue = map(mappedBlue, 0, 255, 0, 4095);

      setColorAllSteps(mappedRed,mappedGreen,mappedBlue);
      
//      for (uint8_t servonum = 0; servonum < 16; servonum++) {
//        board1.setPWM(servonum, 0, mappedRed);
//        board2.setPWM(servonum, 0, mappedGreen);
//        board3.setPWM(servonum, 0, mappedBlue);
//      }
    }
  }
  while (i > 0) {
    if (irrecv.decode(&results)) {
      if (existsInArray(results.value, AVAILABLE_CODES, 24) && results.value != INTENSITY_UP_CODE && results.value !=  INTENSITY_DN_CODE && results.value != FADE_CODE) {
        Serial.println("return break");
        return; break;
        interpretRemoteCode(results.value);
      } else if (results.value == INTENSITY_UP_CODE) {
        raiseIntensity();
      } else if (results.value == INTENSITY_DN_CODE) {
        lowerIntensity();
      }
      irrecv.resume();
    }

    unsigned long currentMillis = millis();
    long mappedSpeed = map(speedValue, 10, 1, 10, 100);
    if (currentMillis - previousMillis >= mappedSpeed) {
      previousMillis = currentMillis;
      long mappedRedIntensity = map(i, 0, 255, 0, red);
      long mappedRed = red != 0 ? map(red, 0, red, 0, mappedRedIntensity) : 0;
      long mappedGreenIntensity = map(i, 0, 255, 0, green);
      long mappedGreen = green != 0 ? map(green, 0, green, 0, mappedGreenIntensity) : 0;
      long mappedBlueIntensity = map(i, 0, 255, 0, blue);
      long mappedBlue = blue != 0 ? map(blue, 0, blue, 0, mappedBlueIntensity) : 0;
      
      mappedRed = map(mappedRed, 0, 255, 0, 4095);
      mappedGreen = map(mappedGreen, 0, 255, 0, 4095);
      mappedBlue = map(mappedBlue, 0, 255, 0, 4095);

      setColorAllSteps(mappedRed,mappedGreen,mappedBlue);
      
//      for (uint8_t servonum = 0; servonum < 16; servonum++) {
//        board1.setPWM(servonum, 0, mappedRed);
//        board2.setPWM(servonum, 0, mappedGreen);
//        board3.setPWM(servonum, 0, mappedBlue);
//      }      
      i--;
      if (i == 0) {
        fade();
      }
    }
  }
}


void subirEscada(){

  long mappedIntensity = map(intensity, 0, 10, 0, 4095);
  long redComputed = map(currentColors[0], 0, 255, 0, mappedIntensity);
  long greenComputed = map(currentColors[1], 0, 255, 0, mappedIntensity);
  long blueComputed = map(currentColors[2], 0, 255, 0, mappedIntensity);
  
  for(int j=0;j<16;j++){
    setIntensity(degraus[j][0],redComputed);
    setIntensity(degraus[j][1],greenComputed);
    setIntensity(degraus[j][2],blueComputed);
    if(j == 7){
      delay(100);
      setPatamar(currentColors[0],currentColors[1],currentColors[2]);
    }
      
    if(findCode())
      return;
    delay(100);
    Serial.print(".");
  }
  
  Serial.println("16 sec...");
  for(int i=0;i<16;i++){
    if(findCode())
      return;
    delay(1000);
  }
  
  for(int j=15;j>=0;j--){
    setIntensity(degraus[j][0],0);
    setIntensity(degraus[j][1],0);
    setIntensity(degraus[j][2],0);
    if(j == 8){
      delay(100);
      setPatamar(0,0,0);
    }
    if(findCode())
      return;
    delay(100);
  }
  //desligarFonte();
}

void setColorAllSteps(int red, int green, int blue){

//MMM      Serial.println("Set all steps");
  //seta a posição mapeada (0 a 47) para cada degrau
  for(int j=0;j<16;j++){
      setIntensity(degraus[j][0],red);
      //Serial.print("red: ");
      //Serial.print(red);
      setIntensity(degraus[j][1],green);
//      //Serial.print(" green: ");
//      //Serial.print(degraus[j][1]);
      setIntensity(degraus[j][2],blue);
//      //Serial.print(" blue: ");
//      //Serial.println(degraus[j][2]);
//      //Serial.print("aqui: ");
//      //Serial.println(map(red,0,4095,0,255));
       setPatamar(map(red,0,4095,0,255),map(green,0,4095,0,255),map(blue,0,4095,0,255));
//      
   
  }
}


//manda o numero o valor da posicao (0 a 47) e da intensidade (0 a 4095)
void setIntensity(uint8_t pos, int intensity){
//  Serial.print("pos: ");
//  Serial.println(pos);
  //Serial.print("intensity:");
  //Serial.println(intensity);
        if(pos<=15){
          board1.setPWM(pos,0,intensity);}
        else if(pos>15 && pos<=31){
          board2.setPWM(pos%16, 0, intensity);}
        else{
          board3.setPWM(pos%32, 0, intensity);}
}


void crossFade() {
  int randomNumber = random(16);
  customLoop = true;
  unsigned long previousMillis = 0;
  // Convert to 0-255
  int R = AVAILABLE_COLORS[randomNumber][0];
  int G = AVAILABLE_COLORS[randomNumber][1];
  int B = AVAILABLE_COLORS[randomNumber][2];

  int stepR = calculateStep(prevR, R);
  int stepG = calculateStep(prevG, G);
  int stepB = calculateStep(prevB, B);
  int i = 0;
  while (i <= 256) {
    if (irrecv.decode(&results)) {
      if (existsInArray(results.value, AVAILABLE_CODES, 24) && results.value != INTENSITY_UP_CODE && results.value !=  INTENSITY_DN_CODE && results.value != SMOOTH_CODE) {
        Serial.println("return break");
        return; break;
        interpretRemoteCode(results.value);
      } else if (results.value == INTENSITY_UP_CODE) {
        raiseIntensity();
      } else if (results.value == INTENSITY_DN_CODE) {
        lowerIntensity();
      }
      irrecv.resume();
    }
    unsigned long currentMillis = millis();
    mappedSpeed = map(speedValue, 10, 1, 50, 150);

    if (currentMillis - previousMillis >= mappedSpeed) {
      previousMillis = currentMillis;
      redVal = calculateVal(stepR, redVal, i);
      grnVal = calculateVal(stepG, grnVal, i);
      bluVal = calculateVal(stepB, bluVal, i);
      setColorAllSteps(redVal,grnVal,bluVal);
      i++;
      if (i == 257) {
        prevR = redVal;
        prevG = grnVal;
        prevB = bluVal;
        crossFade();
      }
    }
  }
}
