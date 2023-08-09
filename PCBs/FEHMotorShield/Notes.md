[TO-DO] Proofread and edit this file.

### Motor Control Shield Notes:
The Motor Control Shield is a shield for the Arduino Mega that can drive up to 4 DC motors and 4 servo motors with a total combined current draw of **4A or less**. This board is designed to be used with an 11.1v, 2600mAh Li-ion battery pack, and is meant to provide motor control functionality identitcal to that of the FEH Proteus microcontroller.

This controller uses pins 3-6, 7-10, and 26-35. 

The core of this shield is the TB6612FNG Breakout Board, which is a dual H-bridge motor controller. There are two breakout boards on the shield, each of which can drive 2 DC Motors with a maximum current draw of **1.7A**, not accounting for total current draw. The H-bridge driver allows a motor to drive forwards, backwards, or brake without the need for a negative power supply. Check out [this link for a more detailed explaination of H-bridges](https://archive.ph/20130112153214/http://www.dprg.org/tutorials/1998-04a/). The breakout boards also include a PWM input to control motor speed through a power FET.

To make controlling these drivers easier, Sparkfun wrote an Arduino library included in this project. 

On this board, the H-drivers are driven by pins 26-35: 2 pins per motor and two additional standby pins, which control if current is drawn by each breakout board.

_[TO-DO] Configure default Arduino project to configure motor objects with correct pins when user specifies the use of motor shield._

Servos are controlled by pins 7-10 and the standard Arduino _Servo.h_ library. Power is provided to the servos through the buck converter power supply.

The buck converter used on this board allows for far more current to go to the motors than the Arduino can safely supply, while also adding a level of isolation from the noise of the motors. The circuitry surrounding the converter is comprised of a voltage divider supplying the feedback pin, an inductor to limit noise, a bulk capacitor on the input to reduce voltage sags, and decoupling capacitors on both the inputs and outputs of the converter.

The Arduino's current limit is 800mA, coming from the specification of the 5v regulator used to supply the board.

#### Component List (_excluding passive and discrete components_):
* [TB6612FNG Breakout Board](https://www.sparkfun.com/products/14450)
* [TPS564242 DC-DC Stepdown Converter](https://www.ti.com/product/TPS564242)