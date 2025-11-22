#include <WiFi.h>
#include <Wire.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>  // Include the Adafruit DHT library
#include <Firebase_ESP_Client.h>

// Pin Definitions
#define DHTPIN 27       // DHT22 sensor pin
#define DHTTYPE DHT22   // Define the type of DHT sensor
#define MQ135_PIN 23    // MQ135 sensor pin (Analog)
#define BUZZER_PIN 15   // Buzzer pin
#define RED_PIN 2      // RGB LED Red pin
#define GREEN_PIN 4    // RGB LED Green pin
#define TRIG_PIN 12     // Ultrasonic sensor Trig pin
#define ECHO_PIN 13     // Ultrasonic sensor Echo pin
#define RELAY_PIN 25     // Relay control pin

// I2C Pin Definitions for ESP32
#define SDA_PIN 21      // I2C SDA pin
#define SCL_PIN 22      // I2C SCL pin

int motor1Pin1 = 33; 
int motor1Pin2 = 32; 
int enable1Pin = 0;

// Motor 2 Pins
int motor2Pin1 = 5; 
int motor2Pin2 = 19; 
int enable2Pin = 0;

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object

// Initialize LCD (address 0x27, 16 chars, 2 lines)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Ensure the I2C address is correct
#include "addons/TokenHelper.h"//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"//Provide the token generation process info.
// Insert your network credentials
#define WIFI_SSID "Redmi Note 9 Pro"
#define WIFI_PASSWORD "12345678p"

// Insert Firebase project API Key
#define API_KEY "AIzaSyBEcSJNhI9juvY-yHi7oYtcu0fFcE9PuEo"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://uv-disinfection-robot-default-rtdb.asia-southeast1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

WebServer server(80);

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = true; 


// Function to handle root page

void handleRoot() {
  const char html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
      body {
        font-family: Arial, sans-serif;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: flex-start;
        height: 100vh;
        margin: 0;
        background-color: #fff; /* White background */
        color: #000;
      }

      h1 {
        margin-top: 15px;
        font-size: 1.8rem;
        color: #000;
        padding: 10px 20px;
        border-radius: 5px;
        background-color: #f4f4f4;
        box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
      }

      .button {
        background-color: #007bff; /* Blue button */
        border: none;
        color: white;
        padding: 12px 24px;
        font-size: 16px;
        margin: 5px;
        cursor: pointer;
        border-radius: 8px;
        transition: background-color 0.3s ease;
      }

      .button:hover {
        background-color: #0056b3; /* Darker blue on hover */
      }

      .button2 {
        background-color: #6c757d; /* Gray button */
      }
      
      .button3 {
        background-color: #06f43d; /* Gray button */
      }

      .button2:hover {
        background-color: #5a6268; /* Darker gray on hover */
      }

      .camera-frame {
        border: 2px solid #007bff; /* Blue border */
        border-radius: 10px;
        overflow: hidden;
        width: 320px;
        height: 240px;
        margin: 20px auto;
        box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
      }

      .camera-frame img {
        width: 100%;
        height: 100%;
        object-fit: cover;
      }

      .joystick {
        display: grid;
        grid-template-areas:
          ". forward ."
          "left stop right"
          ". reverse uv";
        grid-gap: 10px;
        justify-content: center;
        align-items: center;
        margin: 20px auto;
        width: 240px;
      }

      .joystick button {
        grid-area: auto;
      }

      .joystick .forward {
        grid-area: forward;
      }

      .joystick .left {
        grid-area: left;
      }

      .joystick .stop {
        grid-area: stop;
      }

      .joystick .right {
        grid-area: right;
      }

      .joystick .reverse {
        grid-area: reverse;
      }
      .joystick .uv {
        grid-area: uv;
      }

      input[type="range"] {
        width: 100%;
        max-width: 300px;
        margin: 10px auto;
      }
    </style>
    <script>
      function moveForward() {
        fetch("/forward");
      }
      function moveLeft() {
        fetch("/left");
      }
      function stopRobot() {
        fetch("/stop");
      }
      function moveRight() {
        fetch("/right");
      }
      function moveReverse() {
        fetch("/reverse");
      }
      let uvLightState = false; // UV light state

      function toggleUVLight() {
        uvLightState = !uvLightState;
        const action = uvLightState ? "on" : "off";
        document.getElementById("uvButton").innerHTML = `LIGHT ${action.toUpperCase()}`;
        fetch(`/uv?state=${action}`);
      }
    </script>
  </head>
  <body>
    <h1>HMI CONTROL FOR DISINFECTION ROBOT</h1>

    <!-- Camera Frame -->
    <div class="camera-frame">
      <img id="stream" src="http://192.168.80.92:81/stream" crossorigin="">
    </div>

    <!-- Joystick Control -->
    <div class="joystick">
      <button class="button forward" onclick="moveForward()">FORWARD</button>
      <button class="button left" onclick="moveLeft()">LEFT</button>
      <button class="button button2 stop" onclick="stopRobot()">STOP</button>
      <button class="button right" onclick="moveRight()">RIGHT</button>
      <button class="button reverse" onclick="moveReverse()">REVERSE</button>
      <button class="button button3 uv" id="uvButton" onclick="toggleUVLight()">LIGHT</button>
    </div>
  </body>
</html>)rawliteral";
 server.send(200, "text/html", html);
}

void handleForward() {
  Serial.println("Forward");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  server.send(200);
}

void handleLeft() {
  Serial.println("Left");
  digitalWrite(motor1Pin1, LOW); 
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  server.send(200);
}

void handleStop() {
  Serial.println("Stop");
  digitalWrite(motor1Pin1, LOW); 
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);   
  server.send(200);
}

void handleRight() {
  Serial.println("Right");
  digitalWrite(motor1Pin1, HIGH); 
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);    
  server.send(200);
}

void handleReverse() {
  Serial.println("Reverse");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);         
  server.send(200);
}

void handleUVOn() {
  Serial.println("UV Light ON");
  digitalWrite(RELAY_PIN, HIGH);
  server.send(200);
}

void handleUVOff() {
  Serial.println("UV Light OFF");
  digitalWrite(RELAY_PIN, LOW);
  server.send(200);
}

void setup() {
  Serial.begin(500000);

  // Set the Motor pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(MQ135_PIN, INPUT);
  digitalWrite(RELAY_PIN, HIGH); // Ensure the UV light is initially off
  // Set motor pins to LOW to ensure motors are off by default
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  Serial.begin(500000);

   

   // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

   // Define routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/left", handleLeft);
  server.on("/stop", handleStop);
  server.on("/right", handleRight);
  server.on("/reverse", handleReverse);
  server.on("/uv/on", handleUVOn);
  server.on("/uv/off", handleUVOff);

  server.on("/uv", []() {
    if (server.hasArg("state")) {
      String state = server.arg("state");
      if (state == "on") {
        handleUVOn();
      } else if (state == "off") {
        handleUVOff();
      }
    }
  });

  // Start the server
  server.begin();
  // Start Serial communication for debugging
  Serial.begin(500000);

  // Initialize I2C with defined SDA and SCL pins for ESP32
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Initialize LCD
  lcd.init();          // Initialize the LCD
  lcd.backlight();     // Turn on the backlight
  
  // Initialize DHT sensor
  dht.begin();

  // Set pin modes
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(MQ135_PIN, INPUT);  

  // Initial display message on LCD
  lcd.setCursor(0, 0);
  lcd.print("UV Disinfection");
  lcd.setCursor(0, 1);
  lcd.print("Robot Turned ON");
  delay(2000);  // Display for 5 seconds
  lcd.clear();

  // Relay ON by default
  digitalWrite(RELAY_PIN, LOW);  // Turn ON relay initially
  dht.begin();
  Serial.begin(500000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  // Read temperature and humidity from DHT22
  server.handleClient();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read air quality from MQ135 sensor (Analog read)
  float airQuality = digitalRead(MQ135_PIN);  // Get the actual air quality value

  // Display temperature and humidity on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  delay(1000);  // Update every 1 second

  // Display air quality value on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AQI: ");
  lcd.print(airQuality);
  delay(2000);  // Update every 2 seconds

  // Check air quality and trigger buzzer if it's above threshold
  if (temperature > 40) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature High");
  }

  if (airQuality > 150) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Poor AQI");

    // Buzzer beeps 3 times
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(250);
      digitalWrite(BUZZER_PIN, LOW);
      delay(250);
    }

  }
  // Ultrasonic sensor to detect motion
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.0343) / 2; // Calculate distance in cm
  // Check if motion is detected
  // Check if motion/object is detected within a certain range
  if (distance > 0 && distance < 30) {  
    // Motion detected
    digitalWrite(RED_PIN, HIGH);     // Turn on Red LED
    digitalWrite(GREEN_PIN, LOW);    // Turn off Green LED
    digitalWrite(BUZZER_PIN, HIGH);  // Activate buzzer
    digitalWrite(RELAY_PIN, HIGH);   // Turn OFF relay (disabling disinfection)

    // Display motion alert on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Object Detected");
    
    delay(10);  // Wait for a second
  } else {
    // No motion detected
    digitalWrite(RED_PIN, LOW);     // Turn off Red LED
    digitalWrite(GREEN_PIN, HIGH);  // Turn on Green LED
    digitalWrite(BUZZER_PIN, LOW);  // Deactivate buzzer
  }

  delay(10);  // Small delay before the next loop iteration
  
  //temperature and humidity measured should be stored in variables so the user
  //can use it later in the database
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    //since we want the data to be updated every second
    sendDataPrevMillis = millis();
    // Enter Temperature in to the DHT_11 Table
    if (Firebase.RTDB.setInt(&fbdo, "DHT_11/Temperature", temperature)){
      // This command will be executed even if you dont serial print but we will make sure its working
      Serial.printf("Temperature: %f\n", temperature); // Use %f for float
    }
    else {
      Serial.println("Failed to Read from the Sensor");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    // Enter Humidity in to the DHT_11 Table
    if (Firebase.RTDB.setFloat(&fbdo, "DHT_11/Humidity", humidity)){
       Serial.printf("Humidity: %f\n", humidity);
    }
    else {
      Serial.println("Failed to Read from the Sensor");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if (Firebase.RTDB.setFloat(&fbdo, "DHT_11/AQI", airQuality)){
       Serial.printf("AQI: %f\n", airQuality);
    }
    else {
      Serial.println("Failed to Read from the Sensor");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}

