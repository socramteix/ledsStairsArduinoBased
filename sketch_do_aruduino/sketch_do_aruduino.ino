#include <IRremote.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver board3 = Adafruit_PWMServoDriver(0x42);
//comentario 2
int sensorPin = A0;
int recvPin = 8; // IR Receiver - Arduino Pin Number 8
int redPin = 2; // RED Output Pin
int greenPin = 3; // GREEN Output Pin
int bluePin = 4; // BLUE Output Pin
int intensity = 10; // Intensity variable
int speedValue = 5; // Speed Variable
int currentColors[] = {0, 0, 0}; // Current Color outputed variable (black by default)
bool customLoop = false; // Variable telling us we are in a custom animation loop
unsigned long previousMillis = 0; // variable for the delay function

// our servo # counter
uint8_t servonum = 0;
char inChar = '0';
int cont=-1;

//as linhas sao os degraus e as colunas as cores R, G e B
int degraus[16][3] = {
{12,33,32},
{6,5,8},
{29,28,30},
{38,37,39},
{41,40,42},
{22,23,24},
{4,3,7},
{45,46,47},
{14,13,15},
{44,43,31},
{25,27,26},
{0,1,2},
{19,20,21},
{34,35,36},
{17,18,16},
{11,9,10}};

IRrecv irrecv(recvPin);
decode_results results;

// Defining hex codes for the remote
#define ON_CODE           0xF7C03F
#define OFF_CODE          0xF740BF
#define INTENSITY_UP_CODE 0xF700FF
#define INTENSITY_DN_CODE 0xF7807F
#define RED_CODE          0xF720DF
#define GREEN_CODE        0xF7A05F
#define BLUE_CODE         0xF7609F
#define WHITE_CODE        0xF7E01F
#define ORANGE_CODE       0xF710EF
#define TURQUOISE_CODE    0xF7906F
#define NAVY_CODE         0xF750AF
#define BROWN_CODE        0xF730CF
#define TEAL_CODE         0xF7B04F
#define PURPLE_DARK_CODE  0xF7708F
#define ORANGE_LIGHT_CODE 0xF708F7
#define BLUE_LIGHT_CODE   0xF78877
#define PINK_DARK_CODE    0xF748B7
#define YELLOW_CODE       0xF728D7
#define BLUE_BABY_CODE    0xF7A857
#define PINK_CODE         0xF76897
#define FLASH_CODE        0xF7D02F
#define STROBE_CODE       0xF7F00F
#define FADE_CODE         0xF7C837
#define SMOOTH_CODE       0xF7E817
#define REPEATED          0xFFFFFFFF

// defining the avaialble colors one by one
int BLACK_COLOR[3] = {0, 0, 0};
int RED_COLOR[3] = {255, 0, 0};
int GREEN_COLOR[3] = {0, 255, 0};
int BLUE_COLOR[3] =  {0, 0, 255};
int WHITE_COLOR[3] = {255, 255, 255};
int ORANGE_COLOR[3] = {255, 128, 0};
int TURQUOISE_COLOR[3] = {0, 255, 128};
int NAVY_COLOR[3] = {0, 76, 153};
int BROWN_COLOR[3] = {153, 76, 0};
int TEAL_COLOR[3] = {0, 102, 102};
int PURPLE_DARK_COLOR[3] = {102, 0, 51};
int ORANGE_LIGHT_COLOR[3] = {255, 153, 51};
int BLUE_LIGHT_COLOR[3] = {0, 255, 255};
int PINK_DARK_COLOR[3] = {255, 0, 128};
int YELLOW_COLOR[3] = {255, 255, 0};
int BLUE_BABY_COLOR[3] = {51, 153, 255};
int PINK_COLOR[3] = {255, 102, 178};

// defining all the available remote codes in an array
int AVAILABLE_CODES[24] = {ON_CODE, OFF_CODE, INTENSITY_UP_CODE, INTENSITY_DN_CODE, RED_CODE, GREEN_CODE, BLUE_CODE, WHITE_CODE, ORANGE_CODE, TURQUOISE_CODE, NAVY_CODE, BROWN_CODE, TEAL_CODE, PURPLE_DARK_CODE, ORANGE_LIGHT_CODE, BLUE_LIGHT_CODE, PINK_DARK_CODE, YELLOW_CODE, BLUE_BABY_CODE, PINK_CODE, FLASH_CODE, FADE_CODE, SMOOTH_CODE, STROBE_CODE};

// defining all the available colors in an array
int AVAILABLE_COLORS[16][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {255, 128, 0}, {0, 255, 128}, {0, 76, 153}, {153, 76, 0}, {0, 102, 102}, {102, 0, 51}, {255, 153, 51}, {0, 255, 255}, {255, 0, 127}, {255, 255, 0}, {51, 153, 255}, {255, 102, 158}} ;

unsigned long currentMillis;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(sensorPin, INPUT);
  board1.begin();
  board2.begin();
  board3.begin();

  board1.setPWMFreq(490);  // Analog servos run at ~60 Hz updates
  board2.setPWMFreq(490);
  board3.setPWMFreq(490);

  delay(10);
}

// function for interpreting the incoming code and eighter setting a fixed color or starting a custom loop function
void interpretRemoteCode(int code) {
  int randomColor[3] = {random(256), random(256), random(256)};
  switch (code) {
    case ON_CODE: setColor(randomColor); break;
    case OFF_CODE: setColor(BLACK_COLOR); break;
    case INTENSITY_UP_CODE: raiseIntensity(); break;
    case INTENSITY_DN_CODE: lowerIntensity(); break;
    case RED_CODE: setColor(RED_COLOR); break;
    case GREEN_CODE: setColor(GREEN_COLOR); break;
    case BLUE_CODE: setColor(BLUE_COLOR); break;
    case WHITE_CODE: setColor(WHITE_COLOR); break;
    case ORANGE_CODE: setColor(ORANGE_COLOR); break;
    case TURQUOISE_CODE: setColor(TURQUOISE_COLOR); break;
    case NAVY_CODE: setColor(NAVY_COLOR); break;
    case BROWN_CODE: setColor(BROWN_COLOR); break;
    case TEAL_CODE: setColor(TEAL_COLOR); break;
    case PURPLE_DARK_CODE: setColor(PURPLE_DARK_COLOR); break;
    case ORANGE_LIGHT_CODE: setColor(ORANGE_LIGHT_COLOR); break;
    case BLUE_LIGHT_CODE: setColor(BLUE_LIGHT_COLOR); break;
    case PINK_DARK_CODE: setColor(PINK_DARK_COLOR); break;
    case YELLOW_CODE: setColor(YELLOW_COLOR); break;
    case BLUE_BABY_CODE: setColor(BLUE_BABY_COLOR); break;
    case PINK_CODE: setColor(PINK_COLOR); break;
    case FLASH_CODE: flash(); break;
    case STROBE_CODE: strobe(); break;
    case FADE_CODE: fade(); break;
    case SMOOTH_CODE: crossFade(); break;
  }
}

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

// helper function to check if a value is present in an array
int existsInArray(int compareValue, int arrayName[], int arraySize) {
  for (int x = 0; x < arraySize; x = x + 1) {
    if (arrayName[x] == compareValue) {
      return true;
    }
  }
  return false;
}

// set the currentColors variable
void setColor(int colors[]) {
  currentColors[0] = colors[0];
  currentColors[1] = colors[1];
  currentColors[2] = colors[2];
}

// calculate the intensity and send the current color out via the output pins
void sendColor()
{
  if (customLoop == false) {
    int red = currentColors[0];
    int green = currentColors[1];
    int blue = currentColors[2];

    int mappedIntensity = map(intensity, 0, 10, 0, 4095);
    int redComputed = map(red, 0, 255, 0, mappedIntensity);
    int blueComputed = map(blue, 0, 255, 0, mappedIntensity);
    int greenComputed = map(green, 0, 255, 0, mappedIntensity);

    analogWrite(redPin, redComputed); // Sends PWM signal to the Red pin
    analogWrite(greenPin, greenComputed);
    analogWrite(bluePin, blueComputed);

    setColor(redComputed,greenComputed,blueComputed);
//    for (uint8_t servonum = 0; servonum < 16; servonum++) {
//        board1.setPWM(servonum, 0, redComputed);
//        board2.setPWM(servonum, 0, blueComputed);
//        board3.setPWM(servonum, 0, greenComputed);
//    }
  }
}

// decode remote controll code and if found in the array of available codes interpret it
void findCode() {
  
  if (irrecv.decode(&results)) {
//    if(results.value == REPEATED){
//      Serial.println(results.value,HEX);
//      results.value = last_value;
//    } //eu que coloquei esse if pra tentar resolver o problema do invalid code
    if (existsInArray(results.value, AVAILABLE_CODES, 24)) {
      Serial.print("Code Found: ");
      Serial.println(results.value,HEX);
      interpretRemoteCode(results.value);
      if (results.value != FLASH_CODE && results.value != STROBE_CODE && results.value != FADE_CODE && results.value != SMOOTH_CODE) {
        customLoop = false;
        sendColor();
      }
    } else {
      Serial.print("Invalid Code: ");
      Serial.println(results.value,HEX);
    }
    irrecv.resume();
  }
  
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
    int randomNumber = random(16); // get a random number from 0 to 16
    
    // set temporary variales for the red, green and blue values
    int red = AVAILABLE_COLORS[randomNumber][0];
    int green = AVAILABLE_COLORS[randomNumber][1];
    int blue = AVAILABLE_COLORS[randomNumber][2];
    unsigned long currentMillis = millis();
    
    // set a X animation delay from 200 to 3000 milliseconds based on the speed variable
    int mappedSpeed = map(speedValue, 10, 1, 200, 3000);
    
    // every X milliseconds
    if (currentMillis - previousMillis >= mappedSpeed) {
      previousMillis = currentMillis;
      
      // send the color variables through the digital ouput pins 
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);

      int mappedRed = map(red, 0, 255, 0, 4095);
      int mappedGreen = map(green, 0, 255, 0, 4095);
      int mappedBlue = map(blue, 0, 255, 0, 4095);

      setColor(mappedRed,mappedGreen,mappedBlue);

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
    int randomNumber = random(16);
    int red = AVAILABLE_COLORS[randomNumber][0];
    int green = AVAILABLE_COLORS[randomNumber][1];
    int blue = AVAILABLE_COLORS[randomNumber][2];
    unsigned long currentMillis = millis();
    int mappedSpeed = map(speedValue, 10, 1, 50, 1500);
    int mappedRed;
    int mappedGreen;
    int mappedBlue;
    if (currentMillis - previousMillis >= mappedSpeed) {
      previousMillis = currentMillis;
      if ( (i % 2) == 0) {
        analogWrite(redPin, red); // Sends PWM signal to the Red pin
        analogWrite(greenPin, green);
        analogWrite(bluePin, blue);
        mappedRed = map(red, 0, 255, 0, 4095);
        mappedGreen = map(green, 0, 255, 0, 4095);
        mappedBlue = map(blue, 0, 255, 0, 4095);

        setColor(mappedRed,mappedGreen,mappedBlue);
        
//        for (uint8_t servonum = 0; servonum < 16; servonum++) {
//          board1.setPWM(servonum, 0, mappedRed);
//          board2.setPWM(servonum, 0, mappedGreen);
//          board3.setPWM(servonum, 0, mappedBlue);
//        }
      } else {
          setColor(0,0,0);
//          for (uint8_t servonum = 0; servonum < 16; servonum++) {
//            board1.setPWM(servonum, 0, 0);
//            board2.setPWM(servonum, 0, 0);
//            board3.setPWM(servonum, 0, 0);
//          }
          analogWrite(redPin, 0); // Sends PWM signal to the Red pin
          analogWrite(greenPin, 0);
          analogWrite(bluePin, 0);
      }
      i++;
    }
  }
}

void fade() {
  customLoop = true;
  unsigned long previousMillis = 0;
  int i = 1;
  int randomNumber = random(16);
  int red = AVAILABLE_COLORS[randomNumber][0];
  int green = AVAILABLE_COLORS[randomNumber][1];
  int blue = AVAILABLE_COLORS[randomNumber][2];
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
    int mappedSpeed = map(speedValue, 10, 1, 10, 100);
    if (currentMillis - previousMillis >= mappedSpeed) {
      previousMillis = currentMillis;
      int mappedRedIntensity = map(i, 0, 255, 0, red);
      int mappedRed = red != 0 ? map(red, 0, red, 0, mappedRedIntensity) : 0;
      int mappedGreenIntensity = map(i, 0, 255, 0, green);
      int mappedGreen = green != 0 ? map(green, 0, green, 0, mappedGreenIntensity) : 0;
      int mappedBlueIntensity = map(i, 0, 255, 0, blue);
      int mappedBlue = blue != 0 ? map(blue, 0, blue, 0, mappedBlueIntensity) : 0;
      analogWrite(redPin, mappedRed);
      analogWrite(greenPin, mappedGreen);
      analogWrite(bluePin, mappedBlue);
      i++;
      
      mappedRed = map(mappedRed, 0, 255, 0, 4095);
      mappedGreen = map(mappedGreen, 0, 255, 0, 4095);
      mappedBlue = map(mappedBlue, 0, 255, 0, 4095);

      setColor(mappedRed,mappedGreen,mappedBlue);
      
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
    int mappedSpeed = map(speedValue, 10, 1, 10, 100);
    if (currentMillis - previousMillis >= mappedSpeed) {
      previousMillis = currentMillis;
      int mappedRedIntensity = map(i, 0, 255, 0, red);
      int mappedRed = red != 0 ? map(red, 0, red, 0, mappedRedIntensity) : 0;
      int mappedGreenIntensity = map(i, 0, 255, 0, green);
      int mappedGreen = green != 0 ? map(green, 0, green, 0, mappedGreenIntensity) : 0;
      int mappedBlueIntensity = map(i, 0, 255, 0, blue);
      int mappedBlue = blue != 0 ? map(blue, 0, blue, 0, mappedBlueIntensity) : 0;
      analogWrite(redPin, mappedRed);
      analogWrite(greenPin, mappedGreen);
      analogWrite(bluePin, mappedBlue);
      
      mappedRed = map(mappedRed, 0, 255, 0, 4095);
      mappedGreen = map(mappedGreen, 0, 255, 0, 4095);
      mappedBlue = map(mappedBlue, 0, 255, 0, 4095);

      setColor(mappedRed,mappedGreen,mappedBlue);
      
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

int calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;
    }
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    }
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  }
  else if (val < 0) {
    val = 0;
  }
  return val;
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
    int mappedSpeed = map(speedValue, 10, 1, 50, 150);

    if (currentMillis - previousMillis >= mappedSpeed) {
      previousMillis = currentMillis;
      redVal = calculateVal(stepR, redVal, i);
      grnVal = calculateVal(stepG, grnVal, i);
      bluVal = calculateVal(stepB, bluVal, i);
      analogWrite(redPin, redVal);   // Write current values to LED pins
      analogWrite(greenPin, grnVal);
      analogWrite(bluePin, bluVal);
      setColor(redVal,grnVal,bluVal);
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

//manda o numero o valor da posicao (0 a 47) e da intensidade (0 a 4095)
void setIntensity(int pos, int intensity){
        if(pos<16){
          board1.setPWM(pos, 0, intensity);}
        else if(cont>15 && cont<32){
          board2.setPWM(pos%16, 0, intensity);}
        else{
          board3.setPWM(pos%32, 0, intensity);}
}

void setColor(int red, int green, int blue){

  //para a cor vermelha
  for(int j=0;j<16;j++){
      setIntensity(degraus[j][0],red);
      //Serial.print("red: ");
      //Serial.print(degraus[j][0]);
      setIntensity(degraus[j][1],green);
      //Serial.print(" green: ");
      //Serial.print(degraus[j][1]);
      setIntensity(degraus[j][2],blue);
      //Serial.print(" blue: ");
      //Serial.println(degraus[j][2]);
  }
}

//envie 1 para incrementar e outra coisa para reiniciar
void mapear(){
 while (Serial.available()) {
      inChar = (char)Serial.read();
      Serial.println(inChar);
      if (inChar == '1') {
        for (uint8_t pos = 0; pos < 48; pos++) {
          setIntensity(pos, 0);
        }
        cont++;
        Serial.println(cont);
        setIntensity(cont, 4095);
      }
      else if(inChar == '\n'){}
      else if(inChar == 'r'){setColor(4095,0,0);}
      else if(inChar == 'g'){setColor(0,4095,0);}
      else if(inChar == 'b'){setColor(0,0,4095);}
      else if(inChar == 'a'){
        for (uint8_t servonum = 0; servonum < 16; servonum++) {
          board1.setPWM(servonum, 0, 4095);
          board2.setPWM(servonum, 0, 4095);
          board3.setPWM(servonum, 0, 4095);
        }
      }
      else if(inChar == 'x'){
        for (uint8_t servonum = 0; servonum < 16; servonum++) {
          board1.setPWM(servonum, 0, 0);
          board2.setPWM(servonum, 0, 0);
          board3.setPWM(servonum, 0, 0);
        }
      }
      else{
        Serial.println("else");
        cont=-1;
      }
  }
}

void iniciarEscada(){
  for(int j=0;j<16;j++){
    setIntensity(degraus[j][0],4095);
    setIntensity(degraus[j][1],4095);
    setIntensity(degraus[j][2],4095);
    delay(100);
  }
  for(int i=0;i<16;i++)
    delay(1000);
  for(int j=15;j>=0;j--){
    setIntensity(degraus[j][0],0);
    setIntensity(degraus[j][1],0);
    setIntensity(degraus[j][2],0);
    delay(100);
  }
}

// check for a code from the remote every 100 milliseconds
void loop() {
  currentMillis = millis();
  if(analogRead(sensorPin) == 0)
    iniciarEscada();
  if (currentMillis - previousMillis >= 100) {
    previousMillis = currentMillis;
    findCode();
  }
  mapear(); //chame essa funcao para descobrir qual cor esta em cada degrau

}