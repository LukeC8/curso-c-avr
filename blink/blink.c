/*
 * blink.c
 * - alterna o estado (ON/OFF) de um LED a cada 1/2 segundos
 *-----------------------------------------------------------
 * Microcontrolador - AT90CAN128
 * Placa de desenvolvimento - Lasse CAN Teste (2014)
 *-----------------------------------------------------------
 * Instrucoes de compilacao:
 * 	
 * 	compilar: $ avr-gcc -c -Os -DF_CPU=8000000 -mmcu=at90can128 blink.c
 * 	
 * 	linkar: $ avr-gcc -g -mmcu=at90can128 -o blink.elf blink.o
 * 	
 * 	criando imagem .hex: $ avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex
 *
 * Instrucoes de gravacao:
 *
 * 	(linux): $ sudo avrdude -c usbasp -p at90can128 -P lusb -U flash:w:blink.hex:i
 * 	(windows): $ sudo avrdude -c usbasp -p at90can128 -P COM3 -U flash:w:blink.hex:i
 * 			(COM3 eh a porta onde o gravador esta conectado)
 */

#include <avr/io.h>
#include <util/delay.h>

void main (void)
{
	DDRE |= (1<<PE4); // LED na porta PE4 (pino definido como saida)
	for (;;)
	{
		PORTE |= (1<<PE4); //liga o LED (pino PE4 em ALTO)
		_delay_ms (500); //aguarda 500 ms antes de executar a proxima linha
		PORTE &= ~(1<<3); //desliga o LED (pino PE4 em baixo)
		_delay_ms (500);
	}
}

