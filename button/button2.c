/*
 * button2.c
 * - Liga um LED quando o push button2 eh pressionado
 *-----------------------------------------------------------
 * Microcontrolador - AT90CAN128
 * Placa de desenvolvimento - Lasse CAN Teste (2014)
 *-----------------------------------------------------------
 * Instrucoes de compilacao:
 * 	
 * 	compilar: $ avr-gcc -c -Os -DF_CPU=8000000 -mmcu=at90can128 button2.c
 * 	
 * 	linkar: $ avr-gcc -g -mmcu=at90can128 -o button2.elf button2.o
 * 	
 * 	criando imagem .hex: $ avr-objcopy -j .text -j .data -O ihex button2.elf button2.hex
 *
 * Instrucoes de gravacao:
 *
 * 	(linux): $ sudo avrdude -c usbasp -p at90can128 -P lusb -U flash:w:button2.hex:i
 * 	(windows): $ sudo avrdude -c usbasp -p at90can128 -P COM3 -U flash:w:button2.hex:i
 * 			(COM3 eh a porta onde o gravador esta conectado)
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h> //para usar as macros bit_is_set e bit_is_clear

void main (void)
{
	DDRE |= (1<<PE4); // LED na porta PE4 (pino definido como saida)
			  // Botao na porta PE5 (pino definido como entrada)
	for (;;)
	{
		//podemos utilizar algumas macros para tornar mais facil a leitura do codigo
		if (bit_is_set(PORTE, PE5)) 	//verifica se o valor do pino PE5 eh ALTO
			PORTE |= (1<<PE4);	//liga o LED conectado na porta PE4
		else 				//caso o botao nao esteja pressionando o botao
			PORTE &= ~(1<<PE4);	//desliga o LED
	}
}

