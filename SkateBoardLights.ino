#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define TAIL_START 45
#define TAIL_LENGTH 20
#define TAIL_COLOR 0xFF0000

#define DATA_PIN    5
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    111
CRGB leds[NUM_LEDS];

#define BRIGHTNESS 150
#define FRAMES_PER_SECOND 180

void setup() {
  delay(1000);
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // set our rainbow color
  rainbow();

  // set our tail light
  setTail();
  
  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 3 ) { gHue++; } // slowly cycle the "base color" through the rainbow
}

void setTail()
{
  for (int x = TAIL_START; x < TAIL_START + TAIL_LENGTH; x++) {
    leds[x] = TAIL_COLOR;
  }
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 3);
}
