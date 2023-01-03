/*
* Lab3.c  -- Displays the temperature in Farenheit when a button is not pressed.
          -- When the button is pressed the temperature is displayed in Celsius.
          -- Will display the temperature to 3 significant figures with a precision 
          -- of 0.1 degrees, followed by the letter C or F.
* Date          Author              Revision
*4/3/22         Jordan Andrade      initial code creation
*/

#include "avr/io.h"
#include "util/delay.h"

int main(void){

    unsigned int digital_value; // all the assigned variables 
    int celsius;
    int celsius_c;
    float farenheit; // takes float value of temp
    int farenheit_c;
    unsigned char DIG1, DIG2, DIG3, DIG4;
    unsigned char ledDigits[] = {0b00111111, 0b0110, 0b01011101, 0b01001111, 0b01100110, 0b01101011,
         0b01111011, 0b00001110, 0b01111111, 0b01101111};

    ADMUX = 0x45;
    ADCSRA = 0x87;
    DDRC = 0x0F;
    DDRD = 0xF0;
    DDRB = 0x1E;
    PORTD = 1<<PORTD2; // set switch as input

    while(1){ // always runs
        ADCSRA |= (1<<ADSC);
        while ((ADCSRA &(1<<ADIF)) == 0); // runs till not zero 
        digital_value = ADCL|(ADCH<<8); // gets sensor value

        if ((PIND & (1 << 2)) == 0) {
            celsius = digital_value*0.4883 - 50; // converts to celsius
            celsius_c = celsius*10.; // changes to non decimal value 

            DIG2 = (celsius_c)%10; // gets first digit 
            DIG3 = ((celsius_c)/10)%10; // gets second digit
            DIG4 = ((celsius_c)/100); // gets third digit

            //show C
            PORTC = (PORTC&0xF0)|(0b1001&0x0F);
            PORTD = (0b00110000&0xF0)|(PORTD%0x0F);
            PORTB = ~(1<<4);
            _delay_ms(5);

            //show 1s digit 
            PORTC = (PORTC&0xF0)|(0b0&0x0F);
            PORTD = (ledDigits[DIG2]&0xF0)|(PORTD%0x0F);
            PORTB = ~(1<<3);
            _delay_ms(5);

            //show 10s digit 
            PORTC = (PORTC&0xF0)|(ledDigits[DIG3]&0x0F);
            PORTD = (ledDigits[DIG3]&0xF0)|(0b10000000&0xF0)|(PORTD%0x0F);
            PORTB = ~(1<<2);
            _delay_ms(5);

            //show 100s digit 
            PORTC = (PORTC&0xF0)|(ledDigits[DIG4]&0x0F);
            PORTD = (ledDigits[DIG4]&0xF0)|(PORTD%0x0F);
            PORTB = ~(1<<1);
            _delay_ms(5);
            PORTB = 0xFF;
        }

        else{
            celsius = digital_value*0.4883 - 50; // gets celcius value 
            farenheit = ((celsius*(1.8)) + 32); // converts to farenheit
            farenheit_c = farenheit *10; // gets non decimal value

            DIG2 = (farenheit_c)%10; // gets first digit
            DIG3 = ((farenheit_c)/10)%10; // gets second digit
            DIG4 = ((farenheit_c)/100); // gets third digit
            
            //show F
            PORTC = (PORTC&0xF0)|(0b1000&0x0F);
            PORTD = (0b01110000&0xF0)|(PORTD%0x0F);
            PORTB = ~(1<<4);
            _delay_ms(5);

            //show 1s digit 
            PORTC = (PORTC&0xF0)|(ledDigits[DIG2]&0x0F);
            PORTD = (ledDigits[DIG2]&0xF0)|(PORTD%0x0F);
            PORTB = ~(1<<3);
            _delay_ms(5);

            //show 10s digit 
            PORTC = (PORTC&0xF0)|(ledDigits[DIG3]&0x0F);
            PORTD = (ledDigits[DIG3]&0xF0)|(0b10000000&0xF0)|(PORTD%0x0F);
            //PORTD = (0b01110000&0xF0)|(PORTD%0x0F);
            PORTB = ~(1<<2);
            _delay_ms(5);

            //show 100s digit 
            PORTC = (PORTC&0xF0)|(ledDigits[DIG4]&0x0F);
            PORTD = (ledDigits[DIG4]&0xF0)|(PORTD%0x0F);
            PORTB = ~(1<<1);
            _delay_ms(5);
            PORTB = 0xFF;
            
        }

    }
    return(0);
}