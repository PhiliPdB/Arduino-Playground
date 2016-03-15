#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 6
#define DHTTYPE DHT11

// Initialize LCD display.
LiquidCrystal lcd(7,8,9,10,11,12);
// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.write("Temp: ");
  lcd.setCursor(0,1);
  lcd.write("Humidity: ");

  dht.begin();

  Serial.begin(9600);
  Serial.println("WeatherStation:");
}

void loop() {
  readDHT();

  // Wait a few seconds between measurements.
  delay(2000);
}

void readDHT() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  int t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");

  if (t < 10) {
    lcd.setCursor(13,0);
  } else {
    lcd.setCursor(12,0);
  }
  lcd.print(t);
  lcd.print((char) 223);
  lcd.print("C");

  if (h < 100) {
    if (h < 10) {
      lcd.setCursor(14,1);
    } else {
      lcd.setCursor(13,1);
    }
  } else {
    lcd.setCursor(12,1);
  }
  lcd.print(h);
  lcd.print("%");
}

