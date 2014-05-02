#include "FastLED.h"

#define NUM_LEDS 100
#define DATA_PIN 11
#define CLOCK_PIN 13

boolean cells[10][10];

CRGB leds[NUM_LEDS];

int next[10][10];

int current[10][10] =
{ {0,0,0,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0,0,0},
  {0,0,0,1,0,0,0,0,0,0},
  {0,1,1,1,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,1,0,0,0},
  {0,0,0,0,0,0,0,1,0,0},
  {0,0,0,0,0,1,1,1,0,0},
  {0,0,0,0,0,0,0,0,0,0} };


void setup() {
    FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
    Serial.begin(9600);
    Serial.write("hello");
    pinMode(0, INPUT);
    randomSeed(analogRead(0));
    if (random(2)>0) {
        for (int r=0 ; r<10 ; r++) {
            for (int c=0 ; c<10 ; c++) {
                if (random(2) > 0) next[r][c] = 1;
            }
        }
    }
}

void updateLed(int x, int y, CRGB colour) {
    leds[coordToIndex(x, y)] = colour;
}

int coordToIndex(int x, int y) {
    if (x % 2 == 0) return (x * 10) + y;
    else return ((x + 1) * 10) - (y + 1);
}

int mod(int a) {
    return (a+10)%10;
}

void loop() {
    game_of_life();
}

void game_of_life() {

    // draw
    for (int r=0 ; r<10; r++) {
        for (int c=0 ; c<10; c++) {
            int color;
            if (next[r][c] == 0) color = 0;
            else if (next[r][c] == 1) color = CRGB::Orange;
            else if (next[r][c] == 2) color = CRGB::Yellow;
            else if (next[r][c] == 3) color = CRGB::Green;
            else if (next[r][c] == 4) color = CRGB::Blue;
            else if (next[r][c] == 5) color = CRGB::Indigo;
            else if (next[r][c] == 6) color = CRGB::Violet;
            else if (next[r][c] > 10) color = CRGB::Green;
            updateLed(c, r, color);
            FastLED.show();
        }
    }

    // calc next state
    for (int r=0 ; r<10; r++) {
        for (int c=0 ; c<10; c++) {
            // count alive neighbors
            int alive = 0;
            alive += current[mod(r+1)][mod(c)  ] != 0;
            alive += current[mod(r)  ][mod(c+1)] != 0;
            alive += current[mod(r-1)][mod(c)  ] != 0;
            alive += current[mod(r)  ][mod(c-1)] != 0;
            alive += current[mod(r+1)][mod(c+1)] != 0;
            alive += current[mod(r-1)][mod(c-1)] != 0;
            alive += current[mod(r+1)][mod(c-1)] != 0;
            alive += current[mod(r-1)][mod(c+1)] != 0;
            if (current[r][c])
                if (alive < 2 || alive > 3) next[r][c] = 0;
                else next[r][c] = current[r][c] + 1;
            else
                if (alive == 3) next[r][c] = 1;
        }
    }

    for (int r=0 ; r<10; r++) {
        for (int c=0 ; c<10; c++) {
            current[r][c] = next[r][c];
        }
    }
    delay(10);
}