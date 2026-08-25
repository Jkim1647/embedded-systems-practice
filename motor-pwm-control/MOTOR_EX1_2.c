#include <mega128.h>

typedef unsigned char u_char;
flash u_char seg_pat[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
flash u_char seg_on[4] = {0b00001000,0b00000100,0b00000010,0b00000001};

u_char dsp_no = 0;

u_char pwm = 10;
void ocr3a_set();

void main()
{
    DDRB = 0xF0;
    DDRD = 0xF0;
    DDRG = 0x0F;
    DDRE = 0b00001000;
    
    PORTE = 0x00;
    
    EIMSK = 0b00110000;
    EICRB = 0b00001010;
    
    TIMSK = 0b01000000;
    TCCR2 = 0x05;
    TCNT2 = 178;
    
    TCCR3A = 0b10000010;
    TCCR3B = 0x1A;
    TCCR3C = 0x00;
    ICR3H = 0;
    ICR3L = 99;
    
    ocr3a_set();
    SREG = 0x80;
    while(1);
}
interrupt [EXT_INT4] void ext4()
{
    if(pwm < 97)pwm = pwm + 3;
    ocr3a_set();
}
interrupt [EXT_INT5] void ext5()
{
    if(pwm > 3)pwm = pwm - 3;
    ocr3a_set();
}
void ocr3a_set()
{
    OCR3AH = 0;
    OCR3AL = pwm;
}

interrupt [TIM2_OVF] void time2_int()
{
    u_char dsp_val;
    
    TCNT2 = 178;
    PORTG = seg_on[dsp_no];
    
    if(dsp_no == 0)dsp_val = pwm % 10;
    else if(dsp_no == 1) dsp_val = (pwm % 100) / 10;
    else if(dsp_no == 2) dsp_val = pwm / 100;
    
    PORTD = ((seg_pat[dsp_val]&0x0F)<<4)|(PORTD&0x0F);
    PORTB = (seg_pat[dsp_val]&0x70)|(PORTB & 0x0F);
    
    dsp_no = (dsp_no + 1)%3;            
}