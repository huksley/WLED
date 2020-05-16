#include "wled.h"
/*
   This file allows you to add own functionality to WLED more easily
   See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
   EEPROM bytes 2750+ are reserved for your custom use case. (if you extend #define EEPSIZE in const.h)
   bytes 2400+ are currently ununsed, but might be used for future wled features
*/

//Use userVar0 and userVar1 (API calls &U0=,&U1=, uint16_t)

#define FASTLED_INTERNAL
#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontMatrise.h>
#include <LEDSprites.h>

#define MATRIX_WIDTH   16
#define MATRIX_HEIGHT  16
#define MATRIX_TYPE    VERTICAL_ZIGZAG_MATRIX
cLEDMatrix < MATRIX_WIDTH, -MATRIX_HEIGHT, MATRIX_TYPE > leds;

enum btnInput {NONE, UP, DOWN, LEFT, RIGHT, RESET, TOGGLE};
btnInput currentInput = NONE;

CRGB col_to_crgb(uint32_t color)
{
  CRGB fastled_col;
  fastled_col.red =   (color >> 16 & 0xFF);
  fastled_col.green = (color >> 8  & 0xFF);
  fastled_col.blue =  (color       & 0xFF);
  return fastled_col;
}

void FastLED_clear() {
  for (uint16_t i = 0; i < strip.getSegments()[0].virtualLength(); i++) {
    leds(i) = col_to_crgb(BLACK);
    strip.setPixelColor(i, BLACK);
  }
}

uint32_t crgb_to_col(CRGB fastled)
{
  return (((uint32_t)fastled.red << 16) | ((uint32_t)fastled.green << 8) | fastled.blue);
}

void FastLED_show() {
  for (uint16_t i = 0; i < strip.getSegments()[0].virtualLength(); i++) {
    CRGB rgb = leds(i);
    uint32_t col = crgb_to_col(rgb);
    strip.setPixelColor(i, strip.color_blend(col, 0x000000, 190));
  }
}

#include "Snake.h"
#include "Plasma.h"

const uint8_t PacmanRightData[] =
{
  // Pacman Open
  B8_2BIT(00021112), B8_2BIT(00000000),
  B8_2BIT(00111111), B8_2BIT(10000000),
  B8_2BIT(01111111), B8_2BIT(00000000),
  B8_2BIT(21111110), B8_2BIT(00000000),
  B8_2BIT(11111000), B8_2BIT(00000000),
  B8_2BIT(11111000), B8_2BIT(00000000),
  B8_2BIT(21111110), B8_2BIT(00000000),
  B8_2BIT(01111111), B8_2BIT(00000000),
  B8_2BIT(00111111), B8_2BIT(10000000),
  B8_2BIT(00021112), B8_2BIT(00000000),
  // Pacman Half
  B8_2BIT(00021112), B8_2BIT(00000000),
  B8_2BIT(00111111), B8_2BIT(10000000),
  B8_2BIT(01111111), B8_2BIT(11000000),
  B8_2BIT(21111111), B8_2BIT(11200000),
  B8_2BIT(11111200), B8_2BIT(00000000),
  B8_2BIT(11111200), B8_2BIT(00000000),
  B8_2BIT(21111111), B8_2BIT(11200000),
  B8_2BIT(01111111), B8_2BIT(11000000),
  B8_2BIT(00111111), B8_2BIT(10000000),
  B8_2BIT(00021112), B8_2BIT(00000000),
  // Pacman Closed
  B8_2BIT(00021112), B8_2BIT(00000000),
  B8_2BIT(00111111), B8_2BIT(10000000),
  B8_2BIT(01111111), B8_2BIT(11000000),
  B8_2BIT(21111111), B8_2BIT(11200000),
  B8_2BIT(11111111), B8_2BIT(11100000),
  B8_2BIT(11111111), B8_2BIT(11100000),
  B8_2BIT(21111111), B8_2BIT(11200000),
  B8_2BIT(01111111), B8_2BIT(11000000),
  B8_2BIT(00111111), B8_2BIT(10000000),
  B8_2BIT(00021112), B8_2BIT(00000000)
};
const uint8_t PacmanRightMask[] =
{
  // Pacman Open
  B8_1BIT(00011111), B8_1BIT(00000000),
  B8_1BIT(00111111), B8_1BIT(10000000),
  B8_1BIT(01111111), B8_1BIT(00000000),
  B8_1BIT(11111110), B8_1BIT(00000000),
  B8_1BIT(11111000), B8_1BIT(00000000),
  B8_1BIT(11111000), B8_1BIT(00000000),
  B8_1BIT(11111110), B8_1BIT(00000000),
  B8_1BIT(01111111), B8_1BIT(00000000),
  B8_1BIT(00111111), B8_1BIT(10000000),
  B8_1BIT(00011111), B8_1BIT(00000000),
  // Pacman Half
  B8_1BIT(00011111), B8_1BIT(00000000),
  B8_1BIT(00111111), B8_1BIT(10000000),
  B8_1BIT(01111111), B8_1BIT(11000000),
  B8_1BIT(11111111), B8_1BIT(11100000),
  B8_1BIT(11111100), B8_1BIT(00000000),
  B8_1BIT(11111100), B8_1BIT(00000000),
  B8_1BIT(11111111), B8_1BIT(11100000),
  B8_1BIT(01111111), B8_1BIT(11000000),
  B8_1BIT(00111111), B8_1BIT(10000000),
  B8_1BIT(00011111), B8_1BIT(00000000),
  // Pacman Closed
  B8_1BIT(00011111), B8_1BIT(00000000),
  B8_1BIT(00111111), B8_1BIT(10000000),
  B8_1BIT(01111111), B8_1BIT(11000000),
  B8_1BIT(11111111), B8_1BIT(11100000),
  B8_1BIT(11111111), B8_1BIT(11100000),
  B8_1BIT(11111111), B8_1BIT(11100000),
  B8_1BIT(11111111), B8_1BIT(11100000),
  B8_1BIT(01111111), B8_1BIT(11000000),
  B8_1BIT(00111111), B8_1BIT(10000000),
  B8_1BIT(00011111), B8_1BIT(00000000)
};
const struct CRGB PacmanRightColTab[] =  {  CRGB(150, 150, 0), CRGB(30, 30, 0), CRGB(255, 255, 255)  };

cLEDSprites Sprites(&leds);
#define MY_SPRITE_WIDTH  11
#define MY_SPRITE_HEIGHT 10
#define PACMAN_FRAMES  3
cSprite Shape(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PacmanRightData, PACMAN_FRAMES, _2BIT, PacmanRightColTab, PacmanRightMask);




long temptimer = millis();
long lastMeasure = 0;

//gets called once at boot. Do all initialization that doesn't depend on network here
void userSetup()
{
  DEBUG_PRINTLN("userSetup");

  effectCurrent = FX_MODE_USERMOD;
  strip.setBrightness(20);
  colorUpdated(NOTIFIER_CALL_MODE_DIRECT_CHANGE);

  Shape.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 10/*FrameRate*/, +1/*XChange*/, 1/*XRate*/, +1/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);
  //Shape.SetPositionFrameMotionOptions(-12/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN | SPRITE_DETECT_COLLISION);

  Sprites.AddSprite(&Shape);

}

Snake* snake = NULL;
Plasma plasma = Plasma();

//gets called every time WiFi is (re-)connected. Initialize own network interfaces here
void userConnected()
{

  DEBUG_PRINTLN("userConnected");
  snake = new Snake();
  snake->setup();
  plasma.setup();
}

bool isRunning = true;

int inputIndex = 0;
int toggle = 0;
// 0 - plasma, 1 - snake, 2 - pacman
#define TOGGLE_MAX 2

//loop. You can use "if (WLED_CONNECTED)" to check for successful connection
void userLoop()
{
  if (WLED_CONNECTED) {

    temptimer = millis();
    if (temptimer - lastMeasure > 50) {
      lastMeasure = temptimer;

      if (toggle == 0) {
        plasma.loop();
      }

      if (toggle == 1) {
        if (isRunning) isRunning = snake->loop();
        if (!isRunning) {
          delete snake;
          snake = new Snake();
          snake->setup();
          DEBUG_PRINTLN("new snake");
          isRunning = true;
          FastLED_clear();
          currentInput = NONE;
        }
      }

      if (toggle == 2) {
        Sprites.UpdateSprites();
        FastLED_clear();
        Sprites.RenderSprites();
        FastLED_show();
      }

      if (userVar0 != inputIndex) {
        inputIndex = userVar0;
        switch (userVar1) {
          case 1:
            currentInput = UP;
            break;
          case 2:
            currentInput = LEFT;
            break;
          case 4:
            currentInput = DOWN;
            break;
          case 3:
            currentInput = RIGHT;
            break;
          case 0:
            currentInput = RESET;
            break;
          case 5:
            currentInput = TOGGLE;
            toggle ++;
            DEBUG_PRINTLN("new toggle");
            FastLED_clear();
            if (toggle > TOGGLE_MAX) {
              toggle = 0;
            }
        }

        char str[256];
        sprintf(str, "userVar0: %i, userVar1: %i, currentInput: %i", userVar0, userVar1, currentInput);
        DEBUG_PRINTLN(str);
      }
    }

  }
}
