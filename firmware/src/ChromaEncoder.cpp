#include "ChromaEncoder.h"

ChromaEncoder::ChromaEncoder(uint8_t pinA, uint8_t pinB, uint8_t switchPin, uint8_t ccNumber) {
    hwEncoder = new Encoder(pinA, pinB);
    swPin = switchPin;
    midiCC = ccNumber;
    currentValue = 64;
    lastPosition = 0;
    isPressed = false;
    lastDebounceTime = 0;
}
ChromaEncoder::~ChromaEncoder() {
    delete hwEncoder;
}
void ChromaEncoder::begin() {
    pinMode(swPin, INPUT_PULLUP);
    hwEncoder->write(0);
}
bool ChromaEncoder::updateTurn() {
    long newPos = hwEncoder ->read();

    if (abs(newPos - lastPosition) >= 4) {
        if (newPos > lastPosition) {
            currentValue++;
        } else {
            currentValue--;
        }
        lastPosition = newPos;
        if (currentValue > 127) currentValue = 127;
        if (currentValue < 0) currentValue = 0;
        return true;
    }
    return false;
}
bool ChromaEncoder::updateSwitch() {
    bool currentState = (digitalRead(swPin) == LOW);
    if (currentState != isPressed) {
        if ((millis() - lastDebounceTime) > debounceDelay) {
            isPressed = currentState;
            lastDebounceTime = millis();
            if (isPressed) {
                return true;
            }
        }
    }
    return false;
}
uint8_t ChromaEncoder::getCC() {
    return midiCC;
}
int ChromaEncoder::getValue() {
    return currentValue;
}