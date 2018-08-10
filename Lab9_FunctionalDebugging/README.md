# Lab9_FunctionalDebugging
[E-book link](http://users.ece.utexas.edu/~valvano/Volume1/E-Book/C9_ArrayFunctionalDebugging.htm) <br/> 
[YouTube Video by Professor Valvano Describing Lab 8] (https://www.youtube.com/watch?v=74hB62yAIDU) <br/> 

## Purpose
Learn about time delays, arrays and functional debugging. The data collected will be physical proof that <br/> 
the system operates within specifications.<br/>

## Equipment
* Tiva C Series TM4C123G Lauchpad

## What It Does
First, make the LED flash at 10 Hz. In other words, invert the output every 0.05 seconds. <br/>
Second, make the LED flash if either switch SW1 or SW2 are pressed (this means either PF4 or PF0 is 0).  <br/>
This means toggle if just SW1 is pressed, just SW2 is pressed or both switches are pressed.<br/>
Third, record PortF bits 4,1,0 every time the input changes or the output changes. <br/>
For example, if the system detects a change in either PF4 or PF0 input, record PortF bits 4,1,0. <br/>
If the system causes a change in PF1, record PortF bits 4,1,0. In order for the grading engine to see/grade the data, <br/>
leave the debugging array defined exactly as it is in the starter project.<br/>

## Overall functionality of this system is described in the following rules:<br/>

unsigned long Data[50];

System will be graded on its ability to satisfy the following requirements:

1. If both PF4 and PF0 switch are not pressed, the PF1 output should be low.
2. If either PF4 or PF0 switches is pressed, the output is inverted every 50 ms, making it oscillate at 10 Hz (±10%).
3. Information collected in the Data array matches the I/O on PortF.
4. 50 data points are collected only on a change in input or a change in output. (i.e., no adjacent elements in the array are equal).

## Testing

Test the program in simulation mode on Keil. Use the built-in logic analyzer. <br/>