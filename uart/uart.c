#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define BAUDRATE (((F_CPU / (BAUD * 16UL)) - 1))

void uart_init (void)
{
	UBRR0H = (BAUDRATE >> 8);
	UBRR0L = BAUDRATE;

	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

char uart_getchar (void)
{
	while (!(UCSR0A & (1 << RXC0))); //aguarda chegar algum dado
	return UDR0; //faz a leitura dos dados 
}

void uart_putchar (const char c)
{
	while (!(UCSR0A & (1 << UDRE0))); //aguarda a transmissao de algum dado anterior
	UDR0 = c; //escreve dados no registrador (envia o dado)
}

int main (void)
{
	char read = 0;

	DDRB = (1 << PB5);
	uart_init ();

	for (;;)
	{
		uart_putchar ('o');
		uart_putchar ('i');
		uart_putchar ('!');
		uart_putchar ('\r');
		uart_putchar ('\n');

		while (read = uart_getchar() != '\n')
			uart_putchar(read);

		PORTB ^= (1<<PB5);
	}
}

