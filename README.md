# Simple IoT ESP32 MQTT Motion Sensor

This project uses an ESP32 microcontroller to detect motion using one or more sensors and publish the results to an MQTT broker. The code is written in C++ using the Arduino framework and PlatformIO.

## Dependencies

This project depends on the following libraries:

- WiFi.h
- PubSubClient.h
- Wire.h

## Configuration

The `config.h` file contains the following configuration options:

- `WIFI_SSID`: the SSID of the WiFi network to connect to
- `WIFI_PASSWORD`: the password for the WiFi network
- `MQTT_SERVER`: the hostname or IP address of the MQTT broker
- `MQTT_PORT`: the port number for the MQTT broker
- `MQTT_USER`: the username for the MQTT broker (optional)
- `MQTT_PASSWORD`: the password for the MQTT broker (optional)

## Usage

1. Upload the code to your ESP32 microcontroller using the PlatformIO IDE or the `pio run --target upload command` in your project directory.
2.  Connect one or more motion sensors to the ESP32 using the `sensorPins` array in the code.
3. When motion is detected, the ESP32 will publish a message to the `esp32/motion` topic on the MQTT broker with a payload of `1`. When motion detection ends, the ESP32 will publish a message to the same topic with a payload of `0`.
4. ESP32 will be suscribed to the `esp32/output` topic to turn on/off the built-in led.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

Let me know if you need any further assistance!