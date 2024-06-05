#include <util/delay.h>
#include <usart.c>

#define CLOCK_SPEED 12000000
#define BAUD 28800
#define MYUBRR CLOCK_SPEED/16/BAUD-1

#define MORSE_LUNG  3
#define MORSE_SCURT 1

/* Literele alfabetului in cod Morse */
char* morse_alphabet[] = {
    (char*)"13",    // a
    (char*)"3111",  // b
    (char*)"3131",  // c
    (char*)"311",   // d
    (char*)"1",     // e
    (char*)"1131",  // f
    (char*)"331",	// g
    (char*)"1111",	// h
    (char*)"11",	// i
    (char*)"1333",	// j
    (char*)"313",	// k
    (char*)"1311",	// l
    (char*)"33",	// m
    (char*)"31",	// n
    (char*)"333",	// o
    (char*)"1331",	// p
    (char*)"3313",	// q
    (char*)"131",	// r
    (char*)"111",	// s
    (char*)"3",	    // t
    (char*)"113",	// u
    (char*)"1113",	// v
    (char*)"133",	// w
    (char*)"3113",	// x
    (char*)"3133",	// y
    (char*)"3311"	// z
};

/* apelati functia pentru a obtine un ton lung/scurt,
 * folosind macro-urile MORSE_LUNG si MORSE_SCURT
 */
void speaker_morse(int tip)
{
    int delay = 1;
    int i;
    DDRD |= (1 << PD4);     // PD4 trebuie sa fie output

    for (i = 0; i < tip * 50 / delay; i++)
    {
        PIND = (1 << PD4);  // alternam starea iesirii
        _delay_ms(1);
    }
}

int main() {
	
    USART0_init(MYUBRR);
    
    DDRB &= ~(1 << PB2);
    PORTB |= (1 << PB2);

    DDRD |= (1 << PD7) | (1 << PD5);
    DDRB |= (1 << PB3);

    while (1) {
        /* Verifică dacă butonul 1 (PB2) este apăsat */
        if (!(PINB & (1 << PB2))) {
            USART0_print("Butonul 1 a fost apasat\r\n");
        }

        char command[10];
        int i = 0;

        while(1) {
            char received_char = USART0_receive();
            if (received_char == '\n' || received_char == '\r') {
                command[i] = '\0';  // Adaugă terminatorul de șir
                break;
            }
            command[i++] = received_char;
        }

        USART_exec(command);
    }

 
	return 0;
}