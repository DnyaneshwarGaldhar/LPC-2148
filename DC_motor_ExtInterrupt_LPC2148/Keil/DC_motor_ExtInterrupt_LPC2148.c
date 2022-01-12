
#include<lpc214x.h>
#define bit(x) (1<<x)
#define delay for(int z=0; z<=60000; z++)
unsigned int i;

void init_ext_interrupt(void);
__irq void Ext_ISR(void);


void main(void)
{
				init_ext_interrupt();				// initialize the external interrupt
				IO0DIR = (IO0DIR | 0x000000FF);		
				IO0PIN=0; //Clear all IO Pins in P0
				VPBDIV=0x01; //PCLK = 60MHz
		
				while(1) 
				{	
					//Forward
					IO0SET = bit(0); //IN1 = 1
					IO0CLR = bit(1); //IN2 = 0
					for(int j=0; j<20; j++)		
						delay;
				
					//Reverse
					IO0SET = bit(1); //IN1 = 1
					IO0CLR = bit(0); //IN2 = 0
					for(int k=0; k<20; k++)
						delay;
								
				}
}

void init_ext_interrupt()  // Initialize Interrupt
{
			EXTMODE = 0x00; 		//Edge sensitive mode on EINT2
			EXTPOLAR &= ~(0x01); 	//Falling Edge Sensitive
			PINSEL0 = 0x80000000; //Select Pin function P0.15 as EINT2
			 // initialize the interrupt vector 
			VICIntSelect &= ~ (1<<16);        	// EINT2 selected as IRQ 16
			VICVectAddr5 = (unsigned int)Ext_ISR; // address of the ISR
			VICVectCntl5 = (1<<5) | 16;			// 
			VICIntEnable = (1<<16);           	// EINT2 interrupt enabled
			EXTINT &= ~(0x4);	
}



__irq void Ext_ISR(void) // Interrupt Service Routine-ISR
{
			IO0CLR |= (1<<0); 	 // Turn OFF Motor
			IO0CLR |= (1<<1);
			delay;
			delay;
			EXTINT |= 0x4; //clear interrupt
			VICVectAddr = 0; // End of interrupt execution
}
