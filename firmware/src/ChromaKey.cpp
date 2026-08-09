#include "ChromaKey.h"

ChromaKey::ChromaKey(uint8_t hardwarePin, uint8_t note) {
    pin = hardwarePin;
    midiNote = note;
    isPressed = false;
    lastDebounceTime = 0
}

void ChromaKey::begin() {
    pinMode(pin, INPUT_PULLUP);
}

bool ChromaKey::update() {
    bool currentState = (digitalRead(pin) == LOW);
    if (currentState != isPressed ) {
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

uint8_t ChromaKey::getNote() {
    return midiNote;
}

bool ChromaKey::getState() {
    return isPressed;
}