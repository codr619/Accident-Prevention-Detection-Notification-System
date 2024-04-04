# Accident Detection System

This Arduino project detects accidents using an MQ3 sensor and sends SMS alerts with GPS coordinates using a SIM800 module and NeoGPS library.

## Features

- Detects accidents through MQ3 sensor readings.
- Sends SMS alerts using SIM800 module.
- Includes GPS coordinates for location identification.
- Suitable for vehicle safety applications.

## Components

- Arduino board (e.g., NodeMCU)
- MQ3 sensor
- SIM800 module
- NeoGPS library

## Usage

1. Connect the components as per the circuit diagram.
2. Upload the provided sketch to your Arduino board.
3. Ensure proper initialization of the SIM800 module and NeoGPS library.
4. Monitor the serial output for accident detection messages and SMS sending status.

## Circuit Diagram

![Circuit Diagram](link_to_circuit_diagram.png)

## Credits

This project utilizes the following libraries:
- TinyGPS++: [link](https://github.com/mikalhart/TinyGPSPlus)
- NeoGPS: [link](https://github.com/SlashDevin/NeoGPS)

## License

This project is licensed under the [MIT License](LICENSE).
