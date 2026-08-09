#include <Arduino.h>
#include <MIDIUSB.h>

#include "ChromaEncoder.h"
#include "ChromaKey.h"
#include "ChromaFader.h"

ChromaKey keys[8] = {
    ChromaKey(PC0, 36), ChromaKey(PC1, 37), ChromaKey(PC2, 38), ChromaKey(PC3, 39),
    ChromaKey(PC4, 40), ChromaKey(PC6, 41), ChromaKey(PC7, 42), ChromaKey(PC11, 43)
};

ChromaFader faders[4] = {
    ChromaFader(PA0, 1), ChromaFader(PA1, 2), ChromaFader(PA2, 3), ChromaFader(PA3, 4)
};

ChromaEncoder encoders[6] = {
    ChromaEncoder(PB0, PB1, PB2, 5),
    ChromaEncoder(PB4, PB5, PB6, 6),
    ChromaEncoder(PB7, PB8, PB9, 7),
    ChromaEncoder(PE0, PE1, PE2, 8),
    ChromaEncoder(PE3, PE4, PE5, 9),
    ChromaEncoder(PC8, PC9, PC10, 10)
};

void sendNoteOn(byte channel, byte pitch, byte velocity) {
    midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
    MidiUSB.sendMIDI(noteOn);
    MidiUSB.flush();
}

void sendControlChange(byte channel, byte control, byte value) {
    midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
    MidiUSB.sendMIDI(event);
    MidiUSB.flush();
}

void setup() {
    for (int i = 0; i < 8; i++) keys[i].begin();
    for (int i = 0; i < 4; i++) faders[i].begin();
    for (int i = 0; i < 6; i++) encoders[i].begin();
}
void loop() {
    for (int i = 0; i < 8; i++) {
        if (keys[i].update()) {
            sendNoteOn(0, keys[i].getNote(), 127);
        }
    }
    for (int i = 0; i < 4; i++) {
        if (faders[i].update()) {
            sendControlChange(0, faders[i].getCC(), faders[i].getValue());
        }
    }
    for (int i = 0; i < 6; i++) {
        if (encoders[i].updateTurn()) {
            sendControlChange(0, encoders[i].getCC(), encoders[i].getValue());
        }
        if (encoders[i].updateSwitch()) {
            sendNoteOn(0, 50 + 1, 127);
        }
    }
}