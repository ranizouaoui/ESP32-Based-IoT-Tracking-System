#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#elif defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#include <FirebaseESP8266.h>
#endif

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

#define API_KEY "AIzaSyB9G1utWxdOjattwoSMlHeFq9lFg1Vc7fg"
/* 3. If work with RTDB, define the RTDB URL */
#define DATABASE_URL "https://gps-tracker-fafb6-default-rtdb.europe-west1.firebasedatabase.app/"
/* 4. Define the Firebase Data object */
FirebaseData fbdo;
/* 5. Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* 6. Define the FirebaseConfig data for config data */
FirebaseConfig config;

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Redmi"
#define WIFI_PASSWORD "raniphone123"

void senddata_To_Firebase(String acces_code, String email, String password ,String username  ){
    unsigned long dataMillis = 0;
    int count = 0;
    bool signupOK = false;
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
    String  name= auth.token.uid.c_str(); //<- user uid
    if (millis() - dataMillis > 5000 && signupOK && Firebase.ready())
    {
     dataMillis = millis();
      // Create a JSON object with the data
      FirebaseJson json;
      json.add("uid", name);
      json.add("username", username);
      json.add("acces_code", acces_code);
  // Insert the data into the "usersdata" collection
  if (Firebase.pushJSON(fbdo, "/usersdata", json)) {
    Serial.println("Data inserted successfully");
  } else {
    Serial.println("Data insert failed");
  }
    }

  }
String acces_code ="7IG8BGZ24PB4Z99VDU3F";
String email ="oumaima.slema@gmail.com";
String password ="fuck1234";
String username ="oumaima";
/** 2. Define the API key
 *
 * The API key can be obtained since you created the project and set up
 * the Authentication in Firebase console.
 *
 * You may need to enable the Identity provider at https://console.cloud.google.com/customer-identity/providers
 * Select your project, click at ENABLE IDENTITY PLATFORM button.
 * The API key also available by click at the link APPLICATION SETUP DETAILS.
 *
 */





void setup()
{

    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    senddata_To_Firebase(acces_code,email,password ,username );
}

void loop()
{
}
