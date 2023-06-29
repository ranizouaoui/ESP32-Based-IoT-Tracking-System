/*
  Author: Rani zouaoui + Oumaima Slema
  I wrote this code as part of my PFE which is called "Car Tracker".
  The code provides a server that provides an interactive configuration interface for the entire project.
  If our product is correctly configured, a green LED will light up and
  The authentication information (User name, password, E-mail, Access code) will be sent to the e-mail offered by the user.
  Our code also offers two types of connectivity (Wi-Fi & GPRS)
*/

//? This section includes the necessary libraries for code execution

#include <WiFi.h>                                                      // Library for WiFi connectivity
#include <Arduino.h>                                                   // Arduino core library
#include <ESPAsyncWebServer.h>                                         // Library for asynchronous web server functionality
#include <AsyncTCP.h>                                                  // Asynchronous TCP library
#include "SPIFFS.h"                                                    // SPIFFS (SPI Flash File System) library for file operations
#include <esp_system.h>                                                // ESP32 system library
#include <esp_task_wdt.h>                                              // ESP32 watchdog timer library
#include "esp_err.h"                                                   // ESP32 error handling library
#include "email.h"                                                     // Library for sending email
#include <string.h>                                                    // String manipulation library
#include "esp_err.h"                                                   // ESP32 error handling library
#include "driver/adc.h"                                                // ADC (Analog-to-Digital Converter) library
#include <PubSubClient.h>                                              // MQTT library for ESP32
#include <WiFiClientSecure.h>                                          // Secure WiFi client library
#include <TinyGPS++.h>                                                 // Library for parsing NMEA GPS data
#include <SoftwareSerial.h>                                            // Library for software serial communication
#include <FirebaseESP32.h>                                             // Firebase library for ESP32
#include <addons/TokenHelper.h>                                        // Token helper library for Firebase authentication
#include <addons/RTDBHelper.h>                                         // Real-Time Database helper library for Firebase
#define API_KEY "put your API key for Firebase"                        // API key for Firebase
#define DATABASE_URL "put your URL of the Firebase Real-Time Database" // URL of the Firebase Real-Time Database

SoftwareSerial gpsSerial(16, 17); // RX, TX pins for software serial on ESP 32 V1
TinyGPSPlus gps;
WiFiClientSecure espClient; // for no secure connection use WiFiClient instead of WiFiClientSecure
PubSubClient client(espClient);

//---- MQTT Broker settings
const char *mqtt_server = "put your MQTT broker server address"; // MQTT broker server address
const char *mqtt_username = "put your MQTT broker username";     // MQTT broker username
const char *mqtt_password = "put your MQTT broker password";     // MQTT broker password
const int mqtt_port = 8883;                                      // MQTT broker port number

float latitude = 37.2669776;
float longitude = 9.8776592;
float gpsspeed = 0;
int start = 0; // variable that will be used to block mqtt client initialization if the internet connection is not established

const int pin = 2; // Reset button

// Mqtt topics
const char *sensor1_topic = "latitude";
const char *sensor2_topic = "longitude";
const char *sensor3_topic = "speed";
const char *command2_topic = "startgps";
static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
  )EOF";

/* E-mail credentials */
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "gps.tracker.sender@gmail.com"
#define AUTHOR_PASSWORD "zlmmjpmezglzxygc" // This code is generated from google

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Search for parameter in HTTP requests
const char *PARAM_INPUT_1 = "Username";
const char *PARAM_INPUT_2 = "password";
const char *PARAM_INPUT_3 = "email";
const char *PARAM_INPUT_4 = "inlineRadioOptions";
const char *PARAM_INPUT_5 = "wifi-ssid";
const char *PARAM_INPUT_6 = "wifi-password";

// Sccess point settings
const char *soft_ap_ssid = "GPS-Tracker";
const char *soft_ap_password = NULL;

// Variables
String username;
String password;
String email;
String code;
String wifissid;
String wifipassword;
String connectionoption;
String inputusername;
String inputpassword;
String checkemail;
char incomingChar;
int Value;
// File paths to save input values permanently
const char *usernamePath = "/username.txt";
const char *passwordPath = "/password.txt";
const char *emailPath = "/email.txt";
const char *codePath = "/code.txt";
const char *ssidPath = "/ssid.txt";
const char *wifipasswordPath = "/wifipassword.txt";
const char *checkemailPath = "/check.txt";
// Method to initialize SPIFFS
void initSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

void senddata_To_Firebase(String acces_code, String email, String password, String username)
{
  unsigned long dataMillis = 0;
  int count = 0;
  bool signupOK = false;
  /* 4. Define the Firebase Data object */
  FirebaseData fbdo;
  /* 5. Define the FirebaseAuth data for authentication data */
  FirebaseAuth auth;

  /* 6. Define the FirebaseConfig data for config data */
  FirebaseConfig config;
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  /* Assign the API key (required) */
  config.api_key = API_KEY;
  /* Assign the RTDB URL */
  config.database_url = DATABASE_URL;
  Firebase.reconnectWiFi(true);
  Serial.print("Sign up new user... ");
  /* Sign up */
  if (Firebase.signUp(&config, &auth, email, password))
  {
    Serial.println("ok");
    signupOK = true;
  }
  else
  {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  String name = auth.token.uid.c_str(); //<- user uid
  if (millis() - dataMillis > 5000 && signupOK && Firebase.ready())
  {
    dataMillis = millis();
    // Create a JSON object with the data
    FirebaseJson json;
    json.add("uid", name);
    json.add("username", username);
    json.add("acces_code", acces_code);
    // Insert the data into the "usersdata" collection
    if (Firebase.pushJSON(fbdo, "/usersdata", json))
    {
      Serial.println("Data inserted successfully");
    }
    else
    {
      Serial.println("Data insert failed");
    }
  }
}
// MQtt Client function
void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-"; // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("connected");

      client.subscribe(command2_topic); // subscribe the topics here
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds"); // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
// MQtt Client function
void callback(char *topic, byte *payload, unsigned int length)
{
  String incommingMessage = "";
  for (int i = 0; i < length; i++)
    incommingMessage += (char)payload[i];

  Serial.println("Message arrived [" + String(topic) + "]" + incommingMessage);

  //--- check the incomming message

  //  check for other commands
  //  if( strcmp(topic,command2_topic) == 0){
  //
  //        }
  //      if (incommingMessage.equals("0")) {
  //        digitalWrite(pompe, LOW);
  //        }
  //   }
}
void publishMessage(const char *topic, String payload, boolean retained)
{
  if (client.publish(topic, payload.c_str(), true))
    Serial.println("Message publised [" + String(topic) + "]: " + payload);
}

// Method to read File from SPIFFS
String readFile(fs::FS &fs, const char *path)
{
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  String fileContent = "empty";
  if (file.size() > 0)
  {
    while (file.available())
    {
      fileContent = file.readStringUntil('\n');
      break;
    }
  }
  file.close();
  return fileContent;
}

// Method to write file to SPIFFS
void writeFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    Serial.println("- file written");
    file.close();
  }
  else
  {
    Serial.println("- frite failed");
    file.close();
  }
}

// Method to delete Content from SPIFFS
void DeleteContent(fs::FS &fs, const char *path)
{
  fs.remove(path);
  Serial.println("File content deleted");
}
void setup_ap(const char *ssid, const char *password)
{
  Serial.println("\n[*] Creating ESP32 AP");
  WiFi.softAP(ssid, password);
  Serial.print("[+] AP Created with IP Gateway ");
  Serial.println(WiFi.softAPIP());
}
/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);
// Method to initialize WiFi
bool initWiFi(const char *wifi_network_ssid, const char *wifi_network_password)
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(wifi_network_ssid, wifi_network_password);
  Serial.println("\n[*] Connecting to WiFi Network");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.print("\n[+] Connected to the WiFi network with local IP : ");
  Serial.println(WiFi.localIP());
  start = 1;
  if (checkemail == "yes")
  {
    senddata_To_Firebase(code, email, password, username);
    SendEmail(email, username, password, code);
    DeleteContent(SPIFFS, checkemailPath);
  }
}

// Method to check Wi-Fi Connection
bool check_wifi(const char *ssid, const char *password)
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  int i = 0;
  bool isConnected = false;
  while (WiFi.status() != WL_CONNECTED && i < 10)
  {
    delay(500);
    Serial.print(".");
    esp_task_wdt_reset(); //! reset the watchdog timer to avoid its triggering
    i++;
  }
  if (i >= 10)
  {
    Serial.println("Failed to connect to WiFi");
    isConnected = false;
  }
  else
  {
    Serial.println("WiFi connected successfully");
    isConnected = true;
  }
  return isConnected;
}
// Method to restart the ESP32 and SPIFFS
void resetESP32()
{
  DeleteContent(SPIFFS, usernamePath);
  DeleteContent(SPIFFS, passwordPath);
  DeleteContent(SPIFFS, emailPath);
  DeleteContent(SPIFFS, codePath);
  DeleteContent(SPIFFS, wifipasswordPath);
  DeleteContent(SPIFFS, ssidPath);
  DeleteContent(SPIFFS, checkemailPath);
  esp_restart();
}

// Method to Generate an access code
String GenererCode()
{
  String chaine = "AZ8E7R9TY1UIOPQS2DFG5HJK3LMWX4CV6BN";
  String code;
  int index;

  for (int i = 0; i < 20; i++)
  {
    index = random(34);
    code += chaine[index];
  }
  return code;
}

// Method to save data to SPIFFS after successful registration
bool SaveDataWithWiFiConnection()
{
  writeFile(SPIFFS, usernamePath, username.c_str());
  esp_task_wdt_reset();
  writeFile(SPIFFS, emailPath, email.c_str());
  esp_task_wdt_reset();
  writeFile(SPIFFS, passwordPath, password.c_str());
  esp_task_wdt_reset();
  writeFile(SPIFFS, ssidPath, wifissid.c_str());
  esp_task_wdt_reset();
  writeFile(SPIFFS, wifipasswordPath, wifipassword.c_str());
  esp_task_wdt_reset();
  writeFile(SPIFFS, checkemailPath, "yes");
  esp_task_wdt_reset();
  code = GenererCode();
  esp_task_wdt_reset();
  writeFile(SPIFFS, codePath, code.c_str());
}

// Method to send the sign in credentials to user email
void SendEmail(String RECIPIENT_EMAIL, String username, String password, String code)
{
  esp_task_wdt_delete(NULL);
  // SMTPSession smtp;
  smtp.debug(1);
  smtp.callback(smtpCallback);
  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Set the message headers */
  message.sender.name = "GPS Tracker";
  message.sender.email = AUTHOR_EMAIL;

  message.subject = "The sign in credentials";
  message.addRecipient(username, RECIPIENT_EMAIL);
  /*Send HTML message*/
  String htmlMsg = "<div style=\"color:#2f4468;\"><h1>The sign in credentials:</h1><p>- Username: " + username + "</p><p>- Email: " + RECIPIENT_EMAIL + "</p><p>- Password: " + password + "</p><p>- Access code: " + code + "</p></div>";
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;
  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
  {
    Serial.println("Error sending Email, " + smtp.errorReason());
  }
}
void setup()
{
  Serial.begin(9600); // Serial monitor for debugging
  pinMode(pin, INPUT);
  gpsSerial.begin(9600);
  initSPIFFS();
  setup_ap(soft_ap_ssid, soft_ap_password);
  username = readFile(SPIFFS, usernamePath);
  password = readFile(SPIFFS, passwordPath);
  wifissid = readFile(SPIFFS, ssidPath);
  wifipassword = readFile(SPIFFS, wifipasswordPath);
  checkemail = readFile(SPIFFS, checkemailPath);
  email = readFile(SPIFFS, emailPath);
  code = readFile(SPIFFS, codePath);
  Serial.println(username);
  Serial.println(password);
  Serial.println(wifissid);
  Serial.println(wifipassword);
  Serial.println(code);
  Serial.println(email);
  Serial.println(checkemail);

  if (wifissid != "empty" && wifipassword != "empty")
  {
    initWiFi(wifissid.c_str(), wifipassword.c_str()); //? The WiFi connection will be initialized if the user has properly configured
    espClient.setCACert(root_ca);                     // enable this line and the the "certificate" code for secure connection.
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
  }
  if (username == "empty" && password == "empty") //! The configuration has not yet been carried out
  {
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/signin.html", "text/html"); });
    server.serveStatic("/", SPIFFS, "/");
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request)
              {
      int params = request->params();
      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST username value
          if (p->name() == PARAM_INPUT_1) {
            username = p->value().c_str();
          }
          // HTTP POST email value
          if (p->name() == PARAM_INPUT_3) {
            email = p->value().c_str();
          }
          // HTTP POST password value
          if (p->name() == PARAM_INPUT_2) {
            password = p->value().c_str();
          }
          // HTTP POST connection option(Wi-Fi or GPRS) value
          if (p->name() == PARAM_INPUT_4) {
            connectionoption = p->value().c_str();
          }
          // HTTP POST WiFi-SSID value
          if (p->name() == PARAM_INPUT_5) {
            wifissid = p->value().c_str();
          }
          // HTTP POST WiFi-password value
          if (p->name() == PARAM_INPUT_6) {
            wifipassword = p->value().c_str();
          }
        }
      }
      if (connectionoption = "option1")
      {
        //? The user chooses a wifi connection
        // SaveDataWithWiFiConnection();
         if(check_wifi(wifissid.c_str(), wifipassword.c_str())){
            request->send(SPIFFS, "/register-done.html", "text/html");
            }else{
             request->send(200, "text/plain", "Please check your Wi-Fi settings"); 
              }
      }
      else
      {
        request->send(200, "text/plain", "Gsm is not configured yet");
      } });

    // Route to reboot
    server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request)
              {
      request->send(200, "text/plain", "you will receive an email in 15 seconds. you can always make additional configuration on the link: http://192.168.4.1/");
      // request->send(SPIFFS, "/check-email.html", "text/html");
      SaveDataWithWiFiConnection();
      delay(1000);
      esp_restart(); });
    server.begin();
  }
  else
  {
    // Web Server Root URL /
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/login.html", "text/html"); });

    server.serveStatic("/", SPIFFS, "/");

    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request)
              {
      int params = request->params();
      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST username value
          if (p->name() == PARAM_INPUT_1) {
            inputusername = p->value().c_str();
          }
          // HTTP POST password value
          if (p->name() == PARAM_INPUT_2) {
            inputpassword = p->value().c_str();
          }
        }
      }
      delay(2000);
      if (username == inputusername && password == inputpassword) {
        request->send(SPIFFS, "/index.html", "text/html");
      } else {
        request->send(200, "text/plain", "Mot de passe incorrect");
      } });
    server.begin();
  }
}

void loop()
{

  if (digitalRead(pin) == HIGH)
  {               // Vérifie l'état de la broche
    resetESP32(); // Appelle la fonction resetESP32()
  }

  {
    if (!client.connected())
    {
      reconnect();
    }
    client.loop();
    while (gpsSerial.available())
    {
      if (digitalRead(pin) == HIGH)
      {               // Vérifie l'état de la broche
        resetESP32(); // Appelle la fonction resetESP32()
      }
      char c = gpsSerial.read();
      if (gps.encode(c))
      {
        if (gps.location.isUpdated())
        {
          Serial.print("Latitude: ");
          latitude = gps.location.lat();
          Serial.println(latitude, 6);
          Serial.print("Longitude: ");
          longitude = gps.location.lng();
          Serial.println(longitude, 6);
          publishMessage(sensor1_topic, String(latitude), true);
          publishMessage(sensor2_topic, String(longitude), true);
        }
        if (gps.speed.isUpdated())
        {
          Serial.print("Speed: ");
          gpsspeed = gps.speed.kmph();
          Serial.println(gpsspeed);
          publishMessage(sensor3_topic, String(gpsspeed), true);
        }
        delay(1000);
      }
      else
      {
        publishMessage(sensor1_topic, String(latitude), true);
        publishMessage(sensor2_topic, String(longitude), true);
        publishMessage(sensor3_topic, String(gpsspeed), true);
        delay(1000);
      }
    }
  }
}
/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status)
{
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success())
  {
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++)
    {
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients.c_str());
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject.c_str());
    }
    Serial.println("----------------\n");
  }
}
