#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI(); 

#define BTN_LEFT 0
#define BTN_RIGHT 35

int snakeX[100], snakeY[100];
int snakeLength;
int dir; // 0=arriba, 1=derecha, 2=abajo, 3=izquierda
int gridSize = 10;
int foodX, foodY;
bool gameOver = false;
bool startScreen = true;

void setup() {
  tft.init();
  tft.setRotation(0); // Vertical fijo
  tft.fillScreen(TFT_BLACK);

  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  // Pantalla de inicio
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextDatum(MC_DATUM);
  tft.drawString("Presiona", tft.width()/2, tft.height()/2 - 30);
  tft.drawString("START",     tft.width()/2, tft.height()/2);
}

void loop() {
  // Pantalla inicial dinámica
  if (startScreen) {
    if (digitalRead(BTN_LEFT) == LOW || digitalRead(BTN_RIGHT) == LOW) {
      delay(500);
      startScreen = false;
      startGame();
    }
    return;
  }

  // Pantalla de derrota dinámica
  if (gameOver) {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Perdiste", tft.width()/2, tft.height()/2 - 30);
    tft.drawString("malo",     tft.width()/2, tft.height()/2);
    tft.drawString("qlo",      tft.width()/2, tft.height()/2 + 30);

    // Reinicio al mantener presionado un botón
    if (digitalRead(BTN_LEFT) == LOW || digitalRead(BTN_RIGHT) == LOW) {
      delay(500); 
      startGame();
    }
    return;
  }

  // Leer botones
  if (digitalRead(BTN_LEFT) == LOW) {
    dir = (dir + 3) % 4;
  }
  if (digitalRead(BTN_RIGHT) == LOW) {
    dir = (dir + 1) % 4;
  }

  // Mover serpiente
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  if (dir == 0) snakeY[0] -= gridSize;
  if (dir == 1) snakeX[0] += gridSize;
  if (dir == 2) snakeY[0] += gridSize;
  if (dir == 3) snakeX[0] -= gridSize;

  // Detectar choque con bordes
  if (snakeX[0] < 0 || snakeX[0] >= tft.width() ||
      snakeY[0] < 0 || snakeY[0] >= tft.height()) {
    gameOver = true;
    return;
  }

  // Detectar choque con el propio cuerpo
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;
      return;
    }
  }

  // Comer comida
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    spawnFood();
  }

  // Dibujar juego
  tft.fillScreen(TFT_BLACK);
  for (int i = 0; i < snakeLength; i++) {
    tft.fillRect(snakeX[i], snakeY[i], gridSize, gridSize, TFT_GREEN);
  }
  tft.fillRect(foodX, foodY, gridSize, gridSize, TFT_RED);

  delay(200);
}

void spawnFood() {
  foodX = (random(0, tft.width() / gridSize)) * gridSize;
  foodY = (random(0, tft.height() / gridSize)) * gridSize;
}

void startGame() {
  snakeLength = 5;
  dir = 1;
  gameOver = false;

  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = 60 - i * gridSize;
    snakeY[i] = 60;
  }

  spawnFood();
  tft.fillScreen(TFT_BLACK);
}
