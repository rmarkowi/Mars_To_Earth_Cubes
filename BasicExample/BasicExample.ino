/*
  G35: An Arduino library for GE Color Effects G-35 holiday lights.
  Copyright © 2011 The G35 Authors. Use, modification, and distribution are
  subject to the BSD license as described in the accompanying LICENSE file.

  See README for complete attributions.
*/

#include <G35String.h>

// Total # of lights on string (usually 50, 48, or 36). Maximum is 63, because
// the protocol uses 6-bit addressing and bulb #63 is reserved for broadcast
// messages.
#define LIGHT_COUNT (50)

// Arduino pin number. Pin 13 will blink the on-board LED.
#define G35_PIN (13)

G35String lights(G35_PIN, LIGHT_COUNT, LIGHT_COUNT, 0, true);

void setup() {
  Serial.begin(9600);
  lights.enumerate();
}

int r = 15;
int g = 0;
int b = 0;
int c = 0;
void loop() {
  c++;
  if(c <= 30){
    if(c%2 == 0){
    r--;
    }else{
    g++;
    }
  }
  else if(c > 30 && c <= (30 * 2)){
    if(c%2 == 0){
    g--;
    }else{
    b++;
    }
  }
  else if(c > (30 * 2) && c <= (30 * 3)){
    if(c%2 == 0){
    b--;
    }else{
    r++;
    }
  }
  c %= (30 * 3);
  Serial.println("color: " + String(c) + ", red: " + String(r) + ", green: " + String(g) + ", blue: " + String(b));
  lights.fill_color(0, LIGHT_COUNT, 255, G35::color(r, g, b));
  delay(10);
}
