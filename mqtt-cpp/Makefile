CFLAGS=-Wall -ggdb -I lib -Ilib/cpp
LDFLAGS=-Llib lib/cpp/libmosquittopp.so.1 lib/libmosquitto.so.1
LDLIBS += -pthread
.PHONY: all clean

all : mqtt_client

mqtt_client : main.o mqtt_client.o
	${CXX} $^ -o $@ ${LDFLAGS} $(LDLIBS)

main.o : main.cpp
	${CXX} -c $^ -o $@ ${CFLAGS} 

mqtt_client.o : MqttClient.cpp
	${CXX} -c $^ -o $@ ${CFLAGS}

clean : 
	-rm -f *.o mqtt_client
