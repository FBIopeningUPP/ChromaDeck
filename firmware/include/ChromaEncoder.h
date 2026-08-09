#pragma once
#include <Arduino.h>
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

class ChromaEncoder {
private:
    Encoder* hwEncoder;
    uint8_t swPin;
    uint8_t midiCC;
    int currentValue;
    long lastPosition;
    bool isPressed;
    unsigned long lastDebounceTime;
    const unsigned long debounceDelay = 10;

public:
    ChromaEncoder(uint8_t pinA, uint8_t pinB, uint8_t switchPin, uint8_t ccNumber);
    ~ChromaEncoder();
    void begin();
    bool updateTurn();
    bool updateSwitch();
    uint8_t getCC();
    int getValue();
};