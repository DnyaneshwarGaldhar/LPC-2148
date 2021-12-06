#include<lpc214x.h>

#define bit(x) (1<<x)
#define delay for(i=0;i<1000;i++);



/* 
P0.0 to P0.7 Data port
P0.10			RS
P0.11			RW
P0.12 		EN
*/

unsigned int i;

void lcd_int();
void dat(unsigned char);
void cmd(unsigned char);
void string(unsigned char *);


void main()
{
    PINSEL0 = 0x00;
		IO0DIR = 0x00001CFF;
		lcd_int();
	
		while(1)
		{
			if((IO0PIN & 0x00010000) == 0x00010000)
			{	
				
				cmd(0x80);
				string(" Obj Detected!!!");
			}	
			else
			{
				
				cmd(0x80);
				string("Obj Not Detected");
			}
		}
		
}

void lcd_int()
{
    cmd(0x38);
    cmd(0x0c);
    cmd(0x06);
    cmd(0x01);
    cmd(0x80);
}

void cmd(unsigned char a)
{
    IO0PIN&=0x00;
    IO0PIN|=(a<<0);
    IO0CLR|=bit(10);                //rs=0
    IO0CLR|=bit(11);                //rw=0
    IO0SET|=bit(12);               //en=1
    delay;
    IO0CLR|=bit(12);               //en=0
}

void dat(unsigned char b)
{
    IO0PIN&=0x00;
    IO0PIN|=(b<<0);
    IO0SET|=bit(10);                //rs=1
    IO0CLR|=bit(11);                //rw=0
    IO0SET|=bit(12);               //en=1
    delay;
    IO0CLR|=bit(12);               //en=0
}

void string(unsigned char *p)
{
    while(*p!='\0') {
        dat(*p++);
    }
}