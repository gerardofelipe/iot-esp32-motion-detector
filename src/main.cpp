#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

const int ledPin = 27;
// const int sensorPins [] = {26,25};
const int sensorPins [] = {26};
int state = LOW;

void setup_wifi() {
  delay(10);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
  
    // if (client.connect("ESP32Client", MQTT_USER, MQTT_PASSWORD)) {
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

int readSensors() {
  for (int pin : sensorPins) {
    if (digitalRead(pin) == HIGH) return HIGH;
  }

  return LOW;
}

void setup() {
  Serial.begin(115200);

  setup_wifi();

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);

  for (int pin : sensorPins) {
    pinMode(pin, INPUT);
  }
}

void loop() {
  if (!client.connected()) reconnect();

  int val = readSensors();

  client.loop();

  if (val == state) return; // nothing to do here

  state = val;
  digitalWrite(ledPin, val);

  if (val == HIGH) {
      Serial.println("Motion detected!");
      client.publish("esp32/motion", "1");
  } else {
      Serial.println("Motion Detection ended!");
      client.publish("esp32/motion", "0");
  }
}