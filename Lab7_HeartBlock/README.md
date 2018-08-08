# Lab7_HeartBlock
[E-book link](http://users.ece.utexas.edu/~valvano/Volume1/E-Book/C7_DesignDevelopment.htm)
[YouTube Video by Professor Valvano Describing Heart Blocks] (https://www.youtube.com/watch?time_continue=66&v=zYbQNvtkjJo)
[YouTube Video of Professor Valvano Describing Lab 7 Requirements] (https://www.youtube.com/watch?v=QaFlnBglmbA)
[Heart Block Definition] (https://www.hrsonline.org/Patient-Resources/Heart-Diseases-Disorders/Heart-Block)

## Purpose
The purpose of this lab is to construct a simple pacemaker to treat patients that have complete heart block.<br/>
The goal is to recreate the normal 1) atrial contraction, 2) pause, 3) ventricular contraction sequence <br/>
that occurs in a normal, single cardiac cycle. In heart block, the electrical signals that normally pass <br/>
from the atria to the ventricles are delayed, partially blocked, or completely blocked, causing the atria and <br/>
ventricles to beat out of synch. <br>/

Skills gained in this lab include the following:
* Read from a switch, make decisions, and output to an LED. 
* Learn and understand the steps required to initialize parallel ports. 
* Write subroutines that wait for the switch to be pressed, wait for the switch to be released.
* Create an output pulse of fixed duration.
* Learn how to use the logic analyzer and oscilloscope to measure time delay. 
* Use the C programming language to learn masking, toggling, if-then, subroutines, and looping.

## What It Does
I will create seven subroutines.There is one input called the <br/> 
Atrial sensor (AS), and two outputs Ready and Ventricular trigger (VT). AS input is connected <br/>
to PF4. In a real pacemaker, electrodes (wires) are attached to the heart and electronics are <br/>
used to sense the activity of the heart. In this lab, a switch will be used to emulate the <br/>
operation of the atrial sensor. When the switch SW1 is pressed (AS=0) it means the atria has <br/> 
begun to contract. When the switch SW1 is released, it means the atria have completed contraction. <br/> 
The Ready output is connected to PF3. The LED will be green when Ready is high. The Ready signal <br/>
is used for debugging, and not part of an actual pacemaker. In a real pacemaker, electrodes <br/>
(wires) are attached to the heart, and electrical pulses are generated that stimulate the heart, <br/> 
causing it to beat. In this lab, the VT output is connected to PF1, such that the LED will be red <br/>
when VT is high. A 250 ms pulse will cause the ventricules to contract. <br/>

## Overall functionality of this system is described in the following rules:<br/>

1. Make the Ready signal go high
2. Wait for AS to be 0, switch to be pressed
3. Make the Ready signal go low
4. Wait 10ms
5. Wait for AS to be 1, switch to be released
6. Wait 250ms
7. Make the VT signal go high
8. Wait 250ms
9. Make the VT signal go low

## Testing

Test the program in simulation mode. Use the built-in logic analyzer. <br/>