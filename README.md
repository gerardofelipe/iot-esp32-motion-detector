# Simple IoT ESP32 Blynk Motion Sensor

This project uses an ESP32 microcontroller to detect motion using one or more sensors and send the information to the Blynk cloud service. The code is written in C/C++ using the Arduino framework and PlatformIO.

## Dependencies

This project depends on the following libraries:

- [Blynk](https://blynk.io/) - Blynk is a platform with iOS and Android apps to control Arduino, Raspberry Pi and the likes over the Internet.

## Configuration

The `config.h` file contains the following configuration options:

- `WIFI_SSID`: the SSID of the WiFi network to connect to
- `WIFI_PASSWORD`: the password for the WiFi network
- `BLYNK_TEMPLATE_ID`: the template ID for the Blynk project
- `BLYNK_TEMPLATE_NAME`: the template name for the Blynk project
- `BLYNK_AUTH_TOKEN`: the authentication token for the Blynk project

## Usage

1. Upload the code to your ESP32 microcontroller using the PlatformIO IDE or the `pio run --target upload command` in your project directory.
2.  Connect one or more motion sensors to the ESP32 using the `sensorPins` array in the code.
3. Use the Blynk app to monitor the motion detection status. When motion is detected, the ESP32 will turn on the LED and send the motion detection status to the Blynk cloud service. The same will happen when motion is no longer detected, but the LED will be turned off.
4. You can use the Blynk app to turn on/off the LED on the ESP32.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

Let me know if you need any further assistance!