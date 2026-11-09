
#include <xc.h>
#include "main.h"
#include "timer0.h"

extern unsigned int flag;
unsigned short blink;

void interrupt isr (void)
{
	static unsigned short for_minute;
	static unsigned short count;

	if (TMR2IF)								//If the Timer2 Overflow Interrupt Flag Bit is set, Timer2 is requesting for an Interrupt.
	{
		if (count++ == 20000)			//The formula for the Timer2 yields the result as: every 20000/flag ticks.
		{
			blink++;						//Increment the 'blink' for Blnking the Cursor.
			count = 0;						//Reset the 'count' as 0.
		}
	}
	TMR2IF = 0;								//To clear the Timer2 Overflow Interrupt Flag Bit to avoid Recursive interrupts.
}
