#include <IRremote.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

int recvPin = 11; // IR Receiver - Arduino Pin Number 8
bool ligado; //verifies if the system are on or off
bool ligadoAnterior;
bool customLoop = false; // Variable telling us we are in a custom animation loop
int currentColors[] = {0, 0, 0}; // Current Color outputed variable (black by default)
int intensity = 10; // Intensity variable
char inChar = '0';
int cont=0;
int mappedSpeed ;
int speedValue = 5; // resumeSpeed Variable
int patamarValue = 0;
int patamar = 22;
int patamarRed = 9;
int patamarGreen = 10;
int patamarBlue = 8;
int sensorValue;
int sensorPin = A1;

// called this way, it uses the default address 0x40
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver board3 = Adafruit_PWMServoDriver(0x42);



boolean findCode();
int calculateVal(int step, int val, int i);

//the line are the steps and the columns the colors R, G e B
uint8_t degraus[16][3] = {
{17,18,16},
{32,12,33},
{27,26,25},
{41,40,42},
{7,4,2},
{29,30,28},
{3,1,0},
{6,8,5},
{34,36,35},
{23,22,24},
{10,11,9},
{13,15,14},
{38,37,39},
{19,21,20},
{46,47,45},
{31,44,43}};
/*int relePin = 52;
int sensorVcc = A0;
int valorVelhoPatamar = 0;
//int redPin = 8; // RED Output Pin
//int greenPin = 3; // GREEN Output Pin
//int bluePin = 4; // BLUE Output Pin

// our servo # counter
uint8_t servonum = 0;


*/
IRrecv irrecv(recvPin);
decode_results results;

unsigned long currentMillis;
unsigned long previousMillis = 0; // variable for the delay function

void setup() {
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  /*pinMode(relePin  , OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(sensorVcc, OUTPUT);
  pinMode(patamar      , INPUT);*/
  pinMode(patamarRed   , OUTPUT);
  pinMode(patamarGreen , OUTPUT);
  pinMode(patamarBlue  , OUTPUT);

  board1.begin();  // Analog servos run at ~60 Hz updates
  board2.begin();
  board3.begin();
  
  board1.setPWMFreq(490);  // Analog servos run at ~60 Hz updates
  board2.setPWMFreq(490);
  board3.setPWMFreq(490);

  //analogWrite(sensorVcc,255);
  //digitalWrite(relePin,HIGH);
  
  //interrupão para o controle
  //attachInterrupt(digitalPinToInterrupt(recvPin), loop, CHANGE);
  
  delay(2500); //esperar a fonte receber energia

  ligado = true;
  ligadoAnterior = false;
}

// function for interpreting the incoming code and eighter setting a fixed color or starting a custom loop function



// check for a code from the remote every 100 milliseconds
void loop() {

  /*patamarValue = digitalRead(patamar);
  patamarValue = digitalRead(patamar);
  patamarValue = digitalRead(patamar);*/
  //Serial.print("sensor: ");
  //Serial.println(sensorValue);
  //Serial.println(patamarValue);
  /*if(patamarValue == 1){
    if(valorVelhoPatamar == 0){
      setPatamar(255,255,255);
      valorVelhoPatamar = 1;
    }
  }
  else
    if(valorVelhoPatamar == 1){
      setPatamar(0,0,0);
      valorVelhoPatamar = 0;
    }
        */
  if(ligado){
    
    if(!ligadoAnterior){ //Se antes estava desligado
      Serial.println("ligando");
      efeito_ligando2();
      ligadoAnterior = true;
    }
    
    currentMillis = millis();
    if (currentMillis - previousMillis >= 100) {
      previousMillis = currentMillis;
      findCode(); //encontra o codigo do controle remoto
      
      sensorValue = analogRead(sensorPin);
      if(sensorValue < 500){
        //ligarFonte();
        subirEscada();
      }
      /*if (irrecv.decode(&results)) {
        Serial.print("Code Found: ");
        Serial.println(results.value,HEX);
        irrecv.resume();
      }*/
    }
    //mapear(); //chame essa funcao para descobrir qual cor esta em cada degrau
  }
  else{ delay(10); findCode(); ligadoAnterior = false; }
}
