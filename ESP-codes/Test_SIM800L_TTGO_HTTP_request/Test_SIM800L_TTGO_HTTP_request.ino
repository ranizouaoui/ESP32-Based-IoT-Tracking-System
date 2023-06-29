// TTGO T-Call pins
#define MODEM_RX 26
#define MODEM_TX 27
#define MODEM_PWRKEY 4
#define MODEM_RST 5
#define MODEM_POWER 23
#define TINY_GSM_MODEM_SIM800   // Modem is SIM800
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
#include <Wire.h>
#include <TinyGsmClient.h>
#include <TinyGsmClient.h>

// APN credentials
const char apn[] = "internet.tn";
const char gprsUser[] = "";
const char gprsPass[] = "";



// Initialize TinyGSM client
TinyGsm modem(Serial2);

void setup() {
  // Start serial communication
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  
  // Set modem reset and power pins
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER, OUTPUT);

  // Restart the modem using the reset pin
  digitalWrite(MODEM_RST, LOW);
  delay(100);
  digitalWrite(MODEM_RST, HIGH);

  // Power up the modem
  digitalWrite(MODEM_POWER, HIGH);
  delay(2000);

 

  // Unlock your SIM card with a PIN if needed
  // modem.simUnlock("1234");

  // Connect to GPRS
  Serial.println("Connecting to GPRS...");
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    Serial.println("GPRS connection failed");
    return;
  }

  Serial.println("GPRS connected");
  // Print local IP address
  Serial.print("IP address: ");
  Serial.println(modem.localIP());
}

void loop() {
   // Your GPRS code here
  // Example: send an HTTP GET request
  Serial.println("Sending HTTP GET request...");
  
  modem.sendAT("+HTTPPARA=\"URL\",\"http://worldtimeapi.org/api/timezone/Africa/Tunis\"");
  delay(1000);
  modem.sendAT("+HTTPACTION=0");
  delay(5000);
  
  String response;
  response = modem.waitResponse();
  
  Serial.println("Response:");
  Serial.println(response);
  
  // Wait for some time before the next request
  delay(5000);
}
