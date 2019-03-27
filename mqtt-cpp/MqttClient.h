#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <mosquittopp.h>

class CMqttClient : public mosqpp::mosquittopp
{
	private: 
		static CMqttClient* instance;
		static bool isReady;
	public:
		CMqttClient();
		~CMqttClient();
		static bool chkReady() {return isReady; };
		static CMqttClient* getInstance();
		void on_connect(int rc);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);
		void send_message(const char* topic, int payloadlen, const void* payload);
};

#endif
