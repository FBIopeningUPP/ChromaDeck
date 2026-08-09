#include "ChromaFader.h"

ChromaFader::ChromaFader(uint8_t hardwarePin, uint8_t ccNumber) {
    pin = hardwarePin;
    midiCC = ccNumber;
    currentValue = -1;
    smoothedRaw = 0;
}

void ChromaFader::begin() {
    pinMode(pin, INPUT);
    smoothedRaw = analogRead(pin);
}

bool ChromaFader::update() {
    int rawValue = analogRead(pin);
    smoothedRaw = (alpha * rawValue) + ((1.0 - alpha) * smoothedRaw);
    int mappedValue = map((int)smoothedRaw, 0, 4095, 0, 127);
    mappedValue = constrain(mappedValue, 0, 127);
    if (mappedValue != currentValue) {
        currentValue = mappedValue;
        return true;
    }
    return false;
}
uint8_t ChromaFader::getCC() {
    return midiCC;
}
int ChromaFader::getValue() {
    return currentValue;
}