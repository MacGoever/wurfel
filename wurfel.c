#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 1000000UL
#include <util/delay.h>


int main(void){
	volatile uint8_t result = 0;
	volatile uint8_t counter = 0;

	DDRB = 0b11111111;		// Set PB as output
	PORTB = 0b00000000;
	DDRD = 0b00000000;		// Set PD as input
	PORTD = 0b00001000;		// Set Pull Up Resistor


	TCCR0B = (1<<CS00 );		//Set Prescaler to 1, Timer0 is the random source 

	counter=0;
	while((PIND & 0b00001000)){
		counter++;
		_delay_ms(200);
		switch(counter){
			case 1:
				PORTB = 0b10011011;
			break;
			case 2:
				PORTB = 0b10101101;
			break;
			case 3:
				PORTB = 0b10110110;
				counter=0;	
			break;
		}
		
	}

	while(1){

		if(!(PIND & 0b00001000)) {
			result=TCNT0 % 6 + 1;
			counter=255;
			while(counter){
				result++;		//roll the dice!
				if(result > 6) result = 1;
				switch(result){	
					case 1:
						PORTB=0b00001100;
					break;
					case 2:
						PORTB=0b01011011;
					break;
					case 3:
						PORTB=0b01011110;
					break;
					case 4:
						PORTB=0b01101100;
					break;
					case 5:
						PORTB=0b01110110;
					break;
					case 6:
						PORTB=0b01110111;
					break;
				}


				counter--;
				if (counter>110) _delay_ms(5);
				if (counter>50 && counter<=110) _delay_ms(10);
				if (counter>30 && counter<=50) _delay_ms(20);
				if (counter>15 && counter<=30) _delay_ms(30);
				if (counter>3 && counter<=15) _delay_ms(70);
				if (counter<=2) _delay_ms(150);
			}
		
		}
		_delay_ms(50);
	}
}
