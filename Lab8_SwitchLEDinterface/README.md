# Lab8_SwitchLEDinterface
[E-book link](http://users.ece.utexas.edu/~valvano/Volume1/E-Book/C8_SwitchLED.htm)
[YouTube Video by Professor Valvano Describing Lab 8] (https://www.youtube.com/watch?v=bS73Z-WGZz8)
[How to Use the Logic Analyzer] (https://www.youtube.com/watch?v=mtsOrzoECbk)
## Purpose
Build circuits on the breadboard and connect them to the LaunchPad. Learn how to interface a switch <br/> 
and an LED. Perform explicit measurements on the circuits in order to verify they are operational and to <br/> 
improve my understanding of how they work.<br/>

## Equipment
* Tiva C Series TM4C123G Lauchpad
* Switch
* 10kΩ resistor
* LED
* 470Ω resistor 

## Skills
*  Understanding basic circuit elements like source, ground, switch, LED and resistors.
*  Application of Ohm’s Law
*  Analog circuit design and construction
*  Interfacing circuit elements to a microcontroller
*  Programming simple logic. 

## What It Does
Build a switch interface that implements positive logic, and build an LED interface that implements positive logic. <br/>  
Attach this switch and LED to protoboard (the white piece with all the holes), and interface them to the TM4C123. Overall <br/> 
functionality of this system is similar to Lab 6, with five changes:<br/>
1. The pin to which we connect the switch is moved to PE0
2. Remove the PUR initialization because pull up is no longer needed
3. The pin to which we connect the LED is moved to PE1
4. The switch is changed from negative to positive logic
5. Decrease the delay so it flashes about 5 Hz (i.e. 5 cycles per second)

If the switch is pressed we turn on the LED for 100 ms, turn off the LED for 100 ms, and repeat.<br/>

## Overall functionality of this system is described in the following rules:<br/>

1. Make PE1 an output and make PE0 an input. 
2. The system starts with the LED on (make PE1 =1). 
3. Wait about 100 ms
4. If the switch is pressed (PE0 is 1), then toggle the LED once, else turn the LED on. 
5. Steps 3 and 4 are repeated over and over.

## Testing

Test the program in simulation mode on Keil. Use the built-in logic analyzer. <br/>