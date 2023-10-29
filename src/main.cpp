#include "config.h"
#include <BlynkSimpleEsp32.h>

const int ledPin = 27;
const int sensorPins[] = {26};

BlynkTimer timer;
int detectionState = LOW;

BLYNK_CONNECTED() {
    Blynk.syncVirtual(V0);
    Blynk.virtualWrite(V0, HIGH);
    Blynk.syncVirtual(V1);
    Blynk.virtualWrite(V1, detectionState);
}

BLYNK_WRITE(V0) {
    int value = param.asInt();
    digitalWrite(LED_BUILTIN, value);
}

int readSensors() {
    return std::any_of(sensorPins, sensorPins + sizeof(sensorPins) / sizeof(sensorPins[0]), [](int pin) {
        return digitalRead(pin) == HIGH;
    })
               ? HIGH
               : LOW;
}

void checkSensors() {
    int value = readSensors();

    if (value == detectionState) {
        // nothing to do here
        return;
    }

    detectionState = value;

    digitalWrite(ledPin, value);
    Blynk.virtualWrite(V1, value);

    if (value == HIGH) {
        Serial.println("Motion detected!");
    } else {
        Serial.println("Motion Detection ended!");
    }
}

void setup() {
    Serial.begin(115200);

    Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ledPin, OUTPUT);
    for (int pin : sensorPins) {
        pinMode(pin, INPUT);
    }

    // Setup a function to be called every 100 ms
    timer.setInterval(100L, checkSensors);
}

void loop() {
    Blynk.run();
    timer.run();
}