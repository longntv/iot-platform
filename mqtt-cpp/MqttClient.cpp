#include <cstdio>
#include <cstring>

#include "MqttClient.h"
#include <mosquittopp.h>

#define MQTT_ID				"mqtt_client"
#define MQTT_HOST			"192.168.1.8"
#define MQTT_PORT			1883

CMqttClient* CMqttClient::instance = 0;
bool CMqttClient::isReady = false;

CMqttClient* CMqttClient::getInstance()
{
	if (instance == 0)
	{
		instance = new CMqttClient();
	}
	return instance;
}
CMqttClient::CMqttClient() : mosquittopp(MQTT_ID)
{
	int keepalive = 60;

	/* Connect immediately. This could also be done by calling
	 * CMqttClient->connect(). */
	mosquittopp::username_pw_set("test", "test");
	//connect(host, port, keepalive);
	connect( MQTT_HOST, MQTT_PORT, keepalive);
};

CMqttClient::~CMqttClient()
{
}

void CMqttClient::on_connect(int rc)
{
	printf("Connected with code %d.\n", rc);
	if(rc == 0){
		/* Only attempt to subscribe on a successful connect. */
		subscribe(NULL, "temperature/celsius");
	}
}

void CMqttClient::on_message(const struct mosquitto_message *message)
{
	double temp_celsius, temp_farenheit;
	char buf[51];

	if(!strcmp(message->topic, "temperature/celsius")){
		printf("Received message succeeded.\n");
		memset(buf, 0, 51*sizeof(char));
		/* Copy N-1 bytes to ensure always 0 terminated. */
		memcpy(buf, message->payload, 50*sizeof(char));
		temp_celsius = atof(buf);
		temp_farenheit = temp_celsius*9.0/5.0 + 32.0;
		snprintf(buf, 50, "%f", temp_farenheit);
		//publish(NULL, "temperature/farenheit", strlen(buf), buf);
		send_message("temperature/farenheit", strlen(buf), buf);
	}
}

void CMqttClient::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
	printf("Subscription succeeded.\n");
	isReady = true;
}

void CMqttClient::send_message(const char* topic, int payloadlen, const void* payload)
{
	publish(NULL, "temperature/farenheit", payloadlen, payload);
}
