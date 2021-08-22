#include "TinyDHT.h"
#define DHTPIN 2  // DHT connected to Arduino Uno Digital Pin 2
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN    6
#define LED_COUNT 60
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
#define PBSW 4
int count = 0;	// inital count value
int state = HIGH;	// normal state value
#define RED 12
#define GREEN 11

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Output status on Uno serial monitor
  Serial.println("TEMPERATUE MOODLAMP!");
  dht.begin();
pinMode(PBSW, INPUT_PULLUP);
decode(count);
strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();    
  colorWipe(strip.Color(0,   0,   0), 1);        // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float t = dht.readTemperature();
  if (isnan(t)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 
  Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" degree C ");
if(digitalRead(PBSW) == LOW){
    // switch pressed
    if (state == HIGH){
      // ok, lets process
      state = LOW;
    }
    else {
      // ignore, since state = LOW
    }
  }
  else {
    // switch is at normal
    if (state == LOW){
      // register keypress
      count = (count + 1) % 5;
      decode(count);
      state = HIGH;
    }
  }
}

void decode(int v)
{
  switch(v){
    case 0:
      digitalWrite(RED,HIGH);
   digitalWrite(GREEN,LOW);
   colorWipe(strip.Color(0,   0,   0), 1);
    	break;
    case 1:
      digitalWrite(RED,LOW);
   digitalWrite(GREEN,HIGH);
    colorWipe(strip.Color(255,   0,   0), 1); // Red
    	break;
    case 2:
     digitalWrite(RED,LOW);
   digitalWrite(GREEN,HIGH);
    colorWipe(strip.Color(  0, 255,   100), 1); // Green
    	break;
    case 3:
    digitalWrite(RED,LOW);
   digitalWrite(GREEN,HIGH);
    colorWipe(strip.Color(  255, 255,0), 1); 
    break;
    case 4:
     digitalWrite(RED,LOW);
   digitalWrite(GREEN,HIGH);
float t = dht.readTemperature();
  // check if returns are valid then something went wrong!
 if (isnan(t)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } 
  if(t<25){
   colorWipe(strip.Color(0,   80,   255), 1); // BLUE
  }
  else if (t<30){
    colorWipe(strip.Color(255,   255,   255), 1);
  }
  else{
  colorWipe(strip.Color(200,   30,   0), 1); // RED
  }
    break;
  } 	
}




void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}


