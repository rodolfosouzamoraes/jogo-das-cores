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
const int PINS_BUTTONS[] = {BUTTON_RED,BUTTON_YELLOW,BUTTON_BLUE,BUTTON_GREEN};

int listOrder[] = {RED,BLUE,BLUE,GREEN,YELLOW,BLUE,RED,RED,YELLOW,GREEN};

bool isOrderNow = false;
bool endGame = false;
int positionOrder = 0;
int sizeListOrderNow = 0;
int sizeListOrder = 0;

void setup() {
  lcd.begin(16, 2);
  sizeListOrder = (sizeof(listOrder) / sizeof(listOrder[0]));
  sizeListOrderNow =  1;
  PrintLevelGame();
  for(int i = 0; i<4;i++){
    pinMode(PINS_BUTTONS[i],OUTPUT);
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
      if(digitalRead(PINS_BUTTONS[0]) == HIGH){
        for(int i = positionOrder; i<sizeListOrderNow;i++){
          if(0 == listOrder[positionOrder]){
            positionOrder++;
            EnableLed(i);
            break;
          }
          RestartSequenceGame();
          return;
        }
      }
      else if(digitalRead(PINS_BUTTONS[1]) == HIGH){
        for(int i = positionOrder; i<sizeListOrderNow;i++){
          if(1 == listOrder[positionOrder]){
            positionOrder++;
            EnableLed(i);
            break;
          }
          RestartSequenceGame();
          return;
        }
      }
      else if(digitalRead(PINS_BUTTONS[2]) == HIGH){
        for(int i = positionOrder; i<sizeListOrderNow;i++){
          if(2 == listOrder[positionOrder]){
            positionOrder++;
            EnableLed(i);
            break;
          }
          RestartSequenceGame();
          return;
        }
      }
      else if(digitalRead(PINS_BUTTONS[3]) == HIGH){
        for(int i = positionOrder; i<sizeListOrderNow;i++){
          if(3 == listOrder[positionOrder]){
            positionOrder++;
            EnableLed(i);
            break;
          }
          RestartSequenceGame();
          return;
        }
      }
      if(positionOrder == sizeListOrderNow){
        digitalWrite(PINS_LEDS[0], HIGH);
        digitalWrite(PINS_LEDS[1], HIGH);
        digitalWrite(PINS_LEDS[2], HIGH);
        digitalWrite(PINS_LEDS[3], HIGH);
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
  positionOrder = 0;
  isOrderNow = false;
  digitalWrite(PINS_LEDS[0], LOW);
  digitalWrite(PINS_LEDS[1], LOW);
  digitalWrite(PINS_LEDS[2], LOW);
  digitalWrite(PINS_LEDS[3], LOW);
  delay(2000);
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
  PrintLevelGame();
  RestartSequenceGame();
}

void PrintLevelGame(){
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Nivel: "+String(sizeListOrderNow));
}

void PrintEndGame(){
  lcd.setCursor(0,1);
  lcd.print("Fim de jogo");
}
