#include <WiFi.h>
#include "ThingSpeak.h"
#ifdef __cplusplus
extern "C" {
#endif

uint8_t temprature_sens_read();

#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();
const char* ssid = "";   // your network SSID (name)
const char* password = "";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 2001752;
const char * myWriteAPIKey = "3W23OIDUMD20MA79";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

// Variable to hold temperature readings
float temperatureC;
//uncomment if you want to get temperature in Fahrenheit
//float temperatureF;





void setup() {
  Serial.begin(115200);  //Initialize serial
  Serial.println("Demo Started!");

  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Get a new temperature reading
    temperatureC = (temprature_sens_read() - 32) / 1.8;
    Serial.print("Temperature (ºC): ");
    Serial.println(temperatureC);


    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureC, myWriteAPIKey);
    //uncomment if you want to get temperature in Fahrenheit
    //int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureF, myWriteAPIKey);

    if (x == 200) {
      Serial.println("Channel update successful.");
    }
    else {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
