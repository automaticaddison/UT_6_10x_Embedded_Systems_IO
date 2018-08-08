// BranchingFunctionsDelays.c Lab 6
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to 
// toggle an LED while a button is pressed and 
// turn the LED on when the button is released.  
// This lab will use the hardware already built into the LaunchPad.
// Daniel Valvano, Jonathan Valvano
// January 15, 2016
// Modified by Addison Sears-Collins on August 6, 2018
// PF means Port F

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

#include "TExaS.h"

// Dereference the addresses to get the contents. Then typecast in order to 
// know whether to read 8 16 or 32 bits (i.e. solve the type mismatch)
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// Function prototypes
void Delay100ms(unsigned long time); 


int main(void){ 
	// Variable declarations
	unsigned long volatile delay;
	unsigned long output_pf2;	
	
  TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);  // activate grader and set system clock to 80 MHz
  
	// Initialization code. Written by Addison Sears-Collins
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;   // 1) Turn on the clock for Port F
	delay = SYSCTL_RCGC2_R;           	// 2) Allow time for the clock to start
	GPIO_PORTF_AMSEL_R &= ~0x14;     	// 3) Clear the PF4 and PF2 bits in Port F AMSEL to disable analog. 
							// We need a 0 in bits 2 and bits 4 of Port F. 1 is needed everywhere else
							// Note that the ~ bit operator inverts all the bits
	GPIO_PORTF_PCTL_R &= ~0x14;		// 4) Clear the PF4 and PF2 bit fields in Port F PCTL to configure as GPIO
	GPIO_PORTF_DIR_R |= 0x4;          	// 5) Set the Port F direction register so (0 = input; 1 = output)
							// PF4 is an input and 
							// PF2 is an output
	GPIO_PORTF_AFSEL_R &= ~0x14;		// 6) Clear the PF4 and PF2 bits in Port F AFSEL to disable alternate functions
	GPIO_PORTF_DEN_R |= 0x14;		// 7) Set the PF4 and PF2 bits in Port F DEN to enable digital
	GPIO_PORTF_PUR_R |= 0x10;		// 8) Set the PF4 bit in Port F PUR to activate an internal pullup resistor
	GPIO_PORTF_DATA_R |= 0x4;		// 9) Set the PF2 bit in Port F DATA so the LED is initially ON

	output_pf2 = GPIO_PORTF_DATA_R;
	
	EnableInterrupts();           						// enable interrupts for the grader
	
  while(1){
    // loop body goes here. Written by Addison Sears-Collins
		Delay100ms(1);				// 1) Delay about 100 ms
							// 2) Read the switch and test if the switch is pressed
		if (!(GPIO_PORTF_DATA_R & 0x10)) {	// If PF4=0 (the switch is pressed),
			output_pf2 ^= 0x4;			// toggle PF2 (flip bit two on Port F from 0 to 1, or from 1 to 0)
			GPIO_PORTF_DATA_R &= ~0x4;		// Clear PF2
		  GPIO_PORTF_DATA_R |= output_pf2;		// Set PF2 to the new value (either a 0 if 1 before, or 1 if 0 before)
		}
		else {					// Else PF4=1 (the switch is not pressed), 
			GPIO_PORTF_DATA_R |= 0x4;		// set PF2, so LED is ON
		}																							
	}						// 3) Go to loop  
}

void Delay100ms(unsigned long time){
  unsigned long i;
  while(time > 0){
    i = 1333333;  // this number means 100ms
    while(i > 0){
      i = i - 1;
    }
    time = time - 1; 				// decrements every 100 ms. Having time == 1 as an input parameter 
						// makes sure this loop executes only once
  }
}
