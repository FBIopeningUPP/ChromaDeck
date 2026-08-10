#pragma once
#include <Arduino.h>
#include <FastLED.h>

class LEDManager {
    private:
        CRGB keysLeds[8];
        CRGB faderLeds[4][10];
        CRGB encoderLeds[6][12];
    
    public:
        LEDManager();
        void begin();
        void update();
        void setKeyColor(uint8_t index, CRGB color);
        void setFaderLevel(uint8_t index, uint8_t level, CRGB color);
        void setEncoderRing(uint8_t index, uint8_t level, CRGB color);
};