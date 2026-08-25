#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UART1.h"

#define trig_on			PORTF |= _BV(2)
#define trig_off		PORTF &= ~_BV(2)

#define BUZ_ON			PORTD &= ~_BV(7)
#define BUZ_OFF			PORTD |= _BV(7)

#define LE1_ON			PORTA &= ~_BV(6)
#define LE2_ON			PORTC &= ~_BV(6)
#define LE3_ON			PORTC &= ~_BV(7)

#define LE1_OFF			PORTA |= _BV(6)
#define LE2_OFF			PORTC |= _BV(6)
#define LE3_OFF			PORTC |= _BV(7)

#define START_UART		7
#define END_UART		8

int ll = 0;
int led_pwm = 7;
int led_led = 0;
int key = 20;
int sw = 20;
int read = 0;
int t = 0;
int tt = 0;

int error = 0;
int elv1_f = 1;
int elv2_f = 1;
int elv1_h = 0;
int elv2_h = 0;
int temp = 0;

int elv1_d = 0;
int elv2_d = 0;
int elv1_c = 0;
int elv2_c = 0;
int goal = 20;
int temp_goal = 20;
int dis = 0;

char txdata[6] = {0,};
int led_arr[19] = {0,};

uint8_t led_flag = 0;
uint8_t scan_flag = 0;
uint8_t move_1 = 0;
uint8_t move_2 = 0;
uint8_t error_flag = 0;
uint8_t buz_flag = 0;
uint8_t stop_flag = 0;
uint8_t open_flag = 0;
uint8_t close_flag = 0;
uint8_t od_flag = 0;
uint8_t cd_flag = 0;
uint8_t clear_flag = 0;
uint8_t c_flag = 0;
uint8_t input_flag = 0;
uint8_t check_flag = 0;
uint8_t moved = 0;

#include "oled.h"

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 0x88;
	
	if ((PINF &= (1<<PINF3)))
		dis++;
	
	if (led_flag == 1)
	{
		ll++;
		if (ll < led_pwm && led_arr[led_led] == 1)
			led_on(led_led);
		if (ll >= led_pwm)
		{
			led_off();
			led_led++;
		}
		if (ll >= 10)
			ll = 0;
			
		if (led_led >= 19)
			led_led = 0;
	}
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = 0xff06;
	
	t++;
	if (t >= 3000)
		t = 0;
	
	if (buz_flag == 1)
	{
		tt++;
		if (tt < 500)
			BUZ_ON;
		else if (tt < 1000)
			BUZ_OFF;
		
		if (tt > 1000)
			tt = 0;
	}

	if (scan_flag == 1)
		sw_interrupt();
}

void init()
{
	DDRA = 0x7f;
	DDRB = 0x7f;
	DDRC = 0xc7;
	DDRD = 0x80;
	DDRE = 0x00;
	DDRF = 0x04;
	
	BUZ_OFF;
	
	SoftI2CInit1();
	oled_init1();
	SoftI2CInit2();
	oled_init2();
	SoftI2CInit3();
	oled_init3();
	oled_clear1();
	oled_clear2();
	oled_clear3();
	
	UART1_init();
	ADC_init(0);
	
	TIMSK |= 0x01;
	TCCR0 = 0x02;
	TCNT0 = 0x88;
	
	TIMSK |= 0x04;
	TCCR1B = 0x03;
	TCNT1 = 0xff06;
	
	PORTA |= _BV(6);
	PORTC |= _BV(6);
	PORTC |= _BV(7);
	PORTD |= _BV(6);
	
	sei();
}

void ADC_init(unsigned char channel)
{
	ADMUX |= (1 << REFS0);
	
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADFR);
	
	ADMUX = ((ADMUX & 0xE0) | channel);
	ADCSRA |= (1 << ADSC);
}

int read_ADC(void)
{
	while(!(ADCSRA & (1 << ADIF)));
	
	return ADC;
}

void send_data()
{
	UART1_transmit(START_UART);
	UART1_transmit(txdata[0]);
	UART1_transmit(txdata[1]);
	UART1_transmit(txdata[2]);
	UART1_transmit(txdata[3]);
	UART1_transmit(txdata[4]);
	UART1_transmit(txdata[5]);
	UART1_transmit(END_UART);
}

void key_matrix()
{
	key = 20;
	
	for (int x = 0; x < 3; x++)
	{
		PORTC |= 0x07;
		PORTC &= ~_BV(x);
		
		for (int y = 3; y < 6; y++)
		{
			if (bit_is_clear(PINC, y))
				key = ((y-2)+(x*3));
		}
	}
	
	if (key == 1)
		key = 11;
	else if (key == 2)
		key = 10;
	else if (key == 3)
		key = 18;
	else if (key == 4)
		key = 13;
	else if (key == 5)
		key = 12;
	else if (key == 6)
		key = 17;
	else if (key == 7)
		key = 15;	
	else if (key == 8)
		key = 14;
	else if (key == 9)
		key = 16;
		
	if (elv1_h >= 1 || elv2_h >= 1)
	{
		if (key == 16)
		{
			if (error_flag == 0 && stop_flag == 0)
			{
				error_flag = 1;
				led_arr[16] = 1;
			}
			else if (error_flag == 1 && stop_flag == 1)
				error_flag = 0;
		}
		else if (key == 17 && od_flag == 1)
			open_flag = 1;
		else if (key == 18 && cd_flag == 1)
			close_flag = 1;
		if (key == 16 || key == 17 || key == 18)
			key = 20;
		if (led_arr[key] == 1)
			key = 20;
		else if (key != 20)
			led_arr[key] = 1;
	}	
	else
		key = 20;
}

void out_led_on(int elv, int f)
{
	if (elv == 1)
	{
		LE1_ON;
		
		if (f == 1)
			PORTB |= _BV(0);
		else if (f == 2)
			PORTB |= _BV(1);
		else if (f == 3)
			PORTB |= _BV(2);
		else if (f == 4)
			PORTB |= _BV(3);
		else if (f == 5)
			PORTB |= _BV(4);
	}
	else if (elv == 2)
	{
		LE3_ON;
		
		if (f == 2)
			PORTB |= _BV(2);
		else if (f == 3)
			PORTB |= _BV(3);
		else if (f == 4)
			PORTB |= _BV(4);
		else if (f == 5)
			PORTB |= _BV(5);
		else if (f == 6)
			PORTB |= _BV(6);
	}
}

void out_led_off(int elv, int f)
{
	if (elv == 1)
	{
		if (f == 1)
			PORTB &= ~_BV(0);
		else if (f == 2)
			PORTB &= ~_BV(1);
		else if (f == 3)
			PORTB &= ~_BV(2);
		else if (f == 4)
			PORTB &= ~_BV(3);
		else if (f == 5)
			PORTB &= ~_BV(4);
	}
	else if (elv == 2)
	{
		if (f == 2)
			PORTB &= ~_BV(2);
		else if (f == 3)
			PORTB &= ~_BV(3);
		else if (f == 4)
			PORTB &= ~_BV(4);
		else if (f == 5)
			PORTB &= ~_BV(5);
		else if (f == 6)
			PORTB &= ~_BV(6);
	}	
}

void led_on(int k)
{
	if (k == 0)
	{
		PORTB |= _BV(0);
		LE1_ON;
	}
	else if (k == 1)
	{
		PORTB |= _BV(1);
		LE1_ON;
	}
	else if (k == 2)
	{
		PORTB |= _BV(2);
		LE1_ON;
	}
	else if (k == 3)
	{
		PORTB |= _BV(3);
		LE1_ON;
	}
	else if (k == 4)
	{
		PORTB |= _BV(4);
		LE1_ON;
	}
	else if (k == 5)
	{
		PORTB |= _BV(2);
		LE3_ON;
	}
	else if (k == 6)
	{
		PORTB |= _BV(3);
		LE3_ON;
	}
	else if (k == 7)
	{
		PORTB |= _BV(4);
		LE3_ON;
	}
	else if (k == 8)
	{
		PORTB |= _BV(5);
		LE3_ON;
	}
	else if (k == 9)
	{
		PORTB |= _BV(6);
		LE3_ON;
	}
	else if (k == 10)
	{
		PORTB |= _BV(4);
		LE2_ON;
	}
	else if (k == 11)
	{
		PORTB |= _BV(1);
		LE2_ON;
	}
	else if (k == 12)
	{
		PORTB |= _BV(3);
		LE2_ON;
	}
	else if (k == 13)
	{
		PORTB |= _BV(0);
		LE2_ON;
	}
	else if (k == 14)
	{
		PORTB |= _BV(2);
		LE2_ON;
	}
	else if (k == 15)
	{
		PORTB |= _BV(6);
		LE1_ON;
	}
	else if (k == 16)
	{
		PORTB |= _BV(5);
		LE2_ON;
	}
	else if (k == 17)
	{
		PORTB |= _BV(6);
		LE2_ON;
	}
	else if (k == 18)
	{
		PORTB |= _BV(0);
		LE3_ON;
	}											
}

void led_off()
{
	PORTB = 0x00;
	LE1_OFF;
	LE2_OFF;
	LE3_OFF;
}

void start_display()
{
	closed_door3();
	write_number1(55,elv1_f);
	write_number2(55,elv2_f);
	
	led_flag = 1;
	for (int i = 0; i < 5; i++)
	{
		led_arr[i] = 1;
		_delay_ms(50);
	}
	
	for (int i = 0; i < 5; i++)
		led_arr[i] = 0;
		
	_delay_ms(50);
	
	for (int i = 5; i < 10; i++)
	{
		led_arr[i] = 1;
		_delay_ms(50);
	}
	
	for (int i = 5; i < 10; i++)
		led_arr[i] = 0;
}

void temp_check()
{
	ADC_init(0);
	read = read_ADC();
	temp = ((read*5.0)/1023.0) * 100.0;
}

void read_data()
{
	temp_check();

	txdata[0] = (elv1_f << 4) | elv1_h;
	txdata[1] = (elv2_f << 4) | elv2_h;
	txdata[2] = temp;
	txdata[3] = error;
	txdata[4] = temp;
	if (move_1 == 1)
		txdata[5] = (error << 4) | 1;
	else if (move_2 == 2)
		txdata[5] = (error << 4) | 2;
	else
		txdata[5] = (error << 4) | moved;
	
	send_data();	
}

void wave()
{
	trig_on;
	_delay_us(10);
	trig_off;
	_delay_ms(10);
	
	if (dis < 1)
	{
		error_flag = 2;
		buz_flag = 1;
		error = 2;
		read_data();
	}
	else if (c_flag == 1 && (((bit_is_clear(PINA,7))) || (bit_is_clear(PINB,7) && elv1_h >= 1) && (move_1 == 1)))
	{
		error_flag = 2;
		buz_flag = 1;
		error = 2;
		read_data();
	}
	else if (c_flag == 1 && (((bit_is_clear(PINA,7))) || (bit_is_clear(PINB,7) && elv2_h >= 1) && (move_2 == 1)))
	{
		error_flag = 2;
		buz_flag = 1;
		error = 2;
		read_data();
	}
	else 
	{
		error_flag = 0;
		buz_flag = 0;
		error = 0;
		BUZ_OFF;
		read_data();
	}
	dis = 0;
}

void sw_scan()
{
	sw = 20;
	
	if (bit_is_clear(PIND,0))
		sw = 0;
	else if (bit_is_clear(PIND,1))
		sw = 1;
	else if (bit_is_clear(PIND,2))
		sw = 2;
	else if (bit_is_clear(PINE,0))
		sw = 3;
	else if (bit_is_clear(PIND,4))
		sw = 4;
	else if (bit_is_clear(PINE,1))
		sw = 5;
	else if (bit_is_clear(PINE,2))
		sw = 6;
	else if (bit_is_clear(PINE,3))
		sw = 7;
	else if (bit_is_clear(PINE,4))
		sw = 8;
	else if (bit_is_clear(PINE,5))
		sw = 9;
	
	if (led_arr[sw] == 1)
		sw = 20;
	else
		led_arr[sw] = 1;
}

void led_scan()
{	
	read_data();

	if (move_1 == 1)
	{
		if (elv1_c == 0)
		{
			if ((led_arr[5] == 1) && (elv1_f > 2))
				goal = 5;
			else if ((led_arr[6] == 1) && (elv1_f > 3))
				goal = 6;
			else if ((led_arr[7] == 1) && (elv1_f > 4))
				goal = 7;
			else if ((led_arr[8] == 1) && (elv1_f > 5))
				goal = 8;
			else if ((led_arr[9] == 1) && (elv1_f > 6))
				goal = 9;
				
			if ((led_arr[9] == 1) && (elv1_f < 6))
				temp_goal = 9;
			else if ((led_arr[8] == 1) && (elv1_f < 5))
				temp_goal = 8;
			else if ((led_arr[7] == 1) && (elv1_f < 4))
				temp_goal = 7;
			else if ((led_arr[6] == 1) && (elv1_f < 3))
				temp_goal = 6;
			else if ((led_arr[5] == 1) && (elv1_f < 2))
				temp_goal = 5;
				
			if (((led_arr[15] == 1)) && (elv1_f <= 6))
				goal = 15;
			else if ((led_arr[14] == 1) && (elv1_f <= 5))
				goal = 14;
			else if ((led_arr[4] == 1) && (elv1_f <= 5))
				goal = 4;
			else if ((led_arr[13] == 1) && (elv1_f <= 4))
				goal = 13;
			else if ((led_arr[3] == 1) && (elv1_f <= 4))
				goal = 3;
			else if ((led_arr[12] == 1) && (elv1_f <= 3))
				goal = 12;
			else if ((led_arr[2] == 1) && (elv1_f <= 3))
				goal = 2;
			else if ((led_arr[11] == 1) && (elv1_f <= 2))
				goal = 11;
			else if ((led_arr[1] == 1) && (elv1_f <= 2))
				goal = 1;
			else if ((led_arr[10] == 1) && (elv1_f <= 1))
				goal = 10;
			else if ((led_arr[0] == 1) && (elv1_f <= 1))
				goal = 0;
			
			if (((led_arr[10] == 1)) && (elv1_f <= 1))
				temp_goal = 10;
			else if ((led_arr[0] == 1) && (elv1_f <= 1))
				temp_goal = 0;
			else if ((led_arr[11] == 1) && (elv1_f <= 2))
				temp_goal = 11;
			else if ((led_arr[1] == 1) && (elv1_f <= 2))
				temp_goal = 1;
			else if ((led_arr[12] == 1) && (elv1_f <= 3))
				temp_goal = 12;
			else if ((led_arr[2] == 1) && (elv1_f <= 3))
				temp_goal = 2;
			else if ((led_arr[13] == 1) && (elv1_f <= 4))
				temp_goal = 13;
			else if ((led_arr[3] == 1) && (elv1_f <= 4))
				temp_goal = 3;
			else if ((led_arr[14] == 1) && (elv1_f <= 5))
				temp_goal = 14;
			else if ((led_arr[4] == 1) && (elv1_f <= 5))
				temp_goal = 4;
			else if ((led_arr[15] == 1) && (elv1_f <= 6))
				temp_goal = 15;

			if (goal == temp_goal)
				temp_goal = 20;
		}
		////////////////////////////////////////////////////////////////////////////////////////
		else if (elv1_c == 1)
		{
			if ((led_arr[4] == 1) && (elv1_f < 5))
				goal = 4;
			else if ((led_arr[3] == 1) && (elv1_f < 4))
				goal = 3;
			else if ((led_arr[2] == 1) && (elv1_f < 3))
				goal = 2;
			else if ((led_arr[1] == 1) && (elv1_f < 2))
				goal = 1;
			else if ((led_arr[0] == 1) && (elv1_f < 1))
				goal = 0;
			
			if ((led_arr[0] == 1) && (elv1_f > 1))
				temp_goal = 0;
			else if ((led_arr[1] == 1) && (elv1_f > 2))
				temp_goal = 1;
			else if ((led_arr[2] == 1) && (elv1_f > 3))
				temp_goal = 2;
			else if ((led_arr[3] == 1) && (elv1_f > 4))
				temp_goal = 3;
			else if ((led_arr[4] == 1) && (elv1_f > 5))
				temp_goal = 4;	

			if (((led_arr[10] == 1)) && (elv1_f >= 1))
				goal = 10;
			else if ((led_arr[11] == 1) && (elv1_f >= 2))
				goal = 11;
			else if ((led_arr[5] == 1) && (elv1_f >= 2))
				goal = 5;
			else if ((led_arr[12] == 1) && (elv1_f >= 3))
				goal = 12;
			else if ((led_arr[6] == 1) && (elv1_f >= 3))
				goal = 6;
			else if ((led_arr[13] == 1) && (elv1_f >= 4))
				goal = 13;
			else if ((led_arr[7] == 1) && (elv1_f >= 4))
				goal = 7;
			else if ((led_arr[14] == 1) && (elv1_f >= 5))
				goal = 14;
			else if ((led_arr[8] == 1) && (elv1_f >= 5))
				goal = 8;
			else if ((led_arr[15] == 1) && (elv1_f >= 6))
				goal = 15;
			else if ((led_arr[9] == 1) && (elv1_f >= 6))
				goal = 9;
			
			if (((led_arr[15] == 1)) && (elv1_f >= 6))
				temp_goal = 15;
			else if ((led_arr[9] == 1) && (elv1_f >= 6))
				temp_goal = 9;
			else if ((led_arr[14] == 1) && (elv1_f >= 5))
				temp_goal = 14;
			else if ((led_arr[8] == 1) && (elv1_f >= 5))
				temp_goal = 8;
			else if ((led_arr[13] == 1) && (elv1_f >= 4))
				temp_goal = 13;
			else if ((led_arr[7] == 1) && (elv1_f >= 4))
				temp_goal = 7;
			else if ((led_arr[12] == 1) && (elv1_f >= 3))
				temp_goal = 12;
			else if ((led_arr[6] == 1) && (elv1_f >= 3))
				temp_goal = 6;
			else if ((led_arr[11] == 1) && (elv1_f >= 2))
				temp_goal = 11;
			else if ((led_arr[5] == 1) && (elv1_f >= 2))
				temp_goal = 5;
			else if ((led_arr[10] == 1) && (elv1_f >= 1))
				temp_goal = 10;
			
			if (goal == temp_goal)
				temp_goal = 20;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////
	else if (move_2 == 1)
	{
		if (elv2_c == 0)
		{
			if ((led_arr[5] == 1) && (elv2_f > 2))
				goal = 5;
			else if ((led_arr[6] == 1) && (elv2_f > 3))
				goal = 6;
			else if ((led_arr[7] == 1) && (elv2_f > 4))
				goal = 7;
			else if ((led_arr[8] == 1) && (elv2_f > 5))
				goal = 8;
			else if ((led_arr[9] == 1) && (elv2_f > 6))
				goal = 9;
						
			if ((led_arr[9] == 1) && (elv2_f < 6))
				temp_goal = 9;
			else if ((led_arr[8] == 1) && (elv2_f < 5))
				temp_goal = 8;
			else if ((led_arr[7] == 1) && (elv2_f < 4))
				temp_goal = 7;
			else if ((led_arr[6] == 1) && (elv2_f < 3))
				temp_goal = 6;
			else if ((led_arr[5] == 1) && (elv2_f < 2))
				temp_goal = 5;
			
			if (((led_arr[15] == 1)) && (elv2_f <= 6))
				goal = 15;
			else if ((led_arr[14] == 1) && (elv2_f <= 5))
				goal = 14;
			else if ((led_arr[4] == 1) && (elv2_f <= 5))
				goal = 4;
			else if ((led_arr[13] == 1) && (elv2_f <= 4))
				goal = 13;
			else if ((led_arr[3] == 1) && (elv2_f <= 4))
				goal = 3;
			else if ((led_arr[12] == 1) && (elv2_f <= 3))
				goal = 12;
			else if ((led_arr[2] == 1) && (elv2_f <= 3))
				goal = 2;
			else if ((led_arr[11] == 1) && (elv2_f <= 2))
				goal = 11;
			else if ((led_arr[1] == 1) && (elv2_f <= 2))
				goal = 1;
			else if ((led_arr[10] == 1) && (elv2_f <= 1))
				goal = 10;
			else if ((led_arr[0] == 1) && (elv2_f <= 1))
				goal = 0;
						
			if (((led_arr[10] == 1)) && (elv2_f <= 1))
				temp_goal = 10;
			else if ((led_arr[0] == 1) && (elv2_f <= 1))
				temp_goal = 0;
			else if ((led_arr[11] == 1) && (elv2_f <= 2))
				temp_goal = 11;
			else if ((led_arr[1] == 1) && (elv2_f <= 2))
				temp_goal = 1;
			else if ((led_arr[12] == 1) && (elv2_f <= 3))
				temp_goal = 12;
			else if ((led_arr[2] == 1) && (elv2_f <= 3))
				temp_goal = 2;
			else if ((led_arr[13] == 1) && (elv2_f <= 4))
				temp_goal = 13;
			else if ((led_arr[3] == 1) && (elv2_f <= 4))
				temp_goal = 3;
			else if ((led_arr[14] == 1) && (elv2_f <= 5))
				temp_goal = 14;
			else if ((led_arr[4] == 1) && (elv2_f <= 5))
				temp_goal = 4;
			else if ((led_arr[15] == 1) && (elv2_f <= 6))
				temp_goal = 15;
						
			if (goal == temp_goal)
				temp_goal = 20;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////
		else if (elv2_c == 1)
		{
			if ((led_arr[4] == 1) && (elv2_f < 5))
				goal = 4;
			else if ((led_arr[3] == 1) && (elv2_f < 4))
				goal = 3;
			else if ((led_arr[2] == 1) && (elv2_f < 3))
				goal = 2;
			else if ((led_arr[1] == 1) && (elv2_f < 2))
				goal = 1;
			else if ((led_arr[0] == 1) && (elv2_f < 1))
				goal = 0;
			
			if ((led_arr[0] == 1) && (elv2_f > 1))
				temp_goal = 0;
			else if ((led_arr[1] == 1) && (elv2_f > 2))
				temp_goal = 1;
			else if ((led_arr[2] == 1) && (elv2_f > 3))
				temp_goal = 2;
			else if ((led_arr[3] == 1) && (elv2_f > 4))
				temp_goal = 3;
			else if ((led_arr[4] == 1) && (elv2_f > 5))
				temp_goal = 4;

			if (((led_arr[10] == 1)) && (elv2_f >= 1))
				goal = 10;
			else if ((led_arr[11] == 1) && (elv2_f >= 2))
				goal = 11;
			else if ((led_arr[5] == 1) && (elv2_f >= 2))
				goal = 5;
			else if ((led_arr[12] == 1) && (elv2_f >= 3))
				goal = 12;
			else if ((led_arr[6] == 1) && (elv2_f >= 3))
				goal = 6;
			else if ((led_arr[13] == 1) && (elv2_f >= 4))
				goal = 13;
			else if ((led_arr[7] == 1) && (elv2_f >= 4))
				goal = 7;
			else if ((led_arr[14] == 1) && (elv2_f >= 5))
				goal = 14;
			else if ((led_arr[8] == 1) && (elv2_f >= 5))
				goal = 8;
			else if ((led_arr[15] == 1) && (elv2_f >= 6))
				goal = 15;
			else if ((led_arr[9] == 1) && (elv2_f >= 6))
				goal = 9;
			
			if (((led_arr[15] == 1)) && (elv2_f >= 6))
				temp_goal = 15;
			else if ((led_arr[9] == 1) && (elv2_f >= 6))
				temp_goal = 9;
			else if ((led_arr[14] == 1) && (elv2_f >= 5))
				temp_goal = 14;
			else if ((led_arr[8] == 1) && (elv2_f >= 5))
				temp_goal = 8;
			else if ((led_arr[13] == 1) && (elv2_f >= 4))
				temp_goal = 13;
			else if ((led_arr[7] == 1) && (elv2_f >= 4))
				temp_goal = 7;
			else if ((led_arr[12] == 1) && (elv2_f >= 3))
				temp_goal = 12;
			else if ((led_arr[6] == 1) && (elv2_f >= 3))
				temp_goal = 6;
			else if ((led_arr[11] == 1) && (elv2_f >= 2))
				temp_goal = 11;
			else if ((led_arr[5] == 1) && (elv2_f >= 2))
				temp_goal = 5;
			else if ((led_arr[10] == 1) && (elv2_f >= 1))
				temp_goal = 10;
			
			if (goal == temp_goal)
				temp_goal = 20;
		}
	}
}

void sw_interrupt()
{
	sw_scan();	
	key_matrix();
}

void elv1_up()
{
	oled_clear3();
	write_number3(55,elv1_f);
	write_number1(55,elv1_f);
	up(100,1,0,1);
	elv1_f++;
	read_data();
	led_scan();
}

void elv1_down()
{
	oled_clear3();
	write_number3(55,elv1_f);
	write_number1(55,elv1_f);
	down(100,1,0,1);
	elv1_f--;
	read_data();
	led_scan();
}

void elv1_open()
{
	oled_clear3();
	write_number1(55,elv1_f);
	write_number3(55,elv1_f);
	BUZ_ON;
	open_door3(elv1_f);
	BUZ_OFF;
	od_flag = 1;
	for (t = 0; t < 2000;)
	{
		wave();
		key_matrix();
		if (close_flag == 1 )
		{
			close_flag = 0;
			led_arr[18] = 1;
			break;
		}
		if (bit_is_clear(PINA,7) && input_flag == 0)
		{
			input_flag = 1;
			if (elv1_h < 11)
				elv1_h++;
		}
		if (bit_is_clear(PINB,7) && input_flag == 0)
		{
			input_flag = 2;
			if (elv1_h > 0)
				elv1_h--;
		}
		if (input_flag == 1 && bit_is_set(PINA,7))
			input_flag = 0;
		else if (input_flag == 2 && bit_is_set(PINB,7))
			input_flag = 0;
		if (elv1_h > 5)
		{
			error = 4;
			buz_flag = 1;
			error_flag = 4;
			break;
		}
		read_data();
		cd_flag = 1;
	}
	while (error_flag == 4)
	{
		if (bit_is_clear(PINA,7))
		{
			while(bit_is_clear(PINA,7));
			if (elv1_h < 11)
				elv1_h++;
		}
		if (bit_is_clear(PINB,7))
		{
			while(bit_is_clear(PINB,7));
			if (elv1_h > 0)
				elv1_h--;
		}
		if (elv1_h <= 5)
		{
			error_flag = 0;
			error = 0;
			buz_flag = 0;
		}
		read_data();
	}
	c_flag = 1;
	close_door3(elv1_f);
	c_flag = 0;
	BUZ_OFF;
	od_flag = 0;
	cd_flag = 0;
	close_flag = 0;
	led_arr[18] = 0;
	led_arr[17] = 0;
	open_flag = 0;

}

void elv2_up()
{
	oled_clear3();
	write_number3(55,elv2_f);
	write_number2(55,elv2_f);
	up(100,0,1,1);
	elv2_f++;
	read_data();
	led_scan();
}

void elv2_down()
{
	oled_clear3();
	write_number3(55,elv2_f);
	write_number2(55,elv2_f);
	down(100,0,1,1);
	elv2_f--;
	read_data();
	led_scan();
}

void elv2_open()
{
	led_scan();
	oled_clear3();
	write_number2(55,elv2_f);
	write_number3(55,elv2_f);
	BUZ_ON;
	open_door3(elv2_f);
	BUZ_OFF;
	od_flag = 1;
	for (t = 0; t < 2000;)
	{
		wave();
		key_matrix();
		if (close_flag == 1 )
		{
			close_flag = 0;
			led_arr[18] = 1;
			break;
		}
		if (bit_is_clear(PINA,7) && input_flag == 0)
		{
			input_flag = 1;
			if (elv2_h < 11)
				elv2_h++;
		}
		if (bit_is_clear(PINB,7) && input_flag == 0)
		{
			input_flag = 2;
			if (elv2_h > 0)
				elv2_h--;
		}
		if (input_flag == 1 && bit_is_set(PINA,7))
			input_flag = 0;
		else if (input_flag == 2 && bit_is_set(PINB,7))
			input_flag = 0;
		if (elv2_h > 5)
		{
			error = 4;
			buz_flag = 1;
			error_flag = 4;
			break;
		}
		read_data();
		cd_flag = 1;
	}
	while (error_flag == 4)
	{
		if (bit_is_clear(PINA,7))
		{
			while(bit_is_clear(PINA,7));
			if (elv2_h < 11)
				elv2_h++;
		}
		if (bit_is_clear(PINB,7))
		{
			while(bit_is_clear(PINB,7));
			if (elv2_h > 0)
				elv2_h--;
		}
		if (elv2_h <= 5)
		{
			error_flag = 0;
			error = 0;
			buz_flag = 0;
		}
		read_data();
	}
	c_flag = 1;
	close_door3(elv2_f);
	c_flag = 0;
	BUZ_OFF;
	od_flag = 0;
	cd_flag = 0;
	close_flag = 0;
	led_arr[18] = 0;
	led_arr[17] = 0;
	open_flag = 0;
}

void move(int elv)
{
	int goal_flag = 1;
	int num;
	scan_flag = 1;
	
	while(goal_flag)
	{
		if (temp_goal == 20)
			distance(goal);
		else
			distance(temp_goal);
		
		if (error_flag == 1)
		{
			if (move_1 == 1)
			{
				write_number1(55,elv1_f);
				open_door3(elv1_f);
			}
			else if (move_2 == 1)
			{
				write_number2(55,elv2_f);
				open_door3(elv2_f);
			}
			stop_flag = 1;
			while(error_flag == 1)
			{
				led_arr[16] = 1;
				buz_flag = 1;
				error = 1;
				read_data();
				key_matrix();
				if (error_flag == 0)
				{
					error = 0;
					led_arr[16] = 0;
					buz_flag = 0;
					BUZ_OFF;
					if (move_1 == 1)
					{
						close_door3(elv1_f);
						error_flag = 0;
						stop_flag = 0;
					}
					else if (move_2 == 1)
					{
						close_door3(elv2_f);
						error_flag = 0;
						stop_flag = 0;
					}
					read_data();
				}
			}
		}
		else if (temp > 40)
		{
			error_flag = 3;
			buz_flag = 1;
			error = 3;
			if (move_1 == 1)
			{
				write_number1(55,elv1_f);
				open_door3(elv1_f);
			}
			else if (move_2 == 1)
			{
				write_number2(55,elv2_f);
				open_door3(elv2_f);
			}
			while(temp > 40)
			{
				read_data();
				if (move_1 == 1)
				{
					write_number1(55,elv1_f);
					write_number3(55,elv1_f);
				}
				else if (move_2 == 1)
				{
					write_number2(55,elv2_f);
					write_number3(55,elv2_f);
				}
			}
			buz_flag = 0;
			error = 0;
			BUZ_OFF;
			if (move_1 == 1)
			{
				close_door3(elv1_f);
				error_flag = 0;
			}
			else if (move_2 == 1)
			{
				close_door3(elv2_f);
				error_flag = 0;
			}
			read_data();
		}
		////////////////////////////////////////////////////////////
		else if (elv == 1)
		{
			move_1 = 1;
			
			if (temp_goal == 20)
			{
				if (goal == 0 || goal == 10)
				{
					if (elv1_f < 1)
						elv1_up();
					else if (elv1_f > 1)
						elv1_down();
					else if (elv1_f == 1)
					{
						elv1_open();
						if (goal == 10 && elv1_h >= 1)
						{
							led_arr[10] = 0;
							if (elv1_c == 0)
								led_arr[0] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
				else if (goal == 1 || goal == 5 || goal == 11)
				{
					if (elv1_f < 2)
						elv1_up();
					else if (elv1_f > 2)
						elv1_down();
					else if (elv1_f == 2)
					{
						elv1_open();
						if (goal == 11 && elv1_h >= 1)
						{
							led_arr[11] = 0;
							if (elv1_c == 0)
								led_arr[1] = 0;
							else if (elv1_c == 1)
								led_arr[5] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
				else if (goal == 2 || goal == 6 || goal == 12)
				{
					if (elv1_f < 3)
						elv1_up();
					else if (elv1_f > 3)
						elv1_down();
					else if (elv1_f == 3)
					{
						elv1_open();
						if (goal == 12 && elv1_h >= 1)
						{
							led_arr[12] = 0;
							if (elv1_c == 0)
								led_arr[2] = 0;
							else if (elv1_c == 1)
								led_arr[6] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
				else if (goal == 3 || goal == 7 || goal == 13)
				{
					if (elv1_f < 4)
						elv1_up();
					else if (elv1_f > 4)
						elv1_down();
					else if (elv1_f == 4)
					{
						elv1_open();
						if (goal == 13 && elv1_h >= 1)
						{
							led_arr[13] = 0;
							if (elv1_c == 0)
								led_arr[3] = 0;
							else if (elv1_c == 1)
								led_arr[7] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
				else if (goal == 4 || goal == 8 || goal == 14)
				{
					if (elv1_f < 5)
						elv1_up();
					else if (elv1_f > 5)
						elv1_down();
					else if (elv1_f == 5)
					{
						elv1_open();
						if (goal == 14 && elv1_h >= 1)
						{
							led_arr[14] = 0;
							if (elv1_c == 0)
								led_arr[4] = 0;
							else if (elv1_c == 1)
								led_arr[8] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
				else if (goal == 9 || goal == 15)
				{
					if (elv1_f < 6)
						elv1_up();
					else if (elv1_f > 6)
						elv1_down();
					else if (elv1_f == 6)
					{
						elv1_open();
						if (goal == 15 && elv1_h >= 1)
						{
							led_arr[15] = 0;
							if (elv1_c == 1)
								led_arr[9] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
			}
			////////////////////////////////////////////////////////////////////////////////
			else if (temp_goal != 20)
			{
				if (temp_goal == 0 || temp_goal == 10)
				{
					if (elv1_f < 1)
						elv1_up();
					else if (elv1_f > 1)
						elv1_down();
					else if (elv1_f == 1)
					{
						elv1_open();
						if (temp_goal == 10 && elv1_h >= 1)
						{
							led_arr[10] = 0;
							if (elv1_c == 0)
								led_arr[0] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
				else if (temp_goal == 1 || temp_goal == 5 || temp_goal == 11)
				{
					if (elv1_f < 2)
						elv1_up();
					else if (elv1_f > 2)
						elv1_down();
					else if (elv1_f == 2)
					{
						elv1_open();
						if (temp_goal == 11 && elv1_h >= 1)
						{
							led_arr[11] = 0;
							if (elv1_c == 0)
								led_arr[1] = 0;
							else if (elv1_c == 1)
								led_arr[5] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
				else if (temp_goal == 2 || temp_goal == 6 || temp_goal == 12)
				{
					if (elv1_f < 3)
						elv1_up();
					else if (elv1_f > 3)
						elv1_down();
					else if (elv1_f == 3)
					{
						elv1_open();
						if (temp_goal == 12 && elv1_h >= 1)
						{
							led_arr[12] = 0;
							if (elv1_c == 0)
								led_arr[2] = 0;
							else if (elv1_c == 1)
								led_arr[6] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
				else if (temp_goal == 3 || temp_goal == 7 || temp_goal == 13)
				{
					if (elv1_f < 4)
						elv1_up();
					else if (elv1_f > 4)
						elv1_down();
					else if (elv1_f == 4)
					{
						elv1_open();
						if (temp_goal == 13 && elv1_h >= 1)
						{
							led_arr[13] = 0;
							if (elv1_c == 0)
								led_arr[3] = 0;
							else if (elv1_c == 1)
								led_arr[7] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
				else if (temp_goal == 4 || temp_goal == 8 || temp_goal == 14)
				{
					if (elv1_f < 5)
						elv1_up();
					else if (elv1_f > 5)
						elv1_down();
					else if (elv1_f == 5)
					{
						elv1_open();
						if (temp_goal == 14 && elv1_h >= 1)
						{
							led_arr[14] = 0;
							if (elv1_c == 0)
								led_arr[4] = 0;
							else if (elv1_c == 1)
								led_arr[8] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
				else if (temp_goal == 9 || temp_goal == 15)
				{
					if (elv1_f < 6)
						elv1_up();
					else if (elv1_f > 6)
						elv1_down();
					else if (elv1_f == 6)
					{
						elv1_open();
						if (temp_goal == 15 && elv1_h >= 1)
						{
							led_arr[15] = 0;
							if (elv1_c == 1)
								led_arr[9] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////
		else if (elv == 2)
		{
			move_2 = 1;
			if (temp_goal == 20)
			{
				if (goal == 0 || goal == 10)
				{
					if (elv2_f < 1)
						elv2_up();
					else if (elv2_f > 1)
						elv2_down();
					else if (elv2_f == 1)
					{
						elv2_open();
						if (goal == 10 && elv2_h >= 1)
						{
							led_arr[10] = 0;
							if (elv1_c == 0)
								led_arr[0] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
				else if (goal == 1 || goal == 5 || goal == 11)
				{
					if (elv2_f < 2)
						elv2_up();
					else if (elv2_f > 2)
						elv2_down();
					else if (elv2_f == 2)
					{
						elv2_open();
						if (goal == 11 && elv2_h >= 1)
						{
							led_arr[11] = 0;
							if (elv1_c == 0)
								led_arr[1] = 0;
							else if (elv1_c == 1)
								led_arr[5] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
				else if (goal == 2 || goal == 6 || goal == 12)
				{
					if (elv2_f < 3)
						elv2_up();
					else if (elv2_f > 3)
						elv2_down();
					else if (elv2_f == 3)
					{
						elv2_open();
						if (goal == 12 && elv2_h >= 1)
						{
							led_arr[12] = 0;
							if (elv1_c == 0)
								led_arr[2] = 0;
							else if (elv1_c == 1)
								led_arr[6] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
				else if (goal == 3 || goal == 7 || goal == 13)
				{
					if (elv2_f < 4)
						elv2_up();
					else if (elv2_f > 4)
						elv2_down();
					else if (elv2_f == 4)
					{
						elv2_open();
						if (goal == 13 && elv2_h >= 1)
						{
							led_arr[13] = 0;
							if (elv1_c == 0)
								led_arr[3] = 0;
							else if (elv1_c == 1)
								led_arr[7] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
				else if (goal == 4 || goal == 8 || goal == 14)
				{
					if (elv2_f < 5)
						elv2_up();
					else if (elv2_f > 5)
						elv2_down();
					else if (elv2_f == 5)
					{
						elv2_open();
						if (goal == 14 && elv2_h >= 1)
						{
							led_arr[14] = 0;
							if (elv1_c == 0)
								led_arr[4] = 0;
							else if (elv1_c == 1)
								led_arr[8] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
				else if (goal == 9 || goal == 15)
				{
					if (elv2_f < 6)
						elv2_up();
					else if (elv2_f > 6)
						elv2_down();
					else if (elv2_f == 6)
					{
						elv2_open();
						if (goal == 15 && elv2_h >= 1)
						{
							led_arr[15] = 0;
							if (elv1_c == 1)
								led_arr[9] = 0;
						}
						else
							led_arr[goal] = 0;
						goal_flag = 0;
						led_scan();
					}
				}
			}
			/////////////////////////////////////////////////////////////////////////////////
			else if (temp_goal != 20)
			{
				if (temp_goal == 0 || temp_goal == 10)
				{
					if (elv2_f < 1)
						elv2_up();
					else if (elv2_f > 1)
						elv2_down();
					else if (elv2_f == 1)
					{
						elv2_open();
						if (temp_goal == 10 && elv2_h >= 1)
						{
							led_arr[10] = 0;
							if (elv2_c == 0)
								led_arr[0] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
				else if (temp_goal == 1 || temp_goal == 5 || temp_goal == 11)
				{
					if (elv2_f < 2)
						elv2_up();
					else if (elv2_f > 2)
						elv2_down();
					else if (elv2_f == 2)
					{
						elv2_open();
						if (temp_goal == 11 && elv2_h >= 1)
						{
							led_arr[11] = 0;
							if (elv2_c == 0)
								led_arr[1] = 0;
							else if (elv2_c == 1)
								led_arr[5] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
				else if (temp_goal == 2 || temp_goal == 6 || temp_goal == 12)
				{
					if (elv2_f < 3)
						elv2_up();
					else if (elv2_f > 3)
						elv2_down();
					else if (elv2_f == 3)
					{
						elv2_open();
						if (temp_goal == 12 && elv2_h >= 1)
						{
							led_arr[12] = 0;
							if (elv2_c == 0)
								led_arr[2] = 0;
							else if (elv2_c == 1)
								led_arr[6] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
				else if (temp_goal == 3 || temp_goal == 7 || temp_goal == 13)
				{
					if (elv2_f < 4)
						elv2_up();
					else if (elv2_f > 4)
						elv2_down();
					else if (elv2_f == 4)
					{
						elv2_open();
						if (temp_goal == 13 && elv2_h >= 1)
						{
							led_arr[13] = 0;
							if (elv2_c == 0)
								led_arr[3] = 0;
							else if (elv2_c == 1)
								led_arr[7] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
				else if (temp_goal == 4 || temp_goal == 8 || temp_goal == 14)
				{
					if (elv2_f < 5)
						elv2_up();
					else if (elv2_f > 5)
						elv2_down();
					else if (elv2_f == 5)
					{
						elv2_open();
						if (temp_goal == 14 && elv2_h >= 1)
						{
							led_arr[14] = 0;
							if (elv2_c == 0)
								led_arr[4] = 0;
							else if (elv2_c == 1)
								led_arr[8] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
				else if (temp_goal == 9 || temp_goal == 15)
				{
					if (elv2_f < 6)
						elv2_up();
					else if (elv2_f > 6)
						elv2_down();
					else if (elv2_f == 6)
					{
						elv2_open();
						if (temp_goal == 15 && elv2_h >= 1)
						{
							led_arr[15] = 0;
							if (elv2_c == 1)
								led_arr[9] = 0;
						}
						else
							led_arr[temp_goal] = 0;
						temp_goal = 20;
						led_scan();
					}
				}
			}
		}	
	}
	if (move_1 == 1)
		moved = 1;
	else if (move_2 == 1)
		moved = 2;
	move_1 = 0;
	move_2 = 0;
	check_flag = 0;
	scan_flag = 0;
}

void distance(int n)
{
	int num = 0;
	
	if (n == 0 || n == 10)
		num = 1;
	else if (n == 1 || n == 5 || n == 11)
		num = 2;
	else if (n == 2 || n == 6 || n == 12)
		num = 3;
	else if (n ==3 || n == 7 || n == 13)
		num = 4;
	else if (n == 4 || n == 8 || n == 14)
		num = 5;
	else if (n == 9 || n == 15)
		num = 6;
	
		if (elv1_f-num > 0)
		{
			elv1_d = elv1_f-num;
			elv1_c = 1;
		}
		else if (elv1_f-num < 0)
		{
			elv1_d = num-elv1_f;
			elv1_c = 0;
		}
		else if (elv1_f-num == 0)
		{
			if (n >= 0 && n <= 4)
			{
				elv1_d = 0;
				elv1_c = 0;
			}
			else if (n >= 5 && n <= 9)
			{
				elv1_d = 0;
				elv1_c = 1;
			}
		}
		if (elv2_f-num > 0)
		{
			elv2_d = elv2_f-num;
			elv2_c = 1;
		}
		else if (elv2_f-num < 0)
		{
			elv2_d = num-elv2_f;
			elv2_c = 0;
		}
		else if (elv2_f-num == 0)
		{
			if (n >= 0 && n <= 4)
			{
				elv2_d = 0;
				elv2_c = 0;
			}
			else if (n >= 5 && n <= 9)
			{
				elv2_d = 0;
				elv2_c = 1;
			}
		}
}

void priority()
{
	int flag = 1;
	int ledled = 20;
	
	if (led_arr[16] == 1)
	{
		stop_flag = 1;
		error_flag = 1;
		if (moved == 1)
		{
			write_number1(55,elv1_f);
			open_door3(elv1_f);
		}
		else if (moved == 2)
		{
			write_number2(55,elv2_f);
			open_door3(elv2_f);
		}
		while(error_flag == 1)
		{
			led_arr[16] = 1;
			buz_flag = 1;
			error = 1;
			read_data();
			key_matrix();
			if (error_flag == 0)
			{
				error = 0;
				led_arr[16] = 0;
				buz_flag = 0;
				BUZ_OFF;
				if (moved == 1)
				{
					close_door3(elv1_f);
					error_flag = 0;
					stop_flag = 0;
				}
				else if (moved == 2)
				{
					close_door3(elv2_f);
					error_flag = 0;
					stop_flag = 0;
				}
				read_data();
			}
		}
	}
	read_data();
	
	for (int i = 10; i < 16; i++)
	{
		if (led_arr[i] == 1)
		{
			ledled = i;
			break;
		}
	}
	
	if (ledled == 20)
	{
		for (int i = 0; i < 10; i++)
		{
			if (led_arr[i] == 1)
			{
				ledled = i;
				break;
			}
		}
	}
	
	if (sw != 20 || key != 20 || ledled != 20)
	{
		if (sw != 20)
			goal = sw;
		else if (key != 20)
			goal = key;
		else if (ledled != 20)
			goal = ledled;
			
		led_scan();
		
		while(flag)
		{
			distance(goal);
			
			if (goal >= 10 && goal <= 15)
			{
				if (moved == 0)
				{
					if (elv1_h >= 1)
					move(1);
					else if (elv2_h >= 1)
					move(2);
				}
				else if (moved == 1 && elv1_h >= 1)
					move(1);
				else if (moved == 2 && elv2_h >= 1)
					move(2);
			}
			else if (elv1_f == elv2_f)
				move(1);
			else if (elv1_d == elv2_d)
			{
				if (goal == 0 || goal == 1 || goal == 2 || goal == 3 || goal == 4)
				{
					if (elv1_f > elv2_f)
						move(2);
					else
						move(1);
				}
				else if (goal == 5 || goal == 6 || goal == 7 || goal == 8 || goal == 9)
				{
					if (elv1_f > elv2_f)
						move(1);
					else
						move(2);
				}
			}
			else if (elv1_d < elv2_d)
				move(1);
			else if (elv1_d > elv2_d)
				move(2);
			flag = 0;
		}
	}
}

int main(void)
{
	init();
	
	start_display();
	
    while (1) 
    {
		write_number1(55,elv1_f);
		write_number2(55,elv2_f);
		read_data();
		sw_scan();
		key_matrix();
		priority();	

		
		//closed_door1();
			
		//open_door1
		//close_door1
		//oled_clear1
		//oled_fill1
		//up
		//down
		//write_number1
		//clear_number
		//closed_door
    }
}