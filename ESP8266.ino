#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Anya Geraldine";
const char* password = "langsungmasukkok";
const char* mqtt_server = "rmq2.pptik.id"; 
const char* mqtt_user = "TMDG2022";
const char* mqtt_pass= "TMDG2022";

const int mq2pin = A0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  // Connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  Serial.println("In reconnect...");
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Arduino_Gas", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  char msg[8];
  if (!client.connected()) {
    reconnect();
  }

  sprintf(msg,"%i",analogRead(mq2pin));
  client.publish("mq2_mqtt", msg);
  Serial.print("MQ2 gas value:");
  Serial.println(msg);

  delay(5000);
}
