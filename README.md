## tOSU EED Microcontroller Project
### Hardware
#### Arduino Mega
Per the [Arduino Website](https://store-usa.arduino.cc/products/arduino-mega-2560-rev3?selectedStore=us):

> The Arduino Mega 2560 is a microcontroller board based on the ATmega2560. It has 54 digital input/output pins (of which 15 can be used as PWM outputs), 16 analog inputs, 4 UARTs (hardware serial ports), a 16 MHz crystal oscillator, a USB connection, a power jack, an ICSP header, and a reset button. It contains everything needed to support the microcontroller; simply connect it to a computer with a USB cable or power it with a AC-to-DC adapter or battery to get started. The Mega 2560 board is compatible with most shields designed for the Uno and the former boards Duemilanove or Diecimila.

This board is already used inthe FE curriculum, and provides several benefits that the Proteus does not: 
* An existing software ecosystem 
* decreased per-unit cost
* a large list of known compatible components
* the ability to use shields, which are either custom or pre-built circuit boards that interface with the pins on top of the Arduino to add extra functionality, such as motor control, environmental sensors, or wifi connectivity

#### Batteries
Although there is not a complete consensus on the choice of battery pack, the shields in this porject were designed around the [Tenergy 31013-02](https://power.tenergy.com/at-tenergy-li-ion-11-1v-2600mah-rechargeable-battery-pack-w-pcb-3s1p-28-86wh-5a-rate/), a 11.1v 2600mAh Li-Ion battery pack with built in protection against over-charge, over-discharge, and over-current. This is the battery currently ued in the FEH Proteus microcontrollers. The design requirements for any other batteries are built in over-discharge and over-current protections and a lower voltage limit of at least 9v.

#### Motor Shield
The motor shield connects the Arduino's PWM pins to 4 servo ports and 2 [TB6612FNG Dual H-bridge breakout boards](https://www.sparkfun.com/products/14450). It also pulls a second 5v power rail from the battery through a step-down dc-dc converter to bypass the current limits of the Arduino's 5v pins. The decision to limit the motor voltage to 5v was made to ensure that the shield would be compatible with all motors and servos used across the FE and FEH curriculums. The absolute limit on current is **5A**, and is controlled by a current limiters that is built into the step-down converter.

#### Wifi/LCD/IO Shield
This shield adds WiFi functionality, an LCD screen, and a set of buttons to the Arduino. WiFi connectivity is achieved through a [ESP-01 Module](https://www.digikey.com/en/products/detail/seeed-technology-co.,-ltd/317060016/5774757) connected via Serial port 1 to the Arduino. This chip works independently of the Arduino, and has an TCP/IP stack built in, allowing the Arduino's processor to focus on the information being sent and received via WiFi. The LCD screen is a 16x2 [RT162](https://newhavendisplay.com/content/specs/NHD-0216K1Z-NSW-BBW-L.pdf) (This is not the exact display ordered, but the datasheet explains the use of the component well) character-based backlit LCD, which is compatible with the HD44780 Driver and the official Arduino LCD library. The buttons are simple push-buttons wired with pulldown resistors. They allow for a user to interact with a program in a similar fashion to the touchscreens used on the Proteus.

### Software
#### Arduino Dev Stack
The Arduino ecosystem is effectively an abstraction layer for embedded C++. Instead of directly accessing the C/C++ libraries provided to developers by chip manufacturers, Arduino places a core inbetween the user and the MCU. This core specifies an interface for both 3rd party libraries and users, and allows the same program to be compiled for a variety of different chips by using the different cores for each chip. 

In addition to this core, there is also a huge repository of existing libraries to achieve different functions. Arduino officially maintains a few dozen libraries for basic functions such as IO, Ethernet connectivity, UART communication, etc., which are then built on by other developers. Most Arduino-compatible components have existing Arduino libraries maintained by either the company themselves or product users. Although the quality of these libraries can vary, they're certainly still useable for this project. All of these libraries are also open source, which will allow us to modify them if needed to work with our set-up.

Arduino also provides a set of tools to work with this software. Specifically, they package the compiling toolchain as both and IDE and a command-line utility. The command-line utility is newer, and allows for Arduino to be built in to other editors, such as VSCode. In fact, there is currently an Arduino extension for VSCode, although it is currently still in beta.

#### Current 3rd-Party Libraries
As of this point the following libraries are used:
* HttpClient: Automates HTTP requests using the Arduino standard library Client class. Currently only used as an example of how the boards could communicate with the FEH Robot course.
* SparkFun ESP8266 AT Library: Abstracts the AT commands used to communicate with the ESP01 into a set of functions that resemble those found in the standard library, while also adding error protection. These functions include test commands, WiFi connection utilities, and TCP/UDP connections.   
This library also adds the ability to interface with the ESP01 as a _Client_ or _Server_ from the Arduino standard library.
* Sparkfun TB6612FNG library: Adds easier to understand functions for motor control using the TB6612 H-Bridge chip.

#### FEH Course Communication
With this configuration, the only way for the Arduino to wirelessly communicate is through WiFi. This approach is different from the ZigBee radio system used on the Proteus, but it is certainly not difficult to achieve. ESPCourseDemo is the primary example of this, and works by setting up both a WiFi access point and a small HTTP server on a computer, which in this case was a Raspberry Pi 2B. Once set up, the 3rd party libraries can be used to easily fetch content over HTTP, such as a file containing text data.