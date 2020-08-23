
.include "m8def.inc"		; Prozessordefinitionen laden
.org 0x000					; Platziere Code an die Adresse 000
	rjmp start
	

start:
	ldi r16, LOW( RAMEND )	; HIGH-Byte der obersten RAM-Adresse
	out SPL, r16			; da ATmega ..  mehr als 256Byte RAM besitzt, passt die Adresse nicht mehr in ein Byte
	ldi r16, HIGH( RAMEND ) ; LOW-Byte der obersten RAM-Adresse
	out SPH, r16 ;			
	LDI r16,0b00000111		; Lade 0b00000001 zu r16 => Startpunkt
	OUT DDRB, r16
	LDI r16, 0b00000001

left:
	
	OUT PORTB,r16			; Schreib r16 im entschprechenden PORTD
	LSL r16					; Verchieb die 1 nach links (Logical Schift Left)
	RCALL delay
	CPI r16, 0b00000100		; Vegleich if r16 = 0b00000100 => Stoppunkt
	BREQ right				; (branch if equal Befehl), wenn Z=1 jmp into right
	RJMP left				; Wenn nicht verschiebt sich die 1 nach links

right:						; Analog zu left
	OUT PORTB, r16
	LSR r16					
	RCALL delay
	CPI r16, 0b00000001		;
	BREQ left
	RJMP right
	

delay :
    ldi  r19, 4				; laden ..
    ldi  r20, 168			; laden
    ldi  r21, 12			; laden
L1: dec  r21
    brne L1					; (branch if not equal) if Z=0
    dec  r20
    brne L1
    dec  r19				; decrement , -1 von mein register und das ergebniss in RD speichern
    brne L1					; (branch if not equal) if Z=0
	nop
     ret ; regesterv counter

