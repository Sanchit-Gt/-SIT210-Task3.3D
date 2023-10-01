// Including the libraries
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>

char WIFI_SSID[] = "Sanchit";
char WIFI_PASSWORD[] = "12345678";

int LIGHT_PIN_NO = 2;

WiFiClient wifiClient;

MqttClient mqttClient(wifiClient);

// MQTT credentials for communication
const char BROKER[] = "mqtt-dashboard.com";
int PORT_NO = 1883;
const char TOPIC[] = "Distinction_3.3";

void setup() {
  // Serial communication setup at 9600 baud rate for communication between Arduino and the laptop
  Serial.begin(9600);
  pinMode(LIGHT_PIN_NO, OUTPUT);
  while (!Serial) {
    ; // Wait for serial port to connect
  }

  Serial.print("Trying to connect to WiFi network: ");
  Serial.println(WIFI_SSID);

  while (WiFi.begin(WIFI_SSID, WIFI_PASSWORD) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }

  Serial.println("Connected to WiFi successfully");
  Serial.println();

  Serial.print("Trying to connect to MQTT broker: ");
  Serial.println(BROKER);

  if (!mqttClient.connect(BROKER, PORT_NO)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("Connected to the MQTT broker!");
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(TOPIC);
  Serial.println();

  mqttClient.subscribe(TOPIC);

  Serial.print("Topic: ");
  Serial.println(TOPIC);
  Serial.println();
}

void loop() {
  int messageSize = mqttClient.parseMessage();
  if (messageSize) {

    Serial.print("Received a message with topic '");
    Serial.print(mqttClient.messageTopic());
    Serial.print("', length ");
    Serial.print(messageSize);
    Serial.println(" bytes:");

    while (mqttClient.available()) {
      Serial.print((char)mqttClient.read());
    }
    Serial.println();

    digitalWrite(LIGHT_PIN_NO, HIGH);
    delay(200);
    digitalWrite(LIGHT_PIN_NO, LOW);
    delay(200);
    digitalWrite(LIGHT_PIN_NO, HIGH);
    delay(200);
    digitalWrite(LIGHT_PIN_NO, LOW);
    delay(200);
    digitalWrite(LIGHT_PIN_NO, HIGH);
    delay(200);
    digitalWrite(LIGHT_PIN_NO, LOW);
    delay(200);

    Serial.println();
  }
}