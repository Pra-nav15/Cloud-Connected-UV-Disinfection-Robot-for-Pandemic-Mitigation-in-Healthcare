🤖 Cloud-Connected UV Disinfection Robot with HMI Control
📌 Overview

The Cloud-Connected UV Disinfection Robot is an automated robotic system designed to sterilize healthcare environments using UV-C germicidal radiation. The system integrates IoT connectivity, environmental sensing, robotic mobility, and Human-Machine Interface (HMI) control to provide efficient and safe disinfection.

Traditional cleaning methods rely heavily on manual labor and chemical disinfectants, which can leave residues and may not reach hidden surfaces. This project introduces an automated UV-C disinfection robot that minimizes human exposure to pathogens while ensuring effective sterilization.

The robot is equipped with environmental sensors, UV-C LEDs, motorized navigation, and cloud connectivity to monitor environmental conditions and adjust disinfection parameters accordingly.

This system is particularly useful in hospitals and healthcare facilities, where maintaining high hygiene standards is critical for preventing hospital-acquired infections (HAIs) and controlling pandemic outbreaks.

⚙ System Architecture

The system consists of multiple integrated modules working together to perform automated disinfection.

Control Unit – ESP32 Microcontroller

Acts as the main processing unit

Controls sensors, motors, and UV LEDs

Handles Wi-Fi communication with cloud services

Processes environmental data

Navigation Module

Robot movement controlled using gear motors

Motor control implemented through L298N motor driver

Obstacle detection using ultrasonic sensor

Disinfection Module

UV-C LEDs used for germicidal radiation

Relay module used to control UV-C LED activation

UV exposure duration controlled by microcontroller

Environmental Monitoring Module

DHT22 sensor for temperature and humidity monitoring

MQ135 sensor for air quality measurement

Sensor readings uploaded to cloud platform

HMI and Monitoring Module

ESP32-CAM module used for remote visual monitoring

16x2 LCD display with I2C interface for local information display

Website-based interface for remote system control

Alert and Safety Module

Piezoelectric buzzer used for warning signals

RGB LEDs indicate robot operational status

Safety alerts during UV disinfection operation

🌐 Cloud Integration

The system integrates cloud technology using Google Firebase to provide real-time monitoring and data logging.

Cloud functionalities include:

Real-time sensor data storage

Remote monitoring of environmental parameters

Disinfection activity logging

Web interface control for operators

Environmental parameters monitored:

Temperature

Humidity

Air Quality

The cloud platform ensures secure data access and traceability of disinfection operations.

📊 Environmental Monitoring

Environmental factors significantly influence disinfection efficiency.

Parameter	Sensor Used	Purpose
Temperature	DHT22	Monitor environmental conditions
Humidity	DHT22	Adjust UV exposure if humidity increases
Air Quality	MQ135	Detect contamination levels

These values are uploaded to Firebase cloud database for analysis and monitoring.

🖥 Hardware Components

Microcontroller: ESP32 DevKit V1

Camera Module: ESP32-CAM

UV Source: UV-C LEDs

Temperature & Humidity Sensor: DHT22

Air Quality Sensor: MQ135

Distance Sensor: HC-SR04 Ultrasonic Sensor

Motor Driver: L298N Motor Driver

Motors: 12V 100 RPM Gear Motors

Display: 16x2 LCD with I2C Interface

Indicators: RGB LEDs

Alert Device: Piezoelectric Buzzer

Control Device: Relay Module

Power Supply: 12V 7.2Ah Batteries

Robot Mobility: Robot Wheels

🛠 Software Implementation

The project is implemented using embedded programming and IoT technologies.

Software tools used:

Arduino IDE for ESP32 programming

Visual Studio Code for web interface development

Google Firebase for cloud database and monitoring

Key software modules include:

Sensor data acquisition

Motor control and robot navigation

UV LED activation control

Cloud data transmission

Web-based HMI control interface

Environmental monitoring and logging

📡 System Workflow

1️⃣ Environmental sensors collect temperature, humidity, and air quality data

2️⃣ ESP32 processes sensor readings

3️⃣ Data is transmitted to Firebase cloud database

4️⃣ Operator monitors robot through HMI web interface

5️⃣ Robot navigates using motor driver and ultrasonic sensors

6️⃣ UV-C LEDs activate to perform surface disinfection

7️⃣ Environmental data and disinfection logs are stored in cloud

📋 Features

Automated UV-C disinfection robot

Cloud-connected environmental monitoring

Web-based Human Machine Interface (HMI)

Real-time sensor data logging

Remote system monitoring

Obstacle detection using ultrasonic sensors

Visual monitoring using ESP32-CAM

Safety alerts using buzzer and RGB LEDs

🎯 Applications

This system can be used in:

Hospitals and healthcare facilities

Isolation wards and ICUs

Laboratories

Public transport facilities

Airports and railway stations

Schools and offices

The robot helps reduce infection spread in high-risk environments.

📊 Results & Analysis

The developed system successfully demonstrated:

Reliable robot navigation

Real-time environmental monitoring

Effective UV-C based surface sterilization

Cloud-based data logging and monitoring

Web interface for remote system control

Environmental parameters were analyzed using impact scoring and data visualization, including:

Bar chart analysis

Impact percentage distribution

Environmental factor contribution analysis

🧠 Conclusion

The Cloud-Connected UV Disinfection Robot provides an efficient solution for automated surface sterilization in healthcare environments.

By integrating UV-C disinfection, environmental monitoring, robotic mobility, and cloud connectivity, the system enhances hygiene standards while minimizing human exposure to infectious pathogens.

The project demonstrates how IoT-enabled robotic systems can support pandemic mitigation and infection control in healthcare facilities.

🚀 Future Enhancements

Possible improvements include:

Autonomous navigation using SLAM

AI-based surface recognition

Dynamic UV exposure control

Advanced path planning algorithms

Mobile app for robot control

Multi-robot coordinated disinfection

Integration with hospital automation systems

👨‍💻 Authors

Albert Thomas Abraham

Anli Joy

Pranav Prasad

Remya P
