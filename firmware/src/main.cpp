#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

#include "ChromaKey.h"
#include "ChromaFader.h"
#include "ChromaEncoder.h"

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);

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

void setup() {
    usb_midi.begin();
    MIDI.begin(MIDI_CHANNEL_OMNI);

    for (int i = 0; i < 8; i++) keys[i].begin();
    for (int i = 0; i < 4; i++) faders[i].begin();
    for (int i = 0; i < 6; i++) encoders[i].begin();
}

void loop() {
    for (int i = 0; i < 8; i++) {
        if (keys[i].update()) {
            MIDI.sendNoteOn(keys[i].getNote(), 127, 1);
        }
    }

    for (int i = 0; i < 4; i++) {
        if (faders[i].update()) {
            MIDI.sendControlChange(faders[i].getCC(), faders[i].getValue(), 1);
        }
    }

    for (int i = 0; i < 6; i++) {
        if (encoders[i].updateTurn()) {
            MIDI.sendControlChange(encoders[i].getCC(), encoders[i].getValue(), 1);
        }
        if (encoders[i].updateSwitch()) {
            MIDI.sendNoteOn(50 + i, 127, 1);
        }
    }
}