UDP FEH Course communication would look something like this:

UDP server periodically broadcasts 4 packets, 1 for each course, on 4 different ports. These packets contain information regarding the E-Stop, as well as position/heading data and whatever else we want.

Each Arduino has an ESP that is running custom firmware, written with the Arduino Core, to listen on the right port. When it receives a packet, it will check it for an E-Stop flag. If it's true, it will use one of it's IO pins to trigger a hardware interrupt on the Mega, stopping it's program without that program needing to know what's going on. It will also store this packet regardless of the flag. Whenever the Arduino wants heading information, it will send a request via serial to the ESP to retrieve the most recently stored packet. Regulating the pace of requests will be handled on the Arduino. 

Although the serial communication to set this up each run might be a hassle to work the kinks out of, this eliminates the need to safety check any of the Arduino libraries for things that would mess up an on-chip looping solution. By using UDP Broadcasting on a private network, both the server and the ESP can run much less code and not risk sacrificing the speed of either system.

The cost of this solution is losing out on either a PWM pin or a Serial port, as well as the time/labor cost of writing the ESP-side firmware.

UDP Broadcasting over a network is not supported in IPv6, so you must multicast to all clients on a network. Since there is no control on which IP address is assigned to which robot on each course, this approach is preferable to sending packets to individual IPs. In this scheme, the port will be the distinguishing factor of each packet for each course, and the port will be opened during course selection on the robot.

[Relevant Stack Overflow Link](https://stackoverflow.com/questions/64066634/sending-broadcast-in-python)

Python seems like the most natural choice for setting thisup, since it's fast and the sockets API seems simple.