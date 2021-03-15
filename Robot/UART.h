#ifndef UART_H_
#define UART_H_

void configurarUART(uint32_t baudRate, uint8_t intRX, uint8_t intTX);
int mi_putchar(char c, FILE *stream);
int mi_getchar(FILE *stream);
#define fgetc() mi_getchar(&uart_io)	//Redefine la primitiva de entrada como funcion recibir por UART
#define fputc(x) mi_putchar(x,&uart_io)	//Redefine la primitiva de salida como funcion transmitir por UART

uint8_t bandera;		//Flag para evitar imprimir un mismo mensaje sin haber cambiado de estado.
uint8_t indcom;		    //Indice de buffer de recepcion
uint8_t flagcom;        //Flag "comando en curso"
#define comSize 30		//Tamaño buffer de recepcion
char comando[comSize];  //Buffer de recepcion




#endif /* UART_H_ */