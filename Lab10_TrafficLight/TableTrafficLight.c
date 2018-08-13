// ***** 0. Documentation Section *****
// TableTrafficLight.c for Lab 10
// Runs on LM4F120/TM4C123
// Index implementation of a Moore finite state machine to operate a traffic light.  
// Professor Daniel Valvano, Jonathan Valvano
// Author: Addison Sears-Collins
// August 12, 2018

// east/west red light connected to PB5
// east/west yellow light connected to PB4
// east/west green light connected to PB3
// north/south facing red light connected to PB2
// north/south facing yellow light connected to PB1
// north/south facing green light connected to PB0
// pedestrian detector connected to PE2 (1=pedestrian present)
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)
// "walk" light connected to PF3 (built-in green LED)
// "don't walk" light connected to PF1 (built-in red LED)

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****
	
// Declarations for implementing the SysTick
#define NVIC_ST_CTRL_R      (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R    (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R   (*((volatile unsigned long *)0xE000E018))


// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void PortE_Init(void); // Initialize Port E for input
void PortB_Init(void); // Initialize Port B for output
void PortF_Init(void); // Initialize Port F for output

// Implement Phase-Lock_Loop
void PLL_Init(void);

// Implement SysTick
void SysTick_Init(void);
void SysTick_Wait(unsigned long delay);
void SysTick_Wait10ms(unsigned long delay);

// Linked data structure
struct State {
  unsigned long Out_TrafficLights; // east/west and north/south lights currently
	unsigned long Out_WalkLights; // Pedestrian walk signal (walk or don't walk)
  unsigned long Time;     // How much time we spend in each state
  unsigned long Next[8];  // 8 potential next states for each current state
};

// typedef creates a new name for an existing type. 
typedef const struct State STyp;

// Declare the different states the system can be in
#define goNS     0 // Let north/south traffic go
#define slowNS   1 // Slow down north/south traffic
#define goEW     2 // Let east/west traffic go
#define slowEW   3 // Slow down east/west traffic
#define doWalk   4 // Let pedestrians cross the street in any direction
#define hurryUp1 5 // Tell pedestrians to hurry up and finish crossing the street
#define hurryUp2 6 // Tell pedestrians to hurry up and finish crossing the street
#define hurryUp3 7 // Tell pedestrians to hurry up and finish crossing the street
#define hurryUp4 8 // Tell pedestrians to hurry up and finish crossing the street
#define hurryUp5 9 // Tell pedestrians to hurry up and finish crossing the street

// Define the different states the system can be in
// FSM holds an array of Styp structs
STyp FSM[10] = {
  {0x21,0x02,90,{goNS,slowNS,goNS,slowNS,slowNS,slowNS,slowNS,slowNS}},  // 90 = 900 milliseconds
  {0x22,0x02,90,{goEW,goEW,goEW,goEW,doWalk,goEW,doWalk,goEW}},
  {0x0C,0x02,90,{goEW,goEW,slowEW,slowEW,slowEW,slowEW,slowEW,slowEW}},
	{0x14,0x02,90,{doWalk,doWalk,goNS,goNS,doWalk,doWalk,doWalk,doWalk}},
	{0x24,0x08,90,{doWalk,hurryUp1,hurryUp1,hurryUp1,doWalk,hurryUp1,hurryUp1,hurryUp1}},
	{0x24,0x02,90,{hurryUp2,hurryUp2,hurryUp2,hurryUp2,hurryUp2,hurryUp2,hurryUp2,hurryUp2}},
	{0x24,0x00,90,{hurryUp3,hurryUp3,hurryUp3,hurryUp3,hurryUp3,hurryUp3,hurryUp3,hurryUp3}},
	{0x24,0x02,90,{hurryUp4,hurryUp4,hurryUp4,hurryUp4,hurryUp4,hurryUp4,hurryUp4,hurryUp4}},
	{0x24,0x00,90,{hurryUp5,hurryUp5,hurryUp5,hurryUp5,hurryUp5,hurryUp5,hurryUp5,hurryUp5}},
  {0x24,0x02,90,{goNS,goEW,goNS,goNS,goNS,goEW,goNS,goNS}}
};

unsigned long S;  // index to the current state
unsigned long Input;

// ***** 3. Subroutines Section *****

int main(void){ volatile unsigned long delay;
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210,ScopeOff); // activate grader and set system clock to 80 MHz
 
	PLL_Init();
  SysTick_Init();   
	SYSCTL_RCGC2_R |= 0x00000032;   // Turn on the clock for Port B, E, and F
	delay = SYSCTL_RCGC2_R;         // Allow time for the clock to start
	PortE_Init();
	PortB_Init();
	PortF_Init();
	
  S = goNS;  // Initialize the state of the system
	
  EnableInterrupts();
  while(1){
    GPIO_PORTB_DATA_R = FSM[S].Out_TrafficLights;  // set traffic lights
		GPIO_PORTF_DATA_R = FSM[S].Out_WalkLights;  // set the pedestrian walk lights
    SysTick_Wait10ms(FSM[S].Time);
		Input = GPIO_PORTE_DATA_R & 0x07; 
    S = FSM[S].Next[Input]; 
  }
}

// Implement delays based on SysTick
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock
}

// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)
void SysTick_Wait(unsigned long delay){
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}

// 800000*12.5ns equals 10ms
void SysTick_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    SysTick_Wait(800000);  // wait 10ms
  }
}

// Subroutine to initialize port E pins for input
// PE2 is pedestrain walk sensor, PE1 is north/south sensor, PE0 is east/west sensor
// Inputs: None
// Outputs: None
// Notes: ...
void PortE_Init(void){
	GPIO_PORTE_AMSEL_R &= ~0x07;      // 1) Clear the PE2-0 bits in Port E AMSEL to disable analog. 
	GPIO_PORTE_PCTL_R &= 0x00000000;  // 2) Clear the PE2-0 bit fields in Port E PCTL to configure as GPIO
	GPIO_PORTE_DIR_R &= ~0x07;        // 3) Set the Port E direction register so (0 = input; 1 = output)
	GPIO_PORTE_AFSEL_R &= ~0x07;      // 4) Clear the PE2-0 bits in Port E AFSEL to disable alternate functions
	GPIO_PORTE_DEN_R |= 0x07;         // 5) Set the PE2-0 bits in Port E DEN to enable digital
}

// Subroutine to initialize port B pins for output
// PB5-0 are the traffic lights
// Inputs: None
// Outputs: None
// Notes: ...
void PortB_Init(void){
	GPIO_PORTB_AMSEL_R &= ~0x3F;      // 1) Clear the PB5-0 bits in Port B AMSEL to disable analog. 
	GPIO_PORTB_PCTL_R &= 0x00000000;  // 2) GPIO Clear bit PCTL
	GPIO_PORTB_DIR_R |= 0x3F;         // 3) Set the Port B direction register so (0 = input; 1 = output)
	GPIO_PORTB_AFSEL_R &= ~0x3F;      // 4) Clear the PB5-0 bits in Port B AFSEL to disable alternate functions
	GPIO_PORTB_DEN_R |= 0x3F;         // 5) Set the PB5-0 bits in Port B DEN to enable digital
}

// Subroutine to initialize port F pins for output
// PF3 is walk like; PF1 is don't walk light
// Inputs: None
// Outputs: None
// Notes: ...
void PortF_Init(void){
	GPIO_PORTF_AMSEL_R &= ~0x0A;     // 1) Clear the PF1 and PF3 in Port F AMSEL to disable analog. 
	GPIO_PORTF_PCTL_R &= 0x00000000; // 2) GPIO Clear bit PCTL
	GPIO_PORTF_DIR_R |= 0x0A;        // 3) Set the Port F direction register so (0 = input; 1 = output)
	GPIO_PORTF_AFSEL_R &= ~0x0A;     // 4) Clear the PF1 and PF3 bits in Port F AFSEL to disable alternate functions
	GPIO_PORTF_DEN_R |= 0x0A;        // 5) Set the PF1 and PF3 bits in Port F DEN to enable digital
}

