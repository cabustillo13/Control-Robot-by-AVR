#ifndef MAIN_H_
#define MAIN_H_

#define  F_CPU 16000000		// para biblioteca delay y funcion de usuario de UART
#include <math.h>			//
#include <stdio.h>			// para UART como dispositivo estandar (printf(""), etc.)
#include <stdlib.h>			// para atoi(), etc.
#include <util/delay.h>		// para funcion delay
#include <avr/io.h>			// definicion de regitro y bits de micro
#include <avr/interrupt.h>	// definicion de vectores de interr
#include <stdbool.h>		// para tipo bool en timer.h

#include "InterrupcionesINT.h"
#include "UART.h"
#include "Timers.h"

#define HabilitarPrintf			 //Descomentar esta linea para habilitar los printf()
//#define EstadoInicialActivado	 //Descomentar esta linea para iniciar con Estado Activado
#define EstadoInicialDesactivado //DesComentar esta linea para iniciar con Estado Desactivado


enum estado {E_desactivado, E_activado};
enum estado Estado;
#define ApagarTodosLosPines		(PORTB &= (0<<0)) //Colocamos en estado bajo todos los pines del puerto B
//para evitar errores por ruido electromagnetico.
#define C2_OUT				(DDRC |= (1<<DDC2)) //PC2 (Pin A2 arduino nano) como SALIDA
#define C3_OUT				(DDRC |= (1<<DDC3)) //PC3 (Pin A3 arduino nano) como SALIDA
#define C4_OUT				(DDRC |= (1<<DDC4)) //PC4 (Pin A4 arduino nano) como SALIDA
#define LedAmarilloC2_OFF	(PORTC &= ~(1<<PORTC2))	//Definimos: Apagar pin 2 del puerto C
#define LedVerdeC3_OFF		(PORTC &= ~(1<<PORTC3))	//Definimos: Apagar pin 3 del puerto C
#define LedRojoC4_OFF		(PORTC &= ~(1<<PORTC4))	//Definimos: Apagar pin 4 del puerto C
#define LedAmarilloC2_ON	(PORTC |= (1<<PORTC2))	//Definimos: Encender pin 2 del puerto C
#define LedVerdeC3_ON		(PORTC |= (1<<PORTC3))	//Definimos: Encender pin 3 del puerto C
#define LedRojoC4_ON		(PORTC |= (1<<PORTC4))	//Definimos: Encender pin 4 del puerto C

//_________________________________InterrupcionesINT___________________________________//
#define D2_IN				(DDRD &= ~(1<<DDD2)) //PD3 [INT0] (Pin D2 arduino nano) como ENTRADA
#define D3_IN				(DDRD &= ~(1<<DDD3)) //PD2 [INT1] (Pin D3 arduino nano) como ENTRADA
//_____________________________________________________________________________________//
//______________________________________UART___________________________________________//
uint16_t anguloB_CONSIGNA;	//angulo servo Base
uint16_t anguloM_CONSIGNA;	//anguloservo Medio
uint16_t anguloG_CONSIGNA;	//angulo sevo Giro gripper
uint16_t anguloA_CONSIGNA;	//angulo sevo Altura gripper
uint16_t anguloC_CONSIGNA;	//angulo sevo Cierre gripper
float duracionPulsoB;  //Duraciones de Pulsos en ms:
float duracionPulsoM;
float duracionPulsoG;
float duracionPulsoA;
float duracionPulsoC;
void interpretarComando(void);
//_____________________________________________________________________________________//
//______________________________________Timers_________________________________________//
#define B1_SERVO_BASE			(DDRB |= (1<<DDB1)) //PB1 [OC1A] (Pin D9 arduino nano) como SALIDA
#define B2_SERVO_MEDIO			(DDRB |= (1<<DDB2)) //PB2 [OC1B] (Pin D10 arduino nano) como SALIDA
#define D5_SERVO_GIRO_GRIPPER	(DDRD |= (1<<DDD5)) //PD5 [OC0B] (Pin D5 arduino nano) como SALIDA
#define D6_SERVO_ALTURA_GRIPPER	(DDRD |= (1<<DDD6)) //PD6 [OC0A] (Pin D6 arduino nano) como SALIDA
#define B3_SERVO_CIERRE_GRIPPER	(DDRB |= (1<<DDB3)) //PB3 [OC2A] (Pin D11 arduino nano) como SALIDA
//_____________________________________________________________________________________//

#endif /* MAIN_H_ */