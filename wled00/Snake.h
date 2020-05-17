class Snake {

#define MAX_SNAKE_LENGTH 255

    cLEDText ScrollingMsg;
    CRGBPalette16 snakePalette;
    unsigned char txtSnake[17];
    unsigned long previousMillis;
    uint8_t interval, startIndex, fruitHue;
    uint32_t count10ms;
    uint8_t snakeLength, snakeX[MAX_SNAKE_LENGTH], snakeY[MAX_SNAKE_LENGTH];
    uint8_t fruitX, fruitY;
    struct Explode {
      uint8_t x, y, r, hue;
    } ex;
    boolean paused;
    boolean explosion;

  public:
    Snake() {
      previousMillis = 0;
      interval = 250;
      snakeLength = 1;
      snakePalette = RainbowColors_p;
      startIndex = 0;
      fruitHue = 0;
      ex.r = 10;
      count10ms = 0;
      paused = false;
      explosion = false;
    };

    void setup() {
      sprintf((char *)txtSnake, "                ");
      ScrollingMsg.SetFont(MatriseFontData);
      ScrollingMsg.Init(&leds, leds.Width(), ScrollingMsg.FontHeight() + 1, 0, 5);
      ScrollingMsg.SetBackgroundMode(BACKGND_ERASE);
      ScrollingMsg.SetScrollDirection(SCROLL_LEFT);
      ScrollingMsg.SetFrameRate(1);
      ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0x00, 0x99, 0x33);

      currentInput = NONE;

      // Start snake in the middle
      snakeX[0] = leds.Width() / 2;
      snakeY[0] = leds.Height() / 2;

      makeFruit();
    }

    boolean loop() {
      FastLED_clear();
      EVERY_N_MILLISECONDS(10) {
        count10ms++;
      }

      unsigned long currentMillis = millis();

      if (paused) {
        // Black bar behind text
        for (int i = 48; i < 191; i++) {
          leds(i) = CRGB::Black;
        }
        if (ScrollingMsg.UpdateText() == -1) {
          ScrollingMsg.SetText((unsigned char *)txtSnake, sizeof(txtSnake) - 1);
        }
        if (currentInput != NONE) {
          return false;
        }
      }
      else {
        if (explosion) {
          explodeFruit();
        }
        else {
          drawFruit();
          FillSnakeWithColour(startIndex);
          if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;
            nextStep();
          }

          if (currentInput == RESET) {
            return false;
          }
        }
      }

      FastLED_show();
      return true;
    }

  private:
    void drawFruit() {
      leds(fruitX, fruitY) = CHSV(fruitHue, 255, 255);
    }

    void nextStep() {
      for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
      }

      switch (currentInput) {
        case UP:
          snakeY[0] = snakeY[0] + 1;
          break;
        case RIGHT:
          snakeX[0] = snakeX[0] + 1;
          break;
        case DOWN:
          snakeY[0] = snakeY[0] - 1;
          break;
        case LEFT:
          snakeX[0] = snakeX[0] - 1;
          break;
      }

      // Check if head has hit fruit
      if ((snakeX[0] == fruitX) && (snakeY[0] == fruitY)) {
        snakeLength ++;
        interval -= 5;
        if (interval < 100) interval = 100;

        //Store current fruit values to make explosion
        explosion = true;
        ex.x = snakeX[0];
        ex.y = snakeY[0];
        ex.r = 1;
        ex.hue = fruitHue;

        if (snakeLength < MAX_SNAKE_LENGTH) {
          makeFruit();
        }
      }

      // Check if head has hit body or left play area
      if (isPartOfSnakeBody(snakeX[0], snakeY[0]) || !inPlayField(snakeX[0], snakeY[0])) {
        currentInput = NONE;
        FastLED_clear();
        paused = true;
        sprintf((char *)txtSnake, "   SCORE %u   ", snakeLength - 1);
        ScrollingMsg.SetText(txtSnake, strlen((const char *)txtSnake));
      }
    }

    void reset() {
      snakeLength = 1;
      currentInput = NONE;
      interval = 250;
      snakeX[0] = leds.Width() / 2;
      snakeY[0] = leds.Height() / 2;
      for (int i = 1; i < MAX_SNAKE_LENGTH; i++) {
        snakeX[i] = snakeY[i] = -1;
      }
      paused = false;
      explosion = false;
    }

    boolean inPlayField(int x, int y) {
      return (x >= 0) && (x < leds.Width()) && (y >= 0) && (y < leds.Height());
    }

    void makeFruit() {
      uint8_t x, y;
      x = random(0, leds.Width());
      y = random(0, leds.Height());
      while (isPartOfSnake(x, y)) {
        x = random(0, leds.Width());
        y = random(0, leds.Height());
      }
      fruitX = x;
      fruitY = y;
      // Pick a new fruit color
      fruitHue = random8();
    }

    boolean isPartOfSnake(int x, int y) {
      for (int i = 0; i < snakeLength - 1; i++) {
        if ((x == snakeX[i]) && (y == snakeY[i])) {
          return true;
        }
      }
      return false;
    }

    boolean isPartOfSnakeBody(int x, int y) {
      for (int i = 1; i < snakeLength - 1; i++) {
        if ((x == snakeX[i]) && (y == snakeY[i])) {
          return true;
        }
      }
      return false;
    }

    void FillSnakeWithColour(uint8_t colourIndex) {
      startIndex = startIndex + 1;
      for (int i = 0; i < snakeLength; i++) {
        leds(snakeX[i], snakeY[i]) = ColorFromPalette( snakePalette, colourIndex );
        colourIndex += 3;
      }
    }

    void explodeFruit() {
      if (ex.r < 7) {
        for (int r = 1; r <= ex.r; r++) {
          leds.DrawCircle(ex.x, ex.y, r, CHSV(ex.hue, 255, 255 - (r * 40)));
        }
        if (count10ms % 2 == 0) ex.r++;
      } else {
        explosion = false;
        FastLED_clear();
      }
    }
};
