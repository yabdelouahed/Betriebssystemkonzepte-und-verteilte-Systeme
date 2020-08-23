/*
 * GccApplication1.c
 *
 * Created: 29.10.2018 21:03:10
 * Author : Yassine
 */ 

#include <avr/io.h>
#define F_CPU 3686400UL
# include <util/delay.h>
	
uint8_t repeats = 0;

int main (void)
{
	DDRB = 0b00000111; // Setze PORTB als Ausgang für die erste 3 Bits
	
	while (1) {
		
	right(); // Ruf right solange die Bedingung in die Funktion erfüllt ist
	left();	 // Ruf left solange die Bedingung in die Funktion erfüllt ist
	
	}
	
	return 0;
}

void right()
{
	while (repeats<2) {
		
		PORTB = (1 << repeats ); // Setze jedes mal 1 in die Richtige Bit (ist von der Variable repeats abhängig)
		_delay_ms (200);		 // Warte 200ms bis nächstes Befehl
		repeats++;				 // Erhöhe repeats um 1
		
	}
}

void left() // Analog zu right
{
	while (repeats>0) {
		
		PORTB = (1 << repeats ); 
		_delay_ms (200);
		repeats--;
		
	}
}



// f) Mit C++ .hex = 496 Byte || mit Assemler .hex = 206 
// g)  mit O0	|  mit O1	|	mit O2	| mit O3
//    672Byte	| 496Byte	| 443Byte	| 443Byte


