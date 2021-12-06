#include<lpc21xx.h>

#define SIZE 10
#define delay for(int j=0;j<300000;j++);
int data[SIZE]={0x0FC, 0x60, 0x0DA, 0x0F2,0x66, 0x0B6, 0x0BE, 0x0E0, 0x0FE, 0x0F6}; 
/* Hex values of '0' to '9' digits
Here A is MSB i.e. P0.7 and G is LSB i.e. P0.0 and values calculated for CC display
*/
//int ndata[SIZE]={0x};

int main(void)
{
	int i = 0;
	PINSEL0 = 0x00000000; 		// Cong P0L as GPIO
	PINSEL1 = 0x00000000; 		// Cong P0H as GPIO
	IO0DIR = 0x000000FF; 			// P0.0 to P0.7 conf as output
	
	while(1)
	{
		if((IO0PIN & 0x00010000) == 0x00010000)
		{			
			for(i=0;i<SIZE;i++) 
			{
				IO0SET = ~data[i];
				delay;
				IO0CLR = ~data[i];
				
			}				
		}
		
		
	}

	return 0;
}