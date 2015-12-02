#include <avr/io.h>
#include <util/delay.h>

#define CHANNEL_0 0
#define VREF 5.0
#define vin(a) (a/204.8)
#define LOW 307.2
#define VLOW 1.5

/*
 * init_adc - Inicializa o conversor A/D
 */
void init_adc (void);

/*
 * adc_convert - Faz a leitura de um canal analogico e converte
 * em uma amostra de 10 bits
 */
uint16_t adc_read (unsigned char channel);

void main (void)
{
	uint16_t value = 0;

	DDRB = (1<<PB5); // pino PB5 (LED) como saida.
	
	init_adc ();

	for (;;)
	{
		value = adc_read (CHANNEL_0); // leitura da tensao da pilha (canal 0)

		if (vin(value) < VLOW) //se o valor de tensao for abaixo de 1.5V
		{
			PORTB |= (1<<PB5); //Liga o LED
			
			while (vin(value) < VLOW) //mantem o LED ligado enquanto
			{
				value = adc_read (CHANNEL_0);
			}

			PORTB &= ~(1<<PB5); // desliga o LED
		}

		PORTB ^= (1<<PB5);
		_delay_ms(500);
	}
}

void init_adc (void)
{
	ADMUX = (1<<REFS0); // configura referencia do conversor A/D para VCC.
	ADCSRA = (1<<ADEN); // ativa o conversor A/D.
	ADCSRA |= (1<<ADPS1); // configura o Prescaler com F_CPU/4.
}

uint16_t adc_read (unsigned char channel)
{
	channel &= 0b0000111;	//garante que o numero do canal seja no max 8.
	ADMUX &= 0b11111000;	//limpa configuracoes de leitura de canais anteriores.
	ADMUX |= channel;	//configura o canal a ser lido.

	ADCSRA |= (1<<ADSC); 	//inicia a conversao.

	while (ADCSRA & (1 << ADSC)); //enquanto a conversao nao termina o bit ADSC fica ativo.

	//conversao finalizada! O resultado esta armazenado nos registradores
	//ADCH e ADCL
	uint16_t result = ADCL; //le-se a parte menos significativa primeiro
	result |= (ADCH << 8);  //le-se a parte mais significativa

	return result; // (ADCL | (ADCH << 8)) ou ADC
}

