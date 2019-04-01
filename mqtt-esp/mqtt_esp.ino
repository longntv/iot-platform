// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       mqtt_esp.ino
    Created:	3/31/2019 9:53:16 AM
    Author:     Shinryu
*/

// Define User Types below here or use a .h file
//
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Define Function Prototypes that use User Types below here or use a .h file
//
const char* ssid = "your-ssid";
const char* password = "password";
const char* mqtt_server = "192.168.1.7"; // Your mosquitto IP Address

const char* outTopic = "senddata/data";
const char* inTopic = "seting/data";

// Define varables below here
//
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


// Define Functions below here or use other .ino or cpp files
//
void setup_wifi() {

	delay(10);
	// We start by connecting to a WiFi network
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	randomSeed(micros());

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();

	// TODO: Process received data
}

void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Create a random client ID
		String clientId = "MqttESP-";
		clientId += String(random(0xffff), HEX);
		// Attempt to connect with username and password
		if (client.connect(clientId.c_str(), "test", "test")) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			client.publish(outTopic, "hello world");
			// ... and resubscribe
			client.subscribe(inTopic);
		}
		else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}
// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(115200);
	setup_wifi();
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);
}

// Add the main program code into the continuous loop() function
void loop()
{
	if (!client.connected()) {
		reconnect();
	}
	client.loop();

	long now = millis();
	// Publish data every 2s
	if (now - lastMsg > 2000) {
		lastMsg = now;
		++value;
		snprintf(msg, 50, "hello world #%ld", value);
		Serial.print("Publish message: ");
		Serial.println(msg);
		client.publish(outTopic, msg);
	}
}
