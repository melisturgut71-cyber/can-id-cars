ESP32 Vehicle Telematics & MQTT Gateway
📖 Overview
This project is an IoT-based Vehicle Telematics System designed to read real-time data from an Opel Corsa via the CAN Bus network. Using an ESP32 microcontroller and an MCP2515 CAN module, the system sniffs specific CAN IDs, decodes the raw hexadecimal data into meaningful engineering units (RPM, Temperature, Voltage, etc.), and transmits this data wirelessly to an MQTT Broker in JSON format.

This system serves as a bridge between the vehicle's internal network (OBD-II port) and remote monitoring dashboards.

🚀 Features
Real-time CAN Sniffing: Reads data at 500kbps from the vehicle's High-Speed CAN Bus.

Data Parsing: Decodes specific CAN frames for:

🏎️ Engine RPM

🌡️ Engine Coolant & Outside Temperature

⛽ Fuel Level (Calculated)

⚡ Battery Voltage

🚦 Pedal Status (Gas/Brake detection)

🔑 Ignition & Engine State

🚗 Odometer (Total KM)

Connectivity: Connects to WiFi and maintains a persistent MQTT connection.

JSON Serialization: Packages all sensor data into a structured JSON payload for easy integration with Node-RED, Home Assistant, or custom mobile apps.

🛠️ Hardware Requirements
Microcontroller: ESP32 Development Board (DOIT DEVKIT V1 or similar)

CAN Interface: MCP2515 CAN Bus Module (SPI Interface)

Connection: OBD-II Connector (to access CAN-H and CAN-L lines)

Power Supply: 5V/3.3V (typically powered via USB or step-down converter from the car battery)

MCP2515 Pin,ESP32 Pin,Function
VCC,5V,Power
GND,GND,Ground
CS,GPIO 5,Chip Select
SO (MISO),GPIO 19,SPI Data Out
SI (MOSI),GPIO 23,SPI Data In
SCK,GPIO 18,SPI Clock
INT,Not Used,Interrupt
