#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

byte Cactus[8] = {
  0b00100,
  0b00100,
  0b10100,
  0b10100,
  0b11101,
  0b00111,
  0b00100,
  0b00100
};

byte Dinosaur[8] = {
  0b00111,
  0b00101,
  0b00111,
  0b10100,
  0b10110,
  0b11100,
  0b01010,
  0b01010
};

const char PLAYER = 0;
const char CACTUS = 1;
const char FLOOR = 0xFF;
const char SPACE = ' ';
const int BTN = 2;
int score = 0;
int difficulty = 300;

//player pos
int player_x = 4;
int player_y = 2;

//cactus pos
int cactus_x = 19;
int cactus_y = 2;

//floor creating
void ShowFloor() {
  for (int i = 0; i < 20; i++) {
    lcd.setCursor(i, 3);
    lcd.print(FLOOR);
  }
}

void CactusMove() {
  lcd.setCursor(cactus_x, cactus_y);
  lcd.print(CACTUS);
  lcd.print(SPACE);
  delay(difficulty);
  cactus_x--;

  if (cactus_x < 0) {
    lcd.setCursor(0, 2);
    lcd.print(SPACE);
    cactus_x = 19;
  }
}

void DinoMove(){
  lcd.setCursor(player_x, player_y);
  lcd.print(PLAYER);
  delay(difficulty);
}

void DinoJump() {
    if (digitalRead(BTN) == HIGH && player_y != 1) {
      lcd.setCursor(player_x, player_y);
      lcd.print(SPACE);
      player_y=1;
      lcd.setCursor(player_x, player_y);
      DinoMove();
      CactusMove();
      CactusMove();
      lcd.setCursor(player_x, player_y);
      lcd.print(SPACE);
      player_y=2;
  }
}

void Score() {
  if (difficulty >= 10) difficulty -= difficulty * 0.01;
  lcd.setCursor(9, 0);
  lcd.print("score");
  lcd.setCursor(15, 0);
  lcd.print(score);
  score++;
}


void GameOver() {
  if (cactus_x == player_x && cactus_y == player_y) {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("Game");
    lcd.setCursor(7, 2);
    lcd.print("over!");
    delay(1500);

    cactus_x = 19;
    score = 0;
    difficulty = 300;
    lcd.clear();
    ShowFloor();
  }
}

//settings
void setup() {
  lcd.init();
  pinMode(BTN, INPUT);

  //creating custom chars
  lcd.createChar(CACTUS, Cactus);
  lcd.createChar(PLAYER, Dinosaur);

  ShowFloor();
}

void loop() {
  DinoMove();
  DinoJump();
  Score();
  CactusMove();
  GameOver();

  lcd.setCursor(0, 3);
  lcd.print(FLOOR);
}
