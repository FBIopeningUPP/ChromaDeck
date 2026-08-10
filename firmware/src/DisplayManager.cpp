#include "DisplayManager.h"

DisplayManager::Displaymanager() : tft(TFt_eSPI()), sprite(TFT_eSprite(&tft)) {}

void DisplayManager::begin() {
    tft.init()
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    sprite.createSprite(480, 320);
    sprite.setTextColor(TFT_WHITE, TFT_BLACK);
}

void DisplayManager::drawDashboard(int faderValues[4], int encoderValues[6]) {
    sprite.fillSprite(TFT_BLACK);
    for (int i = 0; i < 4; i++) {
        int barHeight = map(faderValues[i], 0, 127, 0, 150);
        sprite.drawRect(50 + (i * 100), 100, 30, 150, TFT_DARKGREY);
        sprite.fillRect(50 + (i * 100), 250 - barHeight, 30, barHeight, TFT_CYAN);
    }
    for (int i = 0; i < 6; i++) {
        sprite.drawString("ENC " + String(i + 1) + ": " + String(encoderValues[i]), 50 + (i * 60), 30);
    }
    sprite.pushSprite(0, 0);
}