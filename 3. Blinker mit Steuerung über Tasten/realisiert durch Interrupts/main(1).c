/*
 * ARBK_Praktikum_3 Interrupts
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int LED_Gelb = 0, LED_Rot = 0;

int main(void)
{
	DDRD = 0b11000000;
	PORTD = 0b00001100;
	double delay = 1000.0;
	
	// Aktiviere Int0 und Int1
	GICR |= ((1 << INT0) | (1 << INT1));
	
	MCUCR &= ~((1 << ISC11) | (1 << ISC10) | (1 << ISC00) | (1 << ISC01));// set INT0 to trigger on ANY logic change
	sei();		// turn on interrupts
	
    while (1) 
    {
		if (LED_Gelb == 1)
		{
			
			PORTD ^= (1 << PD6);
			_delay_ms(delay);
		}
		else if (LED_Rot == 1)
		{
			
			PORTD ^= (1 << PD7);
			_delay_ms(delay);
		}
    }
}

// INT0 - Taster 1 (LED_GELB)
ISR(INT0_vect)
{
	if (LED_Gelb == 1)
	{
		// Gelb + Rot ausschalten
		PORTD &= ~((1 << PD6) | (1 << PD7));
		LED_Gelb = 0;
		LED_Rot = 0;		
	}
	else
	{
		// Rot direkt ausschalten, Gelb auf 1
		PORTD &= ~(1 << PD7);
		LED_Gelb = 1;
		LED_Rot = 0;
	}
	
	_delay_ms(300);
}

// INT0 - Taster 2 (LED_ROT)
ISR(INT1_vect)
{
	if (LED_Rot == 1)
	{
		// Gelb + Rot ausschalten
		PORTD &= ~((1 << PD6) | (1 << PD7));
		LED_Gelb = 0;
		LED_Rot = 0;
	}
	else
	{
		// Gelb direkt ausschalten,Rot auf 1
		PORTD &= ~(1 << PD6);
		LED_Gelb = 0;
		LED_Rot = 1;
	}
	
	_delay_ms(300);
}