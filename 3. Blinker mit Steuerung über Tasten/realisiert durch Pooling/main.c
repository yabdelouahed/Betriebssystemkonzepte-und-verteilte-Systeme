/*
 * ARBk 3
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

//(0 == aus, 1 == blinken)
int LED_Gelb = 0, LED_Rot = 0;

void Poll_T1(void)
{
	
	
	// Wenn LED_Gelb aus ist und der Taster gedrückt wird
	if (!(PIND & (1 << PD2)) & (LED_Gelb == 0))
	{
		// Rot ausschalten
		PORTD &= ~(1 << PD4);
		LED_Rot = 0;
				
		// Gelb blinken
		LED_Gelb = 1;
		
		_delay_ms(250);
	}
	// Wenn LED_Gelb blinkt und der Taster gedrückt wird
	else if (!(PIND & (1 << PD2)) & (LED_Gelb == 1))
	{
		// Rot ausschalten
		PORTD &= ~(1 << PD4);
		LED_Rot = 0;
				
		// Gelb ausschalten
		PORTD &= ~(1 << PD3);
		LED_Gelb = 0;
		
		_delay_ms(150);
	}
}
	
void Poll_T2(void)
{
	
	// Wenn LED_Rot aus ist und der Taster gedrückt wird
	if (!(PINB & (1 << PB5)) & (LED_Rot == 0))
	{
		// Gelb ausschalten
		PORTD &= ~(1 << PD3);
		LED_Gelb = 0;
		
		// Rot blinken
		LED_Rot = 1;
		
		_delay_ms(250);
	}
	// Wenn LED_Rot blinkt und der Taster gedrückt wird
	else if (!(PINB & (1 << PB5)) & (LED_Rot == 1))
	{
		// Gelb ausschalten
		PORTD &= ~(1 << PD3);
		LED_Gelb = 0;
		
		// Rot ausschalten
		PORTD &= ~(1 << PD4);
		LED_Rot = 0;
		
		_delay_ms(150);
	}
}

//Polling
int main(void)
{
	/*
	*	Bit 3-4 als Ausgänge { LED }
	*/
	DDRD = 0b00011000;
	DDRB = 0b00000000;
	
	// Ports 
	/*
	* Taster: 2^D -> Gelb_LED (an,aus)
	* Taster: 5^B -> Rote_LED  (an,aus)
	*/
	
	PORTD = 0b00000100;
	PORTB = 0b00100000;
	
	// Delay
	const double delay = 1000.0;
	

	while (1)
	{
		// Polling T1 (Gelb)
		Poll_T1();
		
		// Polling T2 (Rot)
		Poll_T2();
		
		
		if (LED_Gelb == 1)
		{
			PORTD ^= (1 << PD3);
			_delay_ms(delay);
		}

		
  		if (LED_Rot == 1)
		{
			PORTD ^= (1 << PD4);
			_delay_ms(delay);
		}
	}
	
	return 0;
}