#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>


// Replace the next variables with your SSID/Password combination
const char* ssid = "Demo";
const char* password = "123123123";
char * sub_topic = "j17qwerty123456A"; //This is YOU (Your team)
char * pub_topic = "j17qwerty123456B"; //This is THEM (Another team)



// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];




// LED Pin
const int ledPin = 2;

void setup() {
  Serial.begin(115200);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(ledPin, OUTPUT);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
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
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message

  if (messageTemp == "on") {
    Serial.println("on");
    digitalWrite(ledPin, HIGH);
    client.publish(pub_topic, "LED is ON");
  }
  else if (messageTemp == "off") {
    Serial.println("off");
    digitalWrite(ledPin, LOW);
//    client.publish(pub_topic, "LED is OFF");
  }
  else {
    Serial.println(messageTemp);
//    client.publish(pub_topic, "off");
    
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    String mac = WiFi.macAddress();

    char bufMAC[mac.length() + 2];
    mac.toCharArray(bufMAC, mac.length());

    if (client.connect(bufMAC)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(sub_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if (Serial.available()) {
    String recvString = Serial.readString();
    if (recvString.indexOf("on") >= 0) {
      client.publish(pub_topic, "on");
    }
    else if (recvString.indexOf("off") >= 0) {
      client.publish(pub_topic, "off");
    }
    else {
      char buf[recvString.length() + 2];
      recvString.toCharArray(buf, recvString.length()+2);

      client.publish(pub_topic, buf);
    }


  }

}
