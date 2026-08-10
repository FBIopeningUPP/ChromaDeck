#include "DisplayManager.h"

DisplayManager::DisplayManager() : tft(TFT_eSPI()) {}

void DisplayManager::begin() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    isFirstRender = true;
    for(int i = 0; i < 4; i++) lastFaders[i] = -1;
    for(int i = 0; i < 6; i++) lastEncoders[i] = -1;
}

void DisplayManager::drawDashboard(int faderValues[4], int encoderValues[6]) {
    if (isFirstRender) {
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(2);
        tft.setCursor(15, 15);
        tft.print("CHROMADECK // MAIN CONSOLE");
        tft.drawLine(15, 45, 465, 45, TFT_DARKGREY);

        for (int i = 0; i < 4; i++) {
            tft.setCursor(50 + (i * 90), 280);
            tft.print("CH");
            tft.print(i + 1);
        }
        isFirstRender = false;
    }

    for (int i = 0; i < 4; i++) {
        if (faderValues[i] != lastFaders[i]) {
            int x = 50 + (i * 90);
            int currentHeight = map(faderValues[i], 0, 127, 0, 150);
            int oldHeight = (lastFaders[i] == -1) ? 0 : map(lastFaders[i], 0, 127, 0, 150);

            if (currentHeight > oldHeight) {
                tft.fillRect(x, 260 - currentHeight, 30, currentHeight - oldHeight, TFT_CYAN);
            } else if (currentHeight < oldHeight) {
                tft.fillRect(x, 260 - oldHeight, 30, oldHeight - currentHeight, TFT_BLACK);
            }

            tft.fillRect(x, 80, 50, 25, TFT_BLACK);
            tft.setCursor(x, 80);
            tft.setTextColor(TFT_CYAN, TFT_BLACK);
            tft.print(faderValues[i]);

            lastFaders[i] = faderValues[i];
        }
    }

    for (int i = 0; i < 6; i++) {
        if (encoderValues[i] != lastEncoders[i]) {
            int x = 400;
            int y = 70 + (i * 35);

            if (lastEncoders[i] == -1) {
                tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
                tft.setCursor(x - 50, y);
                tft.print("E");
                tft.print(i + 1);
                tft.print(":");
            }

            tft.fillRect(x, y, 60, 20, TFT_BLACK);
            tft.setCursor(x, y);
            tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
            tft.print(encoderValues[i]);

            lastEncoders[i] = encoderValues[i];
        }
    }
}