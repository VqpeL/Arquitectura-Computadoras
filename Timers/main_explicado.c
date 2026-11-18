#define F_CPU 16000000UL          // Define la frecuencia del reloj del microcontrolador (16 MHz) para funciones de tiempo.
#include <avr/io.h>               // Incluye la librería de entradas y salidas para reconocer los registros del AVR.
#include <avr/interrupt.h>        // Incluye la librería para el manejo de interrupciones globales y vectores.
#include <stdint.h>               // Incluye la definición de tipos de datos estandarizados (como uint16_t).

volatile uint16_t Contador_ms = 0; // Variable global de 16 bits modificada en la interrupción; 'volatile' evita que el compilador la optimice incorrectamente.

ISR(TIMER1_COMPA_vect)            // Rutina de Servicio de Interrupción (ISR) que se ejecuta automáticamente cuando el Timer 1 coincide con OCR1A.
{
    Contador_ms++;                // Incrementa el contador en 1 cada vez que ocurre la interrupción (diseñada para ser cada 1 ms).
    if(Contador_ms >= 500){       // Comprueba si ya han transcurrido 500 milisegundos (0.5 segundos).
        PORTB ^= (1 << PB5);      // Invierte el estado lógico actual del pin PB5 (enciende o apaga el LED).
        Contador_ms = 0;          // Reinicia el contador de milisegundos para empezar el siguiente ciclo de conteo.
    }
}

int main(void) {                  // Función principal donde arranca la ejecución del programa del microcontrolador.
    DDRB |= (1 << DDB5);          // Configura el pin PB5 (pin 13 en Arduino) como pin de salida digital.
    TCCR1A = 0;                   // Limpia el registro de control A del Timer 1 (modo normal de operación de pines).
    TCCR1B = 0;                   // Limpia el registro de control B del Timer 1 para asegurar un estado inicial limpio.
    TCNT1 = 0;                    // Inicializa el registro contador de 16 bits del Timer 1 en cero.
    OCR1A = 249;                  // Establece el valor de comparación del canal A para generar una interrupción exacta cada 1 ms.
    TCCR1B |= (1 << WGM12);       // Configura el Timer 1 en modo CTC (Clear Timer on Compare Match).
    TCCR1B |= (1 << CS11) | (1 << CS10); // Configura el prescaler del Timer 1 en 64 (inicia el conteo del reloj).
    TIMSK1 |= (1 << OCIE1A);      // Habilita la interrupción por coincidencia de comparación del canal A (OCIE1A).
    sei();                        // Activa globalmente las interrupciones (Set Interrupt Enable).
    
    while(1){                     // Bucle infinito que mantiene el programa corriendo.
        // El microcontrolador se queda libre aquí mientras la interrupción hace el trabajo en segundo plano.
    }
}