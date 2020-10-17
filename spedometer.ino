#include <Adafruit_ST7789.h>
#include <Adafruit_ST77xx.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

const uint8_t RXPin = 4, TXPin = 3;
const uint8_t GPSBaud = 9600;

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

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
  while(ss.available()){
    gps.encode(ss.read());
  }
  
  
}
