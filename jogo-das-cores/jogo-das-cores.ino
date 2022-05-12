#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int RED = 0;
const int YELLOW = 1;
const int BLUE = 2;
const int GREEN = 3;
const int PINS_LEDS[] = {9,8,7,6};

const int BUTTON_RED = A0;
const int BUTTON_YELLOW = A1;
const int BUTTON_BLUE = A2;
const int BUTTON_GREEN = A3;
const int BUTTON_RESET = A5;

int listOrder[] = {BLUE,BLUE,RED,GREEN,YELLOW,BLUE,YELLOW,RED,YELLOW,GREEN,BLUE,RED,BLUE,BLUE,GREEN,YELLOW,YELLOW,RED,GREEN,GREEN};

bool isOrderNow = false;
bool endGame = false;
int positionOrder = 0;
int sizeListOrderNow = 0;
int sizeListOrder = 0;
int life = 3;

void setup() {
  lcd.begin(16, 2);
  sizeListOrder = (sizeof(listOrder) / sizeof(listOrder[0]));
  sizeListOrderNow =  1;
  PrintLevelGame();
  PrintLifePlayer();
  for(int i = 0; i<4;i++){
    pinMode(PINS_LEDS[i],OUTPUT);
  }
  delay(2000);
}

void loop() {
  if(isOrderNow == false){
    for(int i = 0; i<sizeListOrderNow; i++){
      EnableLed(i);
    }
    isOrderNow = true;
  }
  else{
    if(digitalRead(BUTTON_RESET) == HIGH){
      ResetGame();
      return;
    }
    else if(endGame == false){
      if(digitalRead(BUTTON_RED) == HIGH){
        if(CompareColor(RED)==false){return;}
      }
      else if(digitalRead(BUTTON_YELLOW) == HIGH){
        if(CompareColor(YELLOW)==false){return;}
      }
      else if(digitalRead(BUTTON_BLUE) == HIGH){
        if(CompareColor(BLUE)==false){return;}
      }
      else if(digitalRead(BUTTON_GREEN) == HIGH){
        if(CompareColor(GREEN)==false){return;}
      }
      if(positionOrder == sizeListOrderNow){
        EnbleOrDisableLED(HIGH);
        NextLevel();
      }
    }
  }
}

void EnableLed(int indexLed){
  digitalWrite(PINS_LEDS[listOrder[indexLed]], HIGH);
  delay(1000);
  digitalWrite(PINS_LEDS[listOrder[indexLed]], LOW);
  delay(500);
}

void RestartSequenceGame(){
  if(life>0){
    positionOrder = 0;
    isOrderNow = false;
    EnbleOrDisableLED(LOW);
    delay(2000);
  }
  else{
    PrintGameOver();
    delay(3000);
    ResetGame();
  }
}

void NextLevel(){
  sizeListOrderNow++;
  delay(3000);
  if(sizeListOrderNow <= sizeListOrder){
    PrintLevelGame();
    RestartSequenceGame();
  }
  else{
    endGame = true;
    PrintEndGame();
  }
}

void ResetGame(){
  endGame = false;
  sizeListOrderNow = 1;
  life = 3;
  lcd.clear();
  PrintLifePlayer();
  PrintLevelGame();
  RestartSequenceGame();
}

void PrintLevelGame(){
  lcd.setCursor(0,0);
  lcd.print("Nivel: "+String(sizeListOrderNow));
}

void PrintEndGame(){
  lcd.setCursor(0,1);
  lcd.print("  Fim de jogo   ");
}

void PrintGameOver(){
  lcd.setCursor(0,0);
  lcd.print("      Game      ");
  lcd.setCursor(0,1);
  lcd.print("      Over      ");
}

void PrintLifePlayer(){
  lcd.setCursor(0,1);
  switch(life){
    case 3:
    lcd.print("Vida : ###      ");
    break;
    case 2:
    lcd.print("Vida : ##       ");
    break;
    case 1:
    lcd.print("Vida : #        ");
    break;
    default:
    lcd.print("Vida :          ");
    break;
  }
}

void WrongSequence(){
  life--;
  PrintLifePlayer();
  RestartSequenceGame();
}

bool CompareColor(int colorLed){
  for(int i = positionOrder; i<sizeListOrderNow;i++){
    if(colorLed == listOrder[positionOrder]){
      positionOrder++;
      EnableLed(i);
      return true;
    }
    WrongSequence();
    return false;
  }
}

void EnbleOrDisableLED(int value){
  for(int i = 0; i<4;i++){
    digitalWrite(PINS_LEDS[i], value);
  }
}
