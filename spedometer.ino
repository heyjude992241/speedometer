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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.println(F("Initializing TFT ... "));
  tft.init(240, 240, SPI_MODE2);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  Serial.println(F("Done"));
  Serial.println("Begin GPS");
}

void loop() {
  // put your main code here, to run repeatedly:
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  while(ss.available() > 0)
    if(gps.encode(ss.read()))
      displayGPS();
 
  
  if(gps.charsProcessed() < 10){
    if(millis() > 5000){
      tft.print(F("Conection error. Check wiring"));
      while(true);
    }else{
      tft.print(F("Waiting for satellite fix . . ."));
    }
  }
}

void displayGPS(){
  if(gps.location.isValid()){
    tft.println(F("Coordinate is: "));
    tft.print(gps.location.lat(), 6);
    tft.print(", ");
    tft.print(gps.location.lng(), 6);
    Serial.print("Location: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(", ");
    Serial.println(gps.location.lng(), 6);
    Serial.println("");
  }else{
    Serial.println("INVALID");
  }
}
