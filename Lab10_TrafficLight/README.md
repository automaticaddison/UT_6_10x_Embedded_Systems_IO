# Lab10_TrafficLight
[E-book link](http://users.ece.utexas.edu/~valvano/Volume1/E-Book/C10_FiniteStateMachines.htm) <br/> 
[YouTube Video describing finite state machine for a traffic light] (https://www.youtube.com/watch?time_continue=894&v=kgABPjf9qLI) <br/> 
[Professor explaining the final solution] (https://www.youtube.com/watch?time_continue=1&v=qNl7vayZEz0)

## Purpose
This lab has these major objectives:  <br/> 
1. the understanding and implementing of indexed data structures
2. learning how to create a segmented software system; and 
3. the study of real-time synchronization by designing a finite state machine controller
Software skills you will learn include advanced indexed addressing, linked data structures, creating  <br/> 
fixed-time delays using the SysTick timer, and debugging real-time systems.  <br/> 

## Equipment
* Tiva C Series TM4C123G Lauchpad
* Three switches
* Three 10kΩ resistors
* Six LEDs
* Six 470Ω resistors

## What It Does
Consider a 4-corner intersection. There are two one-way streets are labeled South (cars travel South) and West <br/> 
(cars travel West). There are three inputs to your LaunchPad, two are car sensors, and one is a pedestrian sensor.  <br/> 
The South car sensor will be true (3.3V) if one or more cars are near the intersection on the South road. Similarly,  <br/> 
the West car sensor will be true (3.3V) if one or more cars are near the intersection on the West road. The Walk sensor <br/> 
will be true (3.3V) if a pedestrian is present and he or she wishes to cross in any direction. This walk sensor is different  <br/> 
from a walk button on most real intersections. This means when you are testing the system, you must push and hold the walk  <br/> 
sensor until the FSM recognizes the presence of the pedestrian. Similarly, you will have to push and hold the car sensor until  <br/> 
the FSM recognizes the presence of the car. In this simple system, if the walk sensor is +3.3V, there is pedestrian to service,  <br/> 
and if the walk sensor is 0V, there are no people who wish to walk. The walk sensor and walk light will service pedestrians who  <br/> 
wish to cross in any direction. This means the roads must both be red before the walk light is activated. In a similar fashion,  <br/> 
when a car sensor is 0V, it means no cars are waiting to enter the intersection. The don't walk light should be on while cars  <br/> 
have a green or yellow light.  <br/> 

Interface 6 LEDs that represent the two Red-Yellow-Green traffic lights, and you will use the PF3 green LED  <br/> 
for the “walk” light and the PF1 red LED for the “don’t walk” light. When the “walk” condition is signified, pedestrians  <br/> 
are allowed to cross in any direction. When the “don’t walk” light flashes (and the two traffic signals are red), pedestrians  <br/> 
should hurry up and finish crossing. When the “don’t walk” condition is on steady, pedestrians should not enter the intersection.  <br/> 

## Overall functionality of this system is described in the following rules:<br/>

0. At all times, there should be exactly one of the {red, yellow, green} traffic lights active on the south road. At all times, there should be exactly one of the {red, yellow, green} traffic lights active on the west road. To switch a light from green to red it must sequence green, yellow then red . The grader checks for the proper sequence of output patterns but does not measure the time the FSM spends in each state. The “walk” and “don’t walk” lights should never both be on at the same time.
1. Do not allow cars to crash into each other. This means there can never be a green or yellow on one road at the same time as a green or yellow on the other road. Engineers do not want people to get hurt.
2. Do not allow pedestrians to walk while any cars are allowed to go. This means there can never be a green or yellow on either road at the same time as a “walk” light. Furthermore, there can never be a green or yellow on either road at the same time as the “don’t walk” light is flashing. If a green light is active on one of the roads, the “don’t walk” should be solid red. Engineers do not want people to get hurt.
3. If just the south sensor is active (no walk and no west sensor), the lights should adjust so the south has a green light within 5 seconds (I know this value is unrealistically short, but it makes the grading faster). The south light should stay green for as long as just the south sensor is active.
4. If just the west sensor is active (no walk and no south sensor), the lights should adjust so the west has a green light within 5 seconds. The west light should stay green for as long as just the west sensor is active.
5. If just the walk sensor is active (no west and no south sensor), the lights should adjust so the “walk” light is green within 5 seconds. The “walk” light should stay green for as long as just the walk sensor is active.
6. If all three sensors are active, the lights should go into a circular pattern in any order with the west light green, the south light green, and the “walk” light is green. Of course, the road lights must sequence green-yellow-red each time.

## Testing

Test the program in simulation mode on Keil. Use the built-in logic analyzer. <br/>