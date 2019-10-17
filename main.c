#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
//#include <avr/atomic.h>

#include "led.h"
#include "serial.h"
#include "timer.h"

uint8_t data = 0;


ISR(ADC_vect)
{
	data = ADCH;
	printf("%d\n", data);

}

ISR(TIMER2_COMPA_vect){
	OCR0A = data;
//	start_convers();//start
}





void main (void) {

	LED_init();
	uart_init();
	timer_init();
	//timer2_init();



	ADCSRA |= (1<< ADEN) | (1<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
	ADMUX |= (1<<ADLAR) | (0<<REFS1) | (1<<REFS0) | (0<<MUX3) | (0<<MUX2) | (0<< MUX1) | (0<<MUX0);
	//timer0
	TCCR0A |= (1 << COM0A1) | (0<<WGM02) | (1<<WGM01) | (1<<WGM00);
  TCCR0B |= (0 << CS02) | (1 << CS01) | (1 << CS00);
	//timer2
	TCCR2A |= (1 << WGM21) | (0 << WGM20);
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
  TIMSK2 |= (1 << OCIE2A);

  OCR2A = 77;



	sei();








	char str[] = "Pushed";
	char str2[] = "Released";




uint8_t temp;
uint8_t previous = 0;

	while (1) {
	ADCSRA |= (1<<ADSC);
	_delay_ms(100);

uint8_t current = (PIND & (1<<PD2));



		if(current != previous && current == 4){
			printf("%s\n", str);
			_delay_ms(5);

		}


		else if(current != previous){
			printf("%s\n", str2);
			_delay_ms(5);


		}
		previous = current;

	}
}
