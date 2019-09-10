// Defining hex codes for the remote
const long ON_CODE           = 0xF7C03F;
const long OFF_CODE          = 0xF740BF;
const long INTENSITY_UP_CODE = 0xF700FF;
const long INTENSITY_DN_CODE = 0xF7807F;
const long RED_CODE          = 0xF720DF;
const long GREEN_CODE        = 0xF7A05F;
const long BLUE_CODE         = 0xF7609F;
const long WHITE_CODE        = 0xF7E01F;
const long ORANGE_CODE       = 0xF710EF;
const long TURQUOISE_CODE    = 0xF7906F;
const long NAVY_CODE         = 0xF750AF;
const long BROWN_CODE        = 0xF730CF;
const long TEAL_CODE         = 0xF7B04F;
const long PURPLE_DARK_CODE  = 0xF7708F;
const long ORANGE_LIGHT_CODE = 0xF708F7;
const long BLUE_LIGHT_CODE   = 0xF78877;
const long PINK_DARK_CODE    = 0xF748B7;
const long YELLOW_CODE       = 0xF728D7;
const long BLUE_BABY_CODE    = 0xF7A857;
const long PINK_CODE         = 0xF76897;
const long FLASH_CODE        = 0xF7D02F;
const long STROBE_CODE       = 0xF7F00F;
const long FADE_CODE         = 0xF7C837;
const long SMOOTH_CODE       = 0xF7E817;
const long REPEATED          = 0xFFFFFFFF;

// defining the avaialble colors one by one
long BLACK_COLOR[3] = {0, 0, 0};
long RED_COLOR[3] = {255, 0, 0};
long GREEN_COLOR[3] = {0, 255, 0};
long BLUE_COLOR[3] =  {0, 0, 255};
long WHITE_COLOR[3] = {255, 255, 255};
long ORANGE_COLOR[3] = {255, 128, 0};
long TURQUOISE_COLOR[3] = {0, 255, 128};
long NAVY_COLOR[3] = {0, 76, 153};
long BROWN_COLOR[3] = {153, 76, 0};
long TEAL_COLOR[3] = {0, 102, 102};
long PURPLE_DARK_COLOR[3] = {102, 0, 51};
long ORANGE_LIGHT_COLOR[3] = {255, 153, 51};
long BLUE_LIGHT_COLOR[3] = {0, 255, 255};
long PINK_DARK_COLOR[3] = {255, 0, 128};
long YELLOW_COLOR[3] = {255, 255, 0};
long BLUE_BABY_COLOR[3] = {51, 153, 255};
long PINK_COLOR[3] = {255, 102, 178};

// defining all the available remote codes in an array
long AVAILABLE_CODES[24] = {ON_CODE, OFF_CODE, INTENSITY_UP_CODE, INTENSITY_DN_CODE, RED_CODE, GREEN_CODE, BLUE_CODE, WHITE_CODE, ORANGE_CODE, TURQUOISE_CODE, NAVY_CODE, BROWN_CODE, TEAL_CODE, PURPLE_DARK_CODE, ORANGE_LIGHT_CODE, BLUE_LIGHT_CODE, PINK_DARK_CODE, YELLOW_CODE, BLUE_BABY_CODE, PINK_CODE, FLASH_CODE, FADE_CODE, SMOOTH_CODE, STROBE_CODE};

// defining all the available colors in an array
long AVAILABLE_COLORS[16][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {255, 128, 0}, {0, 255, 128}, {0, 76, 153}, {153, 76, 0}, {0, 102, 102}, {102, 0, 51}, {255, 153, 51}, {0, 255, 255}, {255, 0, 127}, {255, 255, 0}, {51, 153, 255}, {255, 102, 158}} ;

long existsInArray(long compareValue, long arrayName[], long arraySize);

boolean findCode();

int calculateVal(int step, int val, int i);

void interpretRemoteCode(long code) {
  long randomColor[3] = {random(256), random(256), random(256)};
  switch (code) {
    case ON_CODE: ligado = true; break;
    case OFF_CODE: efeito_desligando(); ligado = false; break;
    case INTENSITY_UP_CODE: if(ligado){raiseIntensity();} break;
    case INTENSITY_DN_CODE: if(ligado){lowerIntensity();} break;
    case RED_CODE: if(ligado){setColor(RED_COLOR);} break;
    case GREEN_CODE: if(ligado){setColor(GREEN_COLOR);} break;
    case BLUE_CODE: if(ligado){setColor(BLUE_COLOR);} break;
    case WHITE_CODE: if(ligado){setColor(WHITE_COLOR);} break;
    case ORANGE_CODE: if(ligado){setColor(ORANGE_COLOR);} break;
    case TURQUOISE_CODE: if(ligado){setColor(TURQUOISE_COLOR);} break;
    case NAVY_CODE: if(ligado){setColor(NAVY_COLOR);} break;
    case BROWN_CODE: if(ligado){setColor(BROWN_COLOR);} break;
    case TEAL_CODE: if(ligado){setColor(TEAL_COLOR);} break;
    case PURPLE_DARK_CODE: if(ligado){setColor(PURPLE_DARK_COLOR);} break;
    case ORANGE_LIGHT_CODE: if(ligado){setColor(ORANGE_LIGHT_COLOR);} break;
    case BLUE_LIGHT_CODE: if(ligado){setColor(BLUE_LIGHT_COLOR);} break;
    case PINK_DARK_CODE: if(ligado){setColor(PINK_DARK_COLOR);} break;
    case YELLOW_CODE: if(ligado){setColor(YELLOW_COLOR);} break;
    case BLUE_BABY_CODE: if(ligado){setColor(BLUE_BABY_COLOR);} break;
    case PINK_CODE: if(ligado){setColor(PINK_COLOR);} break;
    case FLASH_CODE: if(ligado){flash();} break;
    case STROBE_CODE: if(ligado){strobe();} break;
    case FADE_CODE: if(ligado){fade();} break;
    case SMOOTH_CODE: if(ligado){crossFade();} break;
  }
}

// helper function to check if a value is present in an array
long existsInArray(long compareValue, long arrayName[], long arraySize) {
  for (int x = 0; x < arraySize; x = x + 1) {
    if (arrayName[x] == compareValue) {
      return true;
    }
  }
  return false;
}


// decode remote controll code and if found in the array of available codes interpret it
boolean findCode() {
  
  if (irrecv.decode(&results)) {
    if (existsInArray(results.value, AVAILABLE_CODES, 24)) {
      Serial.print("Code Found: ");
      Serial.println(results.value,HEX);
      interpretRemoteCode(results.value);
//      if (results.value != FLASH_CODE && results.value != STROBE_CODE && results.value != FADE_CODE && results.value != SMOOTH_CODE) {
//        customLoop = false;
//        sendColor();
//      }
    } else {
      Serial.print("Invalid Code: ");
      Serial.println(results.value,HEX);
    }
    irrecv.resume();
    return true;
  }
  else{return false;}
  
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
