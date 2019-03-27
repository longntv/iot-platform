#include <thread>				// std::thread, std::this_thread::yield
#include <cstring>
#include <unistd.h>

#include "MqttClient.h"


static	void	mqtt_thread(void);


using namespace std;

bool connect = false;
int main(int argc, char *argv[])
{
	thread thread_mqtt_client(mqtt_thread);

	while( !CMqttClient::getInstance()->chkReady() ) {
		printf("wait for connection \n");
		usleep(500);
	};

	CMqttClient::getInstance()->send_message("test/test", strlen(buf), buf);

	thread_mqtt_client.join();
	return 0;
}


static void mqtt_thread()
{
	CMqttClient *mqtt_client = CMqttClient::getInstance();
	int rc;

	mosqpp::lib_init();

	//mqtt_client = new CMqttClient("mqtt_client", "192.168.1.8", 1883);
	
	while(1){
		rc = mqtt_client->loop();
		if(rc){
			mqtt_client->reconnect();
		}
	}

	mosqpp::lib_cleanup();
}
