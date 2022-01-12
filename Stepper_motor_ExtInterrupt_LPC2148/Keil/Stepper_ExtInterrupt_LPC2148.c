#include <lpc214x.h>
#define delay for(int z=0; z<50000; z++)

void init_ext_interrupt(void);
__irq void Ext_ISR(void);

int main (void)
{
	init_ext_interrupt(); 						// initialize the external interrupt
	IO0DIR = (IO0DIR | 0x0000000F);		// Configure P0.0-P0.3 as output(used for controlling stepper motor) 
	while(1)
	{
			for(int i = 0; i<12; i++ )		//	Full step rotation in one direction 
			{
				IO0PIN = ( (IO0PIN | 0x00000008) & 0xFFFFFFF8 );
				delay;
				IO0PIN = ( (IO0PIN | 0x0000000C) & 0xFFFFFFFC );
				delay;
				IO0PIN = ( (IO0PIN | 0x00000004) & 0xFFFFFFF4 );
				delay;
				IO0PIN = ( (IO0PIN | 0x00000006) & 0xFFFFFFF6 );
				delay;
				IO0PIN = ( (IO0PIN | 0x00000002) & 0xFFFFFFF2 );
				delay;
				IO0PIN = ( (IO0PIN | 0x00000003) & 0xFFFFFFF3 );
				delay;
				IO0PIN = ( (IO0PIN | 0x00000001) & 0xFFFFFFF1 );
				delay;
				IO0PIN = ( (IO0PIN | 0x00000009) & 0xFFFFFFF9 );
				delay;		
			}
			IO0PIN = ( (IO0PIN | 0x00000008) & 0xFFFFFFF8 );
			delay;
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
			
			IO0PIN = (IO0PIN | 0x00000000);	 // Turn OFF Motor
			delay;
			delay;
			EXTINT |= 0x4; //clear interrupt
			VICVectAddr = 0; // End of interrupt execution
}