# MQTT Client using mosquitto-client in C++
# Setup mosquitto in Raspberry Pi
- Step 1 — Installing Mosquitto using apt install:

`sudo apt update`
`sudo apt install mosquitto mosquitto-clients`

- Step 2 — Configuring MQTT Passwords

`sudo mosquitto_passwd -c /etc/mosquitto/passwd test`

This command will prompt you to enter a password for the specified username, and place the results in /etc/mosquitto/passwd

We'll open up a new configuration file for Mosquitto and tell it to use this password file to require logins for all connections:
sudo nano /etc/mosquitto/conf.d/default.conf

This should open an empty file. Paste in the following:

`allow_anonymous false`
`password_file /etc/mosquitto/passwd`

Be sure to leave a trailing newline at the end of the file.

- Step 3 - Testing

Subscribe to the 'test' topic, using the username and password this time:

`mosquitto_sub -h localhost -t test -u "test" -P "password"`

Now publish a message with your other terminal, again using the username and password:

`mosquitto_pub -h localhost -t "test" -m "hello world" -u "test" -P "password"`


# Build mosquitto source in Raspberry Pi
- Step 1 Download mosquitto project at [here](https://github.com/eclipse/mosquitto)

`mkdir MQTT`

`cd MQTT`

`git clone https://github.com/eclipse/mosquitto.git`

- Step 2 Installing mosquitto using cmake ( Install cmake tool if required)

`sudo apt install cmake`

`cd mosquitto`

`mkdir build`

`cd build`

`cmake -DWITH_STATIC_LIBRARIES=ON ../`

`make`

Besure that 2 shared libraries are made:
libmosquitto.so.1
libmosquittopp.so.1

- Step 3 Configuring mosquitto shared library which loading when run program

`sudo cp /lib/libmosquitto.so.1 /usr/local/lib/`

`sudo cp /lib/cpp/libmosquittopp.so.1 /usr/local/lib/`

Then run:

`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib`

# Create example application based on example of mosquitto
`It is a client that subscribes to the topic temperature/celsius which should have temperature data in text form being published to it. It reads this data as a Celsius temperature, converts to Farenheit and republishes on temperature/farenheit.`

- Step 1 Copy lib folder after build source code
- Step 2 run program
Subscribe topic `temperature/farenheit` in termial

`mosquitto_sub -h 192.168.1.16 -t "temperature/farenheit" -u "test" -P "test"`

Run program `.\mqtt-client`

Publish message in other teminal

`mosquitto_pub -m "temperature/celsius" -t '30' -u test -P test`

Check received message show on subscribe Termial





