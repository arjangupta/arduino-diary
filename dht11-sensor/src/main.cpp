#include <Arduino.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 test!");
  dht.begin();
}

void loop() {
  // Delay between measurements
  delay(2000);
  // Read humidity
  float humidity = dht.readHumidity();
  // Read temperature as Celsius
  float temp_c = dht.readTemperature();
  // Read temperature as Fahrenheit
  float temp_f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again)
  if (isnan(humidity) || isnan(temp_c) || isnan(temp_f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(temp_f, humidity);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(temp_c, humidity, false);

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature in Celsius: ");
  Serial.print(temp_c);
  Serial.print(" *C ");
  Serial.print("Temperature in Fahrenheit: ");
  Serial.print(temp_f);
  Serial.print(" *F\t");
  Serial.print("Heat index in Celsius: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print("Heat index in Fahrenheit: ");
  Serial.println(hif);
}