#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>

class DisplayManager {
    private:
        TFT_eSPI tft;
        TFT_eSprite sprite;
    public:
        DisplayManager();
        void begin();
        void drawDashboard(int faderValues[4], int encoderValues[6]);
};