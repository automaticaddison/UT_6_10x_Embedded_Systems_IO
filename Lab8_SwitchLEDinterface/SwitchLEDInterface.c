// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED (PE1)
// while a button (PE0) is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// August 8, 2018
// Professor Jon Valvano and Ramesh Yerraballi
// Author: Addison Sears-Collins

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****
// None

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(unsigned long time); 

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void){ 
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
	// Variable declarations
	unsigned long volatile delay;
	unsigned long output_pe1;
	
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz
  
	// Initialization code. Written by Addison Sears-Collins
	SYSCTL_RCGC2_R |= 0x00000010;   // 1) Turn on the clock for Port E
	delay = SYSCTL_RCGC2_R;         // 2) Allow time for the clock to start
	GPIO_PORTE_AMSEL_R &= ~0x03;    // 3) Clear the PE0 and PE1 bits in Port E AMSEL to disable analog. 
	GPIO_PORTE_PCTL_R &= ~0x03;		  // 4) Clear the PE0 and PE1 bit fields in Port E PCTL to configure as GPIO
	GPIO_PORTE_DIR_R |= 0x02;       // 5) Set the Port E direction register so (0 = input; 1 = output)
							                          // PE0 is an input and 
							                          // PE1 is an output
	GPIO_PORTE_AFSEL_R &= ~0x03;		// 6) Clear the PE0 and PE1 bits in Port E AFSEL to disable alternate functions
	GPIO_PORTE_DEN_R |= 0x03;		    // 7) Set the PE0 and PE1 bits in Port E DEN to enable digital
	GPIO_PORTE_PUR_R &= ~0x01;		  // 8) Clear the PE0 bit in Port E PUR to deactivate an internal pullup resistor
	GPIO_PORTE_DATA_R |= 0x02;	    // 9) Set the PE1 bit in Port E DATA so the LED is initially ON

	output_pe1 = GPIO_PORTE_DATA_R;
		
  EnableInterrupts();                  // enable interrupts for the grader
	
  while(1){
    Delay100ms(1);                     // 1) Delay about 100 ms
							                         // 2) Read the switch and test if the switch is pressed
		if (GPIO_PORTE_DATA_R & 0x01) {	      // If PE0=1 (the switch is pressed),
			output_pe1 ^= 0x02;			              // toggle PE1 (flip bit 1 on Port E from 0 to 1, or from 1 to 0)
			GPIO_PORTE_DATA_R &= ~0x02;		        // Clear PE1
		  GPIO_PORTE_DATA_R |= output_pe1;		  // Set PE1 to the new value (either a 0 if 1 before, or 1 if 0 before)
		}
		else {					                   // Else PE0=0 (the switch is not pressed), 
			GPIO_PORTE_DATA_R |= 0x02;	          // Set PE1, so LED is ON
		}				
  }   // Go to loop  
}

void Delay100ms(unsigned long time){
  unsigned long i;
  while(time > 0){
    i = 1333333;      // this number means 100ms
    while(i > 0){
      i = i - 1;
    }
    time = time - 1;  // decrements every 100 ms. Having time == 1 as an input parameter 
						          // makes sure this loop executes only once
  }
}

