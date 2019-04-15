#include <IRremote.h>

int recvPin = 8; // IR Receiver - Arduino Pin Number 8
int redPin = 13; // RED Output Pin
int greenPin = 12; // GREEN Output Pin
int bluePin = 11; // BLUE Output Pin
int intensity = 10; // Intensity variable
int speedValue = 5; // Speed Variable
int currentColors[] = {0, 0, 0}; // Current Color outputed variable (black by default)
bool customLoop = false; // Variable telling us we are in a custom animation loop
unsigned long previousMillis = 0; // variable for the delay function
int RECV_PIN = 8;

IRrecv irrecv(RECV_PIN);
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

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    findCode(results.value);
  }
  delay(100);
}

// function for interpreting the incoming code and eighter setting a fixed color or starting a custom loop function
void interpretRemoteCode(int code) {
  int randomColor[3] = {random(256), random(256), random(256)};
  switch (code) {
    case ON_CODE: setColor(randomColor); break;
    case OFF_CODE: setColor(BLACK_COLOR); break;
    //case INTENSITY_UP_CODE: raiseIntensity(); break;
    //case INTENSITY_DN_CODE: lowerIntensity(); break;
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
      //case FLASH_CODE: flash(); break;
      //case STROBE_CODE: strobe(); break;
      //case FADE_CODE: fade(); break;
      //case SMOOTH_CODE: crossFade(); break;
  }
}

// set the currentColors variable
void setColor(int colors[]) {
  currentColors[0] = colors[0];
  currentColors[1] = colors[1];
  currentColors[2] = colors[2];
}

// decode remote controll code and if found in the array of available codes interpret it
void findCode(int code) {

  if (existsInArray(code, AVAILABLE_CODES, 24)) {
    //Serial.print("Code Found: ");
    //Serial.println(code,HEX);
    interpretRemoteCode(code);
    if (code != FLASH_CODE && code != STROBE_CODE && code != FADE_CODE && code != SMOOTH_CODE) {
      customLoop = false;
      sendColor();
    }
  } else {
    //Serial.print("Invalid Code: ");
    //Serial.println(code,HEX);
  }
}

// calculate the intensity and send the current color out via the output pins
void sendColor()
{
  if (customLoop == false) {
    int red = currentColors[0];
    int green = currentColors[1];
    int blue = currentColors[2];

    int mappedIntensity = map(intensity, 0, 10, 0, 255);
    int redComputed = map(red, 0, 255, 0, mappedIntensity);
    int blueComputed = map(blue, 0, 255, 0, mappedIntensity);
    int greenComputed = map(green, 0, 255, 0, mappedIntensity);

    analogWrite(redPin, redComputed); // Sends PWM signal to the Red pin
    analogWrite(greenPin, greenComputed);
    analogWrite(bluePin, blueComputed);
  Serial.print("redpin ");
  Serial.print(redPin);
  Serial.print(" greenpin ");
  Serial.print(greenPin);
  Serial.print(" bluepin ");
  Serial.print(bluePin);
  Serial.print(" redComputed ");
  Serial.print(redComputed);
  Serial.print(" greenComputed ");
  Serial.print(greenComputed);
  Serial.print(" blueComputed ");
  Serial.println(blueComputed);
//  
//    analogWrite(redPin, 100); // Sends PWM signal to the Red pin
//    analogWrite(greenPin, 100);
//    analogWrite(bluePin, 0);
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
