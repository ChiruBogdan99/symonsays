#include <LedControl.h>
#include <LiquidCrystal.h>
LedControl lc = LedControl( 12, 11, 10, 1);
LiquidCrystal lcd(A5, A4, A0, A1, A2, A3);
#define V0_PIN 9
const int buttonPinU = 2;
const int buttonPinD = 3;
const int buttonPinL = 4;
const int buttonPinR = 5;
const int redPin = 6;
const int greenPin = 7;
const int bluePin = 8;
int buttonStateU = 0, buttonStateD = 0, buttonStateR = 0, buttonStateL = 0;
unsigned long startMillis, currentMillis, lcdMillis, startLcdMillis;
const unsigned long period;
const int MAX_LEVEL = 100;
int sequence[MAX_LEVEL],player_sequence[MAX_LEVEL], level = 1, score = 10;
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

byte H[8] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
};

byte S[8] = {
  B00000,
  B01010,
  B00000,
  B00000,
  B01110,
  B10001,
  B00000,
  B00000,
};

void GOOD(){
    int i;
    for ( i = 0; i < 8; i++ )
        lc.setColumn(0, i, G[i]);
    delay(500);
    lc.clearDisplay(0); 
    if ( level < MAX_LEVEL )
            {level++;
            score = score + 10;
            if(level % 5 == 0)
            score = score + 500;}
}

void X(){
  int i;
  for ( i = 0; i < 8; i++ )
    lc.setColumn(0, i, x[i]);
  delay(500);
  lc.clearDisplay(0);   
  level = 1;
  score = 10;
  lcdMillis = millis();
  if( lcdMillis - startLcdMillis >=1500)
  {
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("Try again, bro");
    lcd.print(char(2));
    startLcdMillis = lcdMillis;
  }
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
  lcd.createChar(1, H);
  lcd.createChar(2, S);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(2, 1);
  lc.shutdown(0, false);
  lc.setIntensity(0, 7);
  lc.clearDisplay(0);
  startMillis = millis();
  startLcdMillis = millis();
  pinMode(V0_PIN, OUTPUT);
  analogWrite(V0_PIN, 90);
}

void loop()
{
   lcdMillis = millis();
   if( lcdMillis - startLcdMillis >= 1000 )
   { 
     lcd.clear();
     lcd.print("Welcome, bro ");
     lcd.print(char(1));
     lcd.print(char(1));
   if( level == 1)
   { 
        generate_sequence();
        ALL();
       
    }
       startLcdMillis = lcdMillis;
   }                
       
   currentMillis = millis();
   if( currentMillis - startMillis >= 500 && ( digitalRead(buttonPinU) == HIGH || level != 1 ))
   { 
       
       show_sequence();
       get_sequence();
       lcdMillis = millis();
       if( lcdMillis - startLcdMillis >=500) 
       {
       lcd.clear(); 
       lcd.print("LEVEL ");
       lcd.print(level);
       lcd.setCursor(0, 2);
       lcd.print("SCORE ");
       lcd.print(score); 
       startLcdMillis = lcdMillis;
       }       
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
