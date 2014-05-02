#include "FastLED.h"

#define NUM_LEDS 100

#define DATA_PIN 11
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
}

void loop() {

}

void updateLed(int x, int y, CRGB colour) {
    leds[coordToIndex(x, y)] = colour;
}

int coordToIndex(int x, int y) {
    if (x % 2 == 0) return (x * 10) + y;
    else return ((x + 1) * 10) - (y + 1);
}