#include "LEDManager.h"

LEDManager::LEDManager() {}

void LEDManager::begin() {
    FastLED.addLeds<WS2812B, PA8, GRB>(keysLeds, 8);

    FastLED.addLeds<WS2812B, PB10, GRB>(faderLeds[0], 10);
    FastLED.addLeds<WS2812B, PB11, GRB>(faderLeds[1], 10);
    FastLED.addLeds<WS2812B, PB12, GRB>(faderLeds[2], 10);
    FastLED.addLeds<WS2812B, PB13, GRB>(faderLeds[3], 10);

    FastLED.addLeds<WS2812B, PD2, GRB>(encoderLeds[0], 12);
    FastLED.addLeds<WS2812B, PD3, GRB>(encoderLeds[1], 12);
    FastLED.addLeds<WS2812B, PD6, GRB>(encoderLeds[2], 12);
    FastLED.addLeds<WS2812B, PD12, GRB>(encoderLeds[3], 12);
    FastLED.addLeds<WS2812B, PD13, GRB>(encoderLeds[4], 12);
    FastLED.addLeds<WS2812B, PA4, GRB>(encoderLeds[5], 12);

    FastLED.setBrightness(100);
}

void LEDManager::update() {
    FastLED.show();
}

void LEDManager::setKeyColor(uint8_t index, CRGB color) {
    if (index < 8) {
        keysLeds[index] = color;
    }
}

void LEDManager::setFaderLevel(uint8_t index, uint8_t level, CRGB color) {
    if (index < 4) {
        uint8_t numLedsToLight = map(level, 0, 127, 0, 10);
        for (uint8_t i = 0; i < 10; i++) {
            if (i < numLedsToLight) {
                faderLeds[index][i] = color;
            } else {
                faderLeds[index][i] = CRGB::Black;
            }
        }
    }
}

void LEDManager::setEncoderRing(uint8_t index, uint8_t level, CRGB color) {
    if (index < 6) {
        uint8_t numLedsToLight = map(level, 0, 127, 0, 12);
        for (uint8_t i = 0; i < 12; i++) {
            if (i < numLedsToLight) {
                encoderLeds[index][i] = color;
            } else {
                encoderLeds[index][i] = CRGB::Black;
            }
        }
    }
}