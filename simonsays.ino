#include <LedControl.h>
LedControl lc = LedControl(12, 11, 10, 1);
const int buttonPinU = 2;
const int buttonPinD = 3;
const int buttonPinL = 4;
const int buttonPinR = 5;
const int redPin = 6;
const int greenPin = 7;
const int bluePin = 8;
int buttonStateU=0, buttonStateD=0, buttonStateR=0, buttonStateL=0;
unsigned long startMillis, currentMillis;
const unsigned long period ;
const int MAX_LEVEL = 100;
int sequence[MAX_LEVEL],player_sequence[MAX_LEVEL], level = 1, counter = 0;
byte U[8] = {
  B00000000,
  B00100000,
  B01100000,
  B11111111,
  B11111111,
  B01100000,
  B00100000,
  B00000000,
};

byte R[8] = {
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B01111110,
  B00111100,
  B00011000,
};

byte D[8] = {
  B00000000,
  B00000100,
  B00000110,
  B11111111,
  B11111111,
  B00000110,
  B00000100,
  B00000000,
};

byte L[8] = {
  B00011000,
  B00111100,
  B01111110,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
};

byte G[8] = {
  B00010100,
  B00001010,
  B00000101,
  B00001010,
  B00010100,
  B00101000,
  B01010000,
  B10100000,
};

byte x[8] = {
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001,
};

byte A[8] = {
  B11000011,
  B11000011,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B11000011,
  B11000011,
};

void GOOD(){
    int i;
    for ( i = 0; i < 8; i++ )
        lc.setColumn(0, i, G[i]);
    delay(500);
    lc.clearDisplay(0); 
    if ( level < MAX_LEVEL )
            level++;
}

void X(){
  int i;
  for ( i = 0; i < 8; i++ )
    lc.setColumn(0, i, x[i]);
  delay(500);
  lc.clearDisplay(0);   
  level = 1;
}

void ALL(){
  int i;
  for ( i = 0; i < 8; i++ )
    lc.setColumn(0, i, A[i]);
  delay(500);
  lc.clearDisplay(0);   
}

void UP() {
  int i;
  for ( i = 0; i < 8; i++ )
    lc.setColumn(0, i, U[i]);
  delay(500);
  lc.clearDisplay(0);
}

void RIGHT() {
  int i;
  for ( i = 0; i < 8; i++ )
    lc.setColumn(0, i, R[i]);
  delay(500);
  lc.clearDisplay(0);
}

void DOWN() {
  int i;
  for ( i = 0; i < 8; i++ )
    lc.setColumn(0, i, D[i]);
  delay(500);
  lc.clearDisplay(0);
}

void LEFT() {
  int i;
  for ( i = 0; i < 8; i++ )
    lc.setColumn(0, i, L[i]);
  delay(500);
  lc.clearDisplay(0);
}

void setup()
{
  pinMode(buttonPinU, INPUT);
  pinMode(buttonPinD, INPUT);
  pinMode(buttonPinL, INPUT);
  pinMode(buttonPinR, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.setIntensity(0, 7);
  lc.clearDisplay(0);
  startMillis = millis();
  
}

void loop()
{
   if( level == 1)
   { 
        generate_sequence();
        ALL();
    }
   currentMillis = millis();
   if( currentMillis - startMillis >= 500 && ( digitalRead(buttonPinU) == HIGH || level != 1 ))
   { 
       show_sequence();
       get_sequence();
       startMillis = currentMillis;
   }                  
                                                                                                                                                                                                                                                                                                                                                    
}

void generate_sequence()
{
  randomSeed(millis());
  int i;
  for( i = 0; i < MAX_LEVEL; i++)
  {
    sequence[i] = random(1,5);
  }
}

void show_sequence()
{
  int i;
  for( i = 0; i < level; i++)
  {
    currentMillis = millis();
    if( currentMillis - startMillis >= 500 && sequence[i] == 1)
          UP();
    if( currentMillis - startMillis >= 500 && sequence[i] == 2)
          DOWN();
    if( currentMillis - startMillis >= 500 && sequence[i] == 3)
          LEFT();
    if( currentMillis - startMillis >= 500 && sequence[i] == 4)
          RIGHT();
         startMillis = currentMillis;
   }
   Serial.println(sequence[i]);
  }

void get_sequence()
{
  int i, ok = 0; 
  for( i = 0; i < level; i++)
  {
    ok = 0;
    while( ok == 0)
    {
      if ( digitalRead(buttonPinU) == HIGH )
      {
        UP();
        digitalWrite(redPin,HIGH);
        delay(100);
        digitalWrite(redPin,LOW);
        player_sequence[i] = 1;
        ok = 1;
        delay(500);
        if( player_sequence[i] != sequence[i])
              {
               X();
               return;
              }
      }

      if ( digitalRead(buttonPinD) == HIGH)
      {
        DOWN();
        digitalWrite(greenPin,HIGH);
        delay(100);
        digitalWrite(greenPin,LOW);
        player_sequence[i] = 2;
        ok = 1;
        delay(500);
        if( player_sequence[i] != sequence[i])
              {
               X();
               return;
              }
      }

      if ( digitalRead(buttonPinL) == HIGH )
      {
        LEFT();
        digitalWrite(bluePin,HIGH);
        delay(100);
        digitalWrite(bluePin,LOW);
        player_sequence[i] = 3;
        ok = 1;
        delay(500);
        if( player_sequence[i] != sequence[i])
              {
               X();
               return;
              }
      }

      if ( digitalRead(buttonPinR) == HIGH )
      {
        RIGHT();
        digitalWrite(bluePin,HIGH);
        digitalWrite(redPin,HIGH);
        delay(100);
        digitalWrite(bluePin,LOW);
        digitalWrite(redPin,LOW);
        player_sequence[i] = 4;
        ok = 1;
        delay(500);
        if( player_sequence[i] != sequence[i])
              {
               X();
               return;
              }
      }
    }
  }
  GOOD();
}
