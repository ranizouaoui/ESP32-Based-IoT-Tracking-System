#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(4, 2); // RX, TX pins for software serial on TTGO V1
TinyGPSPlus gps;                // TinyGPS++ object

void setup() {
  Serial.begin(9600);         // Serial monitor for debugging
  gpsSerial.begin(9600);      // NEO-7M baud rate

  delay(1000);                // Wait for GPS module to initialize
}

void loop() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    if (gps.encode(c)) {
      if (gps.location.isUpdated()) {
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);
      }
      if (gps.altitude.isUpdated()) {
        Serial.print("Altitude: ");
        Serial.println(gps.altitude.meters());
      }
      if (gps.speed.isUpdated()) {
        Serial.print("Speed: ");
        Serial.println(gps.speed.kmph());
      }
      if (gps.course.isUpdated()) {
        Serial.print("Course: ");
        Serial.println(gps.course.deg());
      }
      if (gps.date.isUpdated() && gps.time.isUpdated()) {
        Serial.print("Date/Time: ");
        Serial.print(gps.date.year());
        Serial.print("/");
        Serial.print(gps.date.month());
        Serial.print("/");
        Serial.print(gps.date.day());
        Serial.print(" ");
        Serial.print(gps.time.hour());
        Serial.print(":");
        Serial.print(gps.time.minute());
        Serial.print(":");
        Serial.println(gps.time.second());
      }
    }
  }
}
