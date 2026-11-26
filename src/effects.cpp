#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "effects.h"
#include "main.cpp"

void solid_white() {
    for (int i = 0; i < strip.numPixels();i++) {
        strip.setPixelColor(i, 255,255,255);
    }
    strip.show();
}

void fade() {
    static uint8_t  level = 0;     
    static int8_t   dir   = 1;     
    static uint32_t last  = 0;     // static so it survives between calls
    const  uint16_t STEP_MS = 10;

    if (millis() - last < STEP_MS) return;
    last = millis();

    
    level += dir;
    if (level == 255 || level == 0) dir = -dir;

    for (int j = 0; j < strip.numPixels(); j++) {   
        strip.setPixelColor(j, level, level, level);
    }
    strip.show();
}

void wave() {

}

void light_off() {
    for (int i = 0; i < strip.numPixels();i++) {
        strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
}

void Fire() {

}

void swirl() {

}

void swirl_wave() {

}

void candle_flicker() {

}

// Fades pixel to nothing over time, used in meteorRain
void fadeToBlack(int ledNo, byte fadeValue) {
  uint32_t oldColor;
  uint8_t r, g, b;

  oldColor = strip.getPixelColor(ledNo);
  r = (oldColor & 0x00ff0000UL) >> 16;
  g = (oldColor & 0x0000ff00UL) >> 8;
  b = (oldColor & 0x000000ffUL);

  r = (r <= 10) ? 0 : (int) r - (r * fadeValue / 256);
  g = (g <= 10) ? 0 : (int) g - (g * fadeValue / 256);
  b = (b <= 10) ? 0 : (int) b - (b * fadeValue / 256);

  strip.setPixelColor(ledNo, r, g, b);
}

// Meteor rain effect
int meteorIndex = 0;
long lastMeteorUpdate = 0;
bool meteorDirection = true; // true = forward, false = reset
byte meteorRed = 255; // Red brightness
byte meteorGreen = 255; // Green brightness
byte meteorBlue = 255; // Blue brightness
int meteorSize = 3; // Size of meteor
int meteorTrailDecay = 64; // Speed of tail decay
boolean meteorRandomDecay = true;
int meteorSpeedDelay = 50; // Animation speed
void meteorRain() {
  if (millis() - lastMeteorUpdate >= meteorSpeedDelay) {
      lastMeteorUpdate = millis();

      // Fade all LEDs
      for (int j = 0; j < strip.numPixels(); j++) {
          if ((!meteorRandomDecay) || (random(10) > 5)) {
              fadeToBlack(j, meteorTrailDecay);
          }
      }

      // Draw meteor
      for (int j = 0; j < meteorSize; j++) {
          int pos = meteorIndex - j;
          if (pos >= 0 && pos < strip.numPixels()) {
              strip.setPixelColor(pos, meteorRed, meteorGreen, meteorBlue);
          }
      }

      strip.show();

      meteorIndex++;

      if (meteorIndex >= strip.numPixels() + meteorSize) {
          meteorIndex = 0;
      }
  }
}


void lightning() {

}