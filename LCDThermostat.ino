// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
// Include Wire Library for I2C
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor


// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22  // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x27;


//Connect the following:
const int analogInPin = A0; //Arduino pin A0 to ground of light sensor
int led = 7;  // Arduino pin D7 to LED to GND

// Connect pin 1 (on the left) of the temp sensor to +5V
// Connect pin 2 of the sensor to Arduino pin D2
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

//Initialize LCD Display
LiquidCrystal_I2C lcd(i2c_addr, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int sensorValue= 0;
int outputValue = 0;


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(1,0);
  lcd.print("LCD THERMOSTAT");
  dht.begin();
  delay(2000);
  lcd.clear();
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  
  if(outputValue < 45){
    digitalWrite(led,HIGH);
    lcd.noBacklight();
  }
  if (outputValue >= 45){
    digitalWrite(led,LOW);
    lcd.backlight();
  }
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  int hum = static_cast<int>(h);
  int fah = static_cast<int>(f);
  lcd.setCursor(1,1);
  lcd.print("H");
  lcd.setCursor(1,0);
  lcd.print(hum);
  lcd.setCursor(7,1);
  lcd.print("F");
  lcd.setCursor(7,0);
  lcd.print(fah);
  lcd.setCursor(13,0);
  lcd.print(outputValue);
  lcd.setCursor(14,1);
  lcd.print("L");
  delay(1000);
  lcd.clear();
} 
