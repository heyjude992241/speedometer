#include <Adafruit_ST7789.h>
#include <Adafruit_ST77xx.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const uint8_t RXPin = 4, TXPin = 3;
const uint8_t TFT_CS = 10, TFT_DC = 8, TFT_RST = 9; 
const uint8_t GPSBaud = 9600;

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

double lat = 3.12331211;
double lng = 101.23441212;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("Initializing TFT ... "));
  tft.init(240, 240, SPI_MODE2);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  Serial.println(F("Done"));
  ss.begin(GPSBaud);
  Serial.println("Begin GPS");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(ss.available() > 0){
    gps.encode(ss.read());
  }

  //graphic test first!!
  tft.setCursor(0, 0);
  tft.println(F("Graphics test first!!!"));
  tft.setTextSize(2);
  tft.println(F("Hello world!!!"));
  tft.setTextSize(1);
  tft.print(F("Location is: "));
  tft.print(lat, 6);
  tft.print(", ");
  tft.print(lng, 6);

//  if(millis() > 5000 && gps.charsProcessed() < 10){
//    tft.setCursor(0, 0);
//    tft.fillScreen(ST77XX_BLACK);
//    tft.print(F("Connection error. Check wiring"));
//  }
  
  
}
