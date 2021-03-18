#include <DHT.h>

/* Data pin and type for DHT11 temperature/humidity sensor */
#define DHT_TYPE    DHT11
#define DHT_PIN     8

DHT dht = DHT(DHT_PIN, DHT_TYPE);

void setup() {
  dht.begin();
  Serial.begin(115200);
}

void loop() {
  dht_do_all_measurements();
  delay(2000);
}

void dht_do_all_measurements() {
  /* Read humidity as relative % */
  float h = dht.readHumidity();
  /* Read temperature as Celsius (default argument) */
  float t = dht.readTemperature();
  /* Read temperature as Fahrenheit (isFahrenheit = true) */
  float f = dht.readTemperature(true);

  /* Check if any reads failed and exit early (to try again) */
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  /* Compute heat index in Fahrenheit (default argument for "isFahreheit") */
  float hif = dht.computeHeatIndex(f, h);
  /* Compute heat index in Celsius ("isFahreheit" = false) */
  float hic = dht.computeHeatIndex(t, h, false);

  /* Print results to serial */
    Serial.print("  ");
    Serial.print(f);
    Serial.print("  ");
    Serial.print(hif);
    Serial.print("  ");
    Serial.print(t);
    Serial.print("  ");
    Serial.print(hic);
    Serial.println("  ");
}

