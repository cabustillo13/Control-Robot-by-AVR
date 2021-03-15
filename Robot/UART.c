/*
 Biblioteca de funciones basicas de UART y manejo de interrupcion por recepcion de dato.
 */

#include "main.h"
#include "UART.h"

//Declara un parametro tipo stream de E/S:
FILE uart_io = FDEV_SETUP_STREAM(mi_putchar, mi_getchar, _FDEV_SETUP_RW);

void configurarUART(uint32_t baudRate, uint8_t intRx, uint8_t intTx) {
	stdout = stdin = &uart_io; //El stream (FILE) uart_io es la E/S estandar, es decir para fputc y fgetc.
	//Parametros de la comunicacion:
	UBRR0   =  F_CPU/16/baudRate-1;	//Configuracion baudrate
	UCSR0A &=~ (1<<U2X0);			//Velocidad simple (1 para doble)
	UCSR0B |=  (1<<RXEN0);			//Habilita recepcion
	UCSR0B |=  (1<<TXEN0);			//Habilita transmision
	UCSR0C |=  (1<<USBS0);			//1 bit de STOP
	UCSR0C |=  (3<<UCSZ00);			//8 bits de dato
	if(intRx) {
		UCSR0A &=~ (1<<RXC0);	//Apaga flag de interrupcion por Recepcion Completa
		UCSR0B |=  (1<<RXCIE0);	//Habilita interrupcion RX
	}
	if(intTx) {
		UCSR0A &=~ (1<<TXC0);	//Apaga flag de interrupcion por Transmision Completa
		UCSR0B |=  (1<<TXCIE0);	//Habilita interrupcion TX
	}
}

int mi_putchar(char c, FILE *stream) {
	while(!(UCSR0A & (1<<UDRE0)) );  //Espera mientras buffer de transmision este ocupado
	UDR0 = c;						 //UDR0 recibe el nuevo dato c a transmitir.
	return 0;
}
int mi_getchar(FILE *stream) {
	while ( !(UCSR0A & (1<<RXC0)) ); //Espera mientras la recepcion no esta completa.
	return UDR0;					 //Cuando se completa, se lee UDR0.
}

//-----------------------------------------------------------------------------------------//
//								Rutina de Servicio de Interrupcion:						   //
//-----------------------------------------------------------------------------------------//
/*	Rutina de Servicio de Interrupcion por recepcion de datos en UART
	Espera mensajes del tipo [:][comando][\r] y lo guarda en buffer comando[]
	limpiando delimitadores y agregando NULL al final del mismo para poder usar atoi*/
ISR(USART_RX_vect) { //Rutina de servicio de Interrupcion por Rx:
	char dato;
	switch(Estado) {
		case E_desactivado:
				#ifdef HabilitarPrintf
					if (bandera) printf("\nEl Estado se encuentra Desactivado\n\n");
				#endif
				bandera=0;
				dato = fgetc(); //No se usa el char dato, solamente es para limpiar el flag RXC0 de 
								//dato recibido, antes de salir de la ISR.
				break;
		case E_activado:
				bandera=1;
				dato = fgetc();
				//printf("echo: %c\r\n",dato);
				switch(dato) {
					case ':':	//Delimitador de inicio
								indcom=0;		//Inicializa indice de buffer de recepcion
								flagcom = 1;	//Comando en curso
								break;
					case 8:		//Basckspace
								if(indcom>0) indcom--;
								break;
					case '\r':	//Delimitador de final (Retorno de Carro)
								if(flagcom==1) {		  //Si hay comando en curso
									comando[indcom] = 0;  //Coloca NULL luego de ultimo caracter recibido
									interpretarComando(); //Interpreta comando recibido
									flagcom = 0;		  //Fin de comando en curso
								}
								break;
					default:	//Todo lo que este entre delimitadores
								if(indcom<30) //Guarda en elemento del buffer e incrementa indcom:
									comando[indcom++] = dato;
				}
				break;
	}
	UCSR0A &=~ (1<<RXC0);			//Apaga el flag de interrupcion por RX
}