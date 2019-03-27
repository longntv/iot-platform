# MQTT Client using mosquitto-client in C++
# Setup mosquitto in Raspberry Pi
Step 1 — Installing Mosquitto using apt install:

`sudo apt update`
`sudo apt install mosquitto mosquitto-clients`

Step 2 — Configuring MQTT Passwords

'sudo mosquitto_passwd -c /etc/mosquitto/passwd test'

This command will prompt you to enter a password for the specified username, and place the results in /etc/mosquitto/passwd

We'll open up a new configuration file for Mosquitto and tell it to use this password file to require logins for all connections:
sudo nano /etc/mosquitto/conf.d/default.conf

This should open an empty file. Paste in the following:

allow_anonymous false
password_file /etc/mosquitto/passwd

Be sure to leave a trailing newline at the end of the file.

Step 3 - Testing

Subscribe to the 'test' topic, using the username and password this time:

mosquitto_sub -h localhost -t test -u "test" -P "password"

Now publish a message with your other terminal, again using the username and password:

mosquitto_pub -h localhost -t "test" -m "hello world" -u "test" -P "password"


