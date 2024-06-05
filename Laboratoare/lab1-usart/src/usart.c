#include "usart.h"
#include <string.h>

/*
 * Functie de initializare a controllerului USART
 */
void USART0_init(unsigned int ubrr)
{
    /* seteaza baud rate-ul */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;

    /* porneste transmitatorul */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    /* seteaza formatul frame-ului: 8 biti de date, 2 biti de stop, fara paritate */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}


/*
 * Functie ce transmite un caracter prin USART
 *
 * @param data - caracterul de transmis
 */
void USART0_transmit(char data)
{
    /* asteapta pana bufferul e gol */
    while(!(UCSR0A & (1<<UDRE0)));

    /* pune datele in buffer; transmisia va porni automat in urma scrierii */
    UDR0 = data;
}

/*
 * Functie ce primeste un caracter prin USART
 *
 * @return - caracterul primit
 */
char USART0_receive()
{
    /* asteapta cat timp bufferul e gol */
    while(!(UCSR0A & (1<<RXC0)));

    /* returneaza datele din buffer */
    return UDR0;
}

/*
 * Functie ce transmite un sir de caractere prin USART
 *
 * @param data - sirul (terminat cu '\0') de transmis
 */
void USART0_print(const char *data)
{
    while(*data != '\0')
        USART0_transmit(*data++);
}

void USART_exec(char *command) {
    if (strcmp(command, "off") == 0) {
        // Aprinde led-ul RGB în culoarea albă
        PORTD |= (1 << PD5) | (1 << PD7);  // Setează pinii PD5 și PD7 (Red și Green) HIGH
        PORTB |= (1 << PB3);  // Setează pinul PB3 (Blue) HIGH
    } else if (strcmp(command, "on") == 0) {
        // Stinge led-ul RGB
        PORTD &= ~((1 << PD5) | (1 << PD7));  // Setează pinii PD5 și PD7 (Red și Green) LOW
        PORTB &= ~(1 << PB3);  // Setează pinul PB3 (Blue) LOW
    } else if (strcmp(command, "red") == 0) {
        // Setează led-ul în culoarea roșie
        PORTD &= ~(1 << PD5);  // Setează pinul PD5 (Red) HIGH
        PORTD |= (1 << PD7); // Setează pinul PD7 (Green) LOW
        PORTB |= (1 << PB3); // Setează pinul PB3 (Blue) LOW
    } else if (strcmp(command, "green") == 0) {
        // Setează led-ul în culoarea verde
        PORTD &= ~(1 << PD7);  // Setează pinul PD7 (Green) HIGH
        PORTD |= (1 << PD5); // Setează pinul PD5 (Red) LOW
        PORTB |= (1 << PB3); // Setează pinul PB3 (Blue) LOW
    } else if (strcmp(command, "blue") == 0) {
        // Setează led-ul în culoarea albastră
        PORTB &= ~(1 << PB3);  // Setează pinul PB3 (Blue) HIGH
        PORTD |= (1 << PD5); // Setează pinul PD5 (Red) LOW
        PORTD |= (1 << PD7); // Setează pinul PD7 (Green) LOW
    }
}