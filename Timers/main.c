#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint16_t contador_ms = 0;
volatile uint16_t limite_tiempo = 500; // Valor inicial

ISR(TIMER1_COMPA_vect)
{
    contador_ms++;
    if (contador_ms >= limite_tiempo) {
        PORTC ^= (1 << PC0);
        contador_ms = 0;
    }
}

int main(void)
{
    // Configurar PC0 como salida (LED)
    DDRC |= (1 << DDC0);

    // Configurar pines del dip como entradas como(PD2 y PD3)
    DDRD &= ~((1 << DDD0) | (1 << DDD1));
    PORTD |= (1 << PORTD0) | (1 << PORTD0);

    // Configuración del Timer 1 en modo CTC
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    OCR1A = 249; 
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11) | (1 << CS10); 
    TIMSK1 |= (1 << OCIE1A);

    sei(); 

    while (1) {
        // Leer el estado del Dip Switch
        uint8_t dip = (PIND & ((1 << PIND0) | (1 << PIND1)));

        // Cambiar la velocidad de parpadeo según la combinación del dip switch
        if (dip == 0) {
            limite_tiempo = 200;  // Velocidad rápida (parpadeo cada 200 ms)
        } else if (dip == (1 << PIND0)) {
            limite_tiempo = 500;  // Velocidad media (parpadeo cada 500 ms)
        } else if (dip == (1 << PIND1)){
            limite_tiempo = 1000; // Velocidad lenta (parpadeo cada 1000 ms)
        }
    }
}