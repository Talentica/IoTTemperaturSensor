# IoTTemperaturSensor

This project collects and shows the temperature data from various sensors. Multiple BLE beacons are designed to measure ambient temperature and broadcast it over BLE, which is collected by a gateway and sent to a cloud.

The sensors are custom designed hardware using Nordic nRF51 chipset.
The gateway is a Raspberry Pi connected to a BLE Nano (based on Nordic) to collect the data. The RPi then sends this data to the cloud using MQTT protocol, secured with TLS 1.2.
The cloud used is AWS-IoT, which stores the data and shows it as a graph on a dashboard.

