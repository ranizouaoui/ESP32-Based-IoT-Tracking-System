

// Your GPRS credentials (leave empty, if not needed)
const char apn[] = "internet.tn";    
const char gprsUser[] = ""; // GPRS User
const char gprsPass[] = ""; // GPRS Password

// Server details
// The server variable can be just a domain name or it can have a subdomain. It depends on the service you are using
const char server[] = "https://jsonplaceholder.typicode.com"; // domain name: example.com
const char resource[] = "/todos/1";                           // resource path, for example: /post-data.php

// TTGO T-Call pins
#define SIM800L_RX 26
#define SIM800L_TX 27
#define SIM800L_PWRKEY 4
#define SIM800L_RST 5
#define SIM800L_POWER 23

// Configure TinyGSM library
#define TINY_GSM_MODEM_SIM800   // Modem is SIM800
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
#include <TinyGsmClient.h>
#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 3600     /* Time ESP32 will go to sleep (in seconds) 3600 seconds = 1 hour */

#define IP5306_ADDR 0x75
#define IP5306_REG_SYS_CTL0 0x00

// TinyGSM Client for Internet connection
TinyGsm modem(Serial2);
TinyGsmClient client(modem);

void setup()
{
  // put your setup code here, to run once:
  pinMode(SIM800L_POWER, OUTPUT);
  digitalWrite(SIM800L_POWER, HIGH);

  Serial.begin(115200);
  Serial.println("ESP32+SIM800L GPRS Connection Test");
  delay(10000);

  Serial2.begin(115200, SERIAL_8N1, SIM800L_RX, SIM800L_TX);
  Serial.println("Lessgo bitch!!!");

  // Initialize the SIM800L Module
  Serial.println("Initializing modem...");
  modem.restart();

  modem.gprsConnect(apn, gprsUser, gprsPass);
}

void loop()
{
  // put your main code here, to run repeatedly:

  // Network registration
  Serial.print("Waiting for network...");
  if (!modem.waitForNetwork())
  {
    Serial.println(" fail");
    delay(10000);
    return;
  }
  Serial.println(" success");

  if (modem.isNetworkConnected())
  {
    Serial.println("Network connected");
  }

  // GPRS connection parameters
  Serial.print(F("Connecting to "));
  Serial.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass))
  {
    Serial.println(" fail");
    delay(10000);
    return;
  }
  Serial.println(" success");

  if (modem.isGprsConnected())
  {
    Serial.println("GPRS connected");
  }

  // HTTP GET request:
  client.print(String("GET ") + resource + " HTTP/1.0\r\n");
  client.print(String("Host: ") + server + "\r\n");
  client.print("Connection: close\r\n\r\n");

  delay(1000);

  // Wait a minute before trying again
  delay(60000);
}
