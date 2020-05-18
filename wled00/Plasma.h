class Plasma {
  
    uint16_t PlasmaTime, PlasmaShift;
    const uint8_t PlasmaLowHue = 100;
    const uint8_t PlasmaHighHue = 150;

    public:
    Plasma() {
    };

    void setup() {
      PlasmaShift = (random8(0, 5) * 32) + 64;
      PlasmaTime = 0;
    }

    boolean loop() {
      // Fill background with dim plasma

#define PLASMA_X_FACTOR  48
#define PLASMA_Y_FACTOR  48
      for (int16_t x = 0; x < leds.Width(); x++)
      {
        for (int16_t y = 0; y < leds.Height(); y++)
        {
          int16_t r = sin16(PlasmaTime) / 256;
          int16_t h = sin16(x * r * PLASMA_X_FACTOR + PlasmaTime) + cos16(y * (-r) * PLASMA_Y_FACTOR + PlasmaTime) + sin16(y * x * (cos16(-PlasmaTime) / 256) / 2);
          int16_t hue = ((h / 256) + 128);
          leds(x, y) = CHSV((uint8_t)hue, 255, 64);
        }
      }
      uint16_t OldPlasmaTime = PlasmaTime;
      PlasmaTime += PlasmaShift;
      if (OldPlasmaTime > PlasmaTime) {
        PlasmaShift = (random8(0, 5) * 32) + 64;
      }
      FastLED_show();
    }
};
