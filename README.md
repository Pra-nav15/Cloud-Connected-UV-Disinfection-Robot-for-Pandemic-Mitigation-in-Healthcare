# 🤖 Cloud-Connected UV Disinfection Robot with HMI Control for Pandemic Mitigation in Healthcare

## 📌 Overview
The Cloud-Connected UV Disinfection Robot is an automated robotic system designed to sterilize healthcare environments using UV-C germicidal radiation.

The system integrates ESP32 microcontroller, IoT connectivity, environmental sensors, robotic navigation, and Human-Machine Interface (HMI) control to provide efficient and safe disinfection.

Traditional cleaning methods rely heavily on manual labor and chemical disinfectants, which may leave residues and fail to reach hidden surfaces. This project introduces an automated UV-C disinfection robot that minimizes human exposure to pathogens while ensuring effective sterilization.

The robot monitors environmental conditions such as temperature, humidity, and air quality, and uploads the data to a cloud platform for real-time monitoring and analysis.

---

# ⚙ System Architecture

The system consists of multiple modules integrated through the ESP32 controller.

### Control Unit – ESP32 Microcontroller
- Acts as the main processing unit
- Controls sensors, motors, and UV LEDs
- Handles Wi-Fi communication with cloud services
- Processes environmental sensor data

### Navigation Module
- Robot movement using gear motors
- Motor control using L298N motor driver
- Obstacle detection using ultrasonic sensor

### Disinfection Module
- UV-C LEDs used for germicidal radiation
- Relay module used to control UV LED activation
- UV exposure duration controlled by ESP32

### Environmental Monitoring Module
- DHT22 sensor measures temperature and humidity
- MQ135 sensor measures air quality
- Sensor readings uploaded to cloud database

### HMI and Monitoring Module
- ESP32-CAM used for remote visual monitoring
- 16x2 LCD with I2C interface for local display
- Web-based interface for remote monitoring and control

### Alert and Safety Module
- Piezoelectric buzzer for safety alerts
- RGB LEDs indicate robot operational status
- Warning alerts during UV disinfection operation

---

# 🌐 Cloud Integration

The system integrates cloud technology using Google Firebase.

Key functionalities include:

- Real-time environmental data storage
- Remote monitoring through web interface
- Disinfection activity logging
- Cloud-based system control

Environmental parameters monitored:

- Temperature
- Humidity
- Air Quality

---

# 📊 Environmental Monitoring

Environmental conditions affect disinfection efficiency.

| Parameter | Sensor Used | Description |
|-----------|-------------|-------------|
| Temperature | DHT22 | Monitors environmental temperature |
| Humidity | DHT22 | Helps adjust UV exposure conditions |
| Air Quality | MQ135 | Detects environmental contamination |

Sensor data is uploaded to Firebase cloud database.

---

# 🖥 Hardware Components

- Microcontroller: ESP32 DevKit V1
- Camera Module: ESP32-CAM
- UV Source: UV-C LEDs
- Temperature and Humidity Sensor: DHT22
- Air Quality Sensor: MQ135
- Distance Sensor: HC-SR04 Ultrasonic Sensor
- Motor Driver: L298N Motor Driver
- Motors: 12V 100 RPM Gear Motors
- Display: 16x2 LCD with I2C Interface
- Indicators: RGB LEDs
- Alert Device: Piezoelectric Buzzer
- Control Device: Relay Module
- Power Supply: 12V 7.2Ah Batteries
- Robot Mobility: Robot Wheels

---

# 🛠 Software Implementation

The system is developed using embedded programming and IoT technologies.

Development tools used:

- Arduino IDE for ESP32 programming
- Visual Studio Code for web interface development
- Google Firebase for cloud database

Key software modules:

- Sensor data acquisition
- Motor control and navigation
- UV LED activation control
- Cloud data transmission
- Web-based HMI interface
- Environmental monitoring and logging

---

# 📡 System Workflow

1. Environmental sensors collect temperature, humidity, and air quality data
2. ESP32 processes sensor readings
3. Data is transmitted to Firebase cloud database
4. Operator monitors system through web-based HMI interface
5. Robot navigates using motor driver and ultrasonic sensor
6. UV-C LEDs activate to disinfect surfaces
7. Environmental data and disinfection logs are stored in cloud

---

# 📋 Features

- Automated UV-C disinfection robot
- IoT-based cloud monitoring
- Web-based Human Machine Interface (HMI)
- Real-time environmental sensing
- Cloud data logging
- Obstacle detection using ultrasonic sensor
- Remote monitoring using ESP32-CAM
- Safety alerts using buzzer and RGB LEDs

---

# 🎯 Applications

This system can be used in:

- Hospitals and healthcare facilities
- Isolation wards and ICUs
- Laboratories
- Airports and railway stations
- Public transportation areas
- Schools and offices

---

# 🧠 Conclusion

The Cloud-Connected UV Disinfection Robot provides an automated solution for surface sterilization in healthcare environments.

By integrating UV-C disinfection, environmental monitoring, robotic navigation, and cloud connectivity, the system improves hygiene standards while reducing human exposure to infectious pathogens.

This project demonstrates the potential of IoT-enabled robotic systems for pandemic mitigation and infection control.

---

# 🚀 Possible Enhancements

Future improvements may include:

- Autonomous navigation using SLAM
- AI-based surface recognition
- Dynamic UV intensity control
- Advanced path planning algorithms
- Mobile application control
- Multi-robot coordinated disinfection
- Integration with hospital automation systems

---

# 👨‍💻 Authors

Albert Thomas Abraham  
Anli Joy  
Pranav Prasad  
Remya P
