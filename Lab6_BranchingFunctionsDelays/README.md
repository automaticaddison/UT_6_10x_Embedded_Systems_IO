# Lab6_BranchingFunctionsDelays
[E-book link](http://users.ece.utexas.edu/~valvano/Volume1/E-Book/C6_MicrocontrollerPorts.htm)

## Purpose
The purpose of this lab is the following<br/>
* To estimate how long it takes to run software, and use this estimation to create a time delay function. 
* To learn how to use the logic analyzer and oscilloscope to measure time delay. 
* To use the C programming language to learn masking, toggling, if-then, subroutines, and looping.

## What It Does
The system has one input switch and one output LED. <br/>
The schematic enclosed in this folder shows the system when simulated as the switch is touched. <br/>
A negative logic switch means the PF4 signal will be 1 (high, 3.3V) if the switch is not pressed, <br/>
and the PF4 signal will be 0 (low, +0V) if the switch is pressed. <br/>
A positive logic blue LED interface means if the software outputs a 1 to PF2 (high, +3.3V) the <br/>
LED will turn ON, and if the software outputs a 0 to PF2 (low, 0V) the blue LED will be OFF. <br/>

## Overall functionality of this system is described in the following rules:<br/>

When SW1 is not pressed, the blue LED must be on. When SW1 is pressed the blue LED should turn <br/>
on for 100ms and off for 100ms. <br/>

1. Make PF2 an output and make PF4 an input (enable PUR for PF4). 
2. The system starts with the LED ON (make PF2 =1). 
3. Delay for about 100 ms
4. If the switch is pressed (PF4 is 0), then toggle the LED once, else turn the LED ON. 
5. Repeat steps 3 and 4 over and over.

## Testing

Test the program in simulation mode. Use the built-in logic analyzer to verify the LED is toggling at <br/> 
the rate at which it was designed. On the real board, use a real oscilloscope. To measure execution time, <br/>
I cause rising and falling edges on a digital output pin that occur at known places within the software execution.</br>
Use the logic analyzer/oscilloscope to measure the elapsed time between the rising and falling edges. 