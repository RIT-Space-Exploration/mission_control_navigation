#include "interface.h"
#include <Arduino.h>
#include <SPI.h>
#include <math.h>
#include <LedControl.h>
#define DISPLAY_OUT 11
#define SCK 13

const int MAX_ANALOG = 1023;

int getDegrees(int potVal) {
   return int(360*float(potVal/MAX_ANALOG));
}

void setDisplay(int roll, int pitch, int yaw) {
    pinMode(DISPLAY_OUT, OUTPUT);
    //LedControl segmentDisplay = LedControl(, SCK, , 3); <-- Not sure about DIN and LOAD pins
    segmentDisplay.shutdown(0, false); // Turn on displays
    segmentDisplay.shutdown(1, false); //  --------------
    segmentDisplay.shutdown(2, false); //  --------------
    segmentDisplay.setIntensity(0, 0); // Set display brightness to minimum
    segmentDisplay.setIntensity(1, 0); //  --------------
    segmentDisplay.setIntensity(2, 0); //  --------------
    // Set roll
    segmentDisplay.setDigit(2, 4, parseValue(roll, 0), true);
    segmentDisplay.setDigit(2, 5, parseValue(roll, 1), true);
    segmentDisplay.setDigit(2, 6, parseValue(roll, 2), true);
    // Set pitch
    segmentDisplay.setDigit(1, 4, parseValue(pitch, 0), true);
    segmentDisplay.setDigit(1, 5, parseValue(pitch, 1), true);
    segmentDisplay.setDigit(1, 6, parseValue(pitch, 2), true);
    // Set yaw
    segmentDisplay.setDigit(0, 4, parseValue(yaw, 0), true);
    segmentDisplay.setDigit(0, 5, parseValue(yaw, 1), true);
    segmentDisplay.setDigit(0, 6, parseValue(yaw, 2), true);

}

int parseValue(int value, int factor) {
    int digit, place = factor;
    do {
        digit = value%10;
        value /= 10;
        place -= 1;
    } while (place >= 0);
    return digit;
}