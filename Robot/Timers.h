/*
Define tipos y declara funciones para configurar los modulos de timer del Atmega328
y sus interrupciones:
	El Atmega328 tiene dos timers de 8 bits (TIMER0 y TIMER2) y un timer de 16 (TIMER1)
Los modos de trabajo de TIMER0 y TIMER2 son iguales entre si, pero difieren respecto
a los del TIMER1 (este tiene mas modos).
	Las opciones de prescaler de TIMER0 y TIMER1 son iguales entre si, pero difieren de
las del prescaler del TIMER2 (este no tiene los modos externos, y agrega dos modos
internos x32 y x128).
*/

#ifndef TIMERS_H_
#define TIMERS_H_

typedef enum {
	Normal			= 0,
	PWM_PC_8b		= 1,
	CTC_OCRA		= 2,
	FAST_PWM_8b		= 3,
	PWM_PC_OCR		= 5,
	FAST_PWM_OCR	= 7
}tT0y2modo; //Tipo modos de trabajo para TIMER0 y TIMER2
typedef enum {
	Normal1			= 0,
	PWM_PC1_8b		= 1,
	PWM_PC1_9b		= 2,
	PWM_PC1_10b		= 3,
	CTC_OCR1A		= 4,
	FAST_PWM1_8b	= 5,
	FAST_PWM1_9b	= 6,
	FAST_PWM1_10b	= 7,
	PWM_PyFC_ICR1	= 8,
	PWM_PyFC_OCR1A	= 9,
	PWM_PC_ICR1		= 10,
	PWM_PC_OCR1A	= 11,
	CTC_ICR1		= 12,
	FAST_PWM_ICR1	= 14,
	FAST_PWM_OCR1A	= 15
}tT1modo; //Tipo modos de trabajo para TIMER1

typedef enum {
	des			=	0,
	prex1		=	1,
	prex8		=	2,
	prex64		=	3,
	prex256		=	4,
	prex1024	=	5,
	Ext_Fneg	=	6,
	Ext_Fpos	=	7
}tT0y1pre; //Tipo prescaler para TIMER0 y TIMER1
typedef enum {
	des2		=	0,
	pre2x1		=	1,
	pre2x8		=	2,
	pre2x32		=	3,
	pre2x64		=	4,
	pre2x128	=	5,
	pre2x256	=	6,
	pre2x1024	=	7
}tT2pre;  //Tipo prescaler para TIMER2

typedef enum {
	sNo			= 0,
	sToggle		= 1,
	sClear		= 2,
	sSet		= 3
}tTsalida; //Tipo salida para todos los timers

//Aqui se definen las estructuras con todos los Parametros de Configuracion
//de TIMER0, TIMER1 y TIMER2. Son estructura con campos de diversos tipos enumerados.
typedef struct {
	tT0y2modo	modo;  //estos campos son los anteriormente definidos
	tT0y1pre	pre;
	tTsalida	OCA;
	tTsalida	OCB;
}tT0config;
typedef struct {
	tT1modo		modo;
	tT0y1pre	pre;
	tTsalida	OCA;
	tTsalida	OCB;
}tT1config;
typedef struct {
	tT0y2modo	modo;
	tT2pre		pre;
	tTsalida	OCA;
	tTsalida	OCB;
}tT2config;

//  Aqui se definen las estructuras para activar interrupciones de
//  TIMER0, TIMER1 y TIMER2.
typedef struct {
	bool	IT_ovf:1;   //Estos campos son simplemente booleanos.
	bool	IT_compa:1;
	bool	IT_compb:1;
}tT0INTconfig;
typedef struct {
	bool	IT_ovf:1;   //Al usar booleanos lo ideal es especificar su longitud para que
	bool	IT_compa:1; //sea de 1 Byte (con :1), sino genera una longitud de 3 Bytes;
	bool	IT_compb:1; //aunque no es necesariamente fundamental, si es que se cuenta con
	bool	IT_ic:1;	//un Uc que dispone de mucha mas memoria de la que se necesita.
}tT1INTconfig;
typedef struct {        //Esta estructura es igual a la de TIMER0
	bool	IT_ovf:1;
	bool	IT_compa:1;
	bool	IT_compb:1;
}tT2INTconfig;

// Declaracion de variables:
#define T_ms  16.32  //Periodo fijo [en ms]
#define ANCHO_PULSO_INICIAL    1.500 //Pulso Inicial [en ms]
#define ANCHO_PULSO_INICIAL_G  2.100 //Pulso Inicial servo Giro gripper [en ms]
#define ANCHO_PULSO_INICIAL_A  2.500 //Pulso Inicial servo Altura gripper [en ms]
#define ANCHO_PULSO_INICIAL_C  0.250 //Pulso Inicial servo Cierre-apertura gripper [en ms]

uint16_t valorPrescaler__T0;
uint16_t valorPrescaler__T1;
uint16_t valorPrescaler__T2;
tT0config T0cfg;
tT1config T1cfg;
tT2config T2cfg;

// Declaracion de las funciones:
void T0_Init(tT0config *Tcfg);
void T0_deInit(tT0config *Tcfg);  //Funcion que pone parametros de estructura Tcfg
								  //en valores por defecto.
void T1_Init(tT1config *Tcfg);
void T1_deInit(tT1config *Tcfg); //Funcion que pone parametros de estructura Tcfg
								  //en valores por defecto.
void T2_Init(tT2config *Tcfg);
void T2_deInit(tT2config *Tcfg); //Funcion que pone parametros de estructura Tcfg
								  //en valores por defecto.
void T0_Interrupts(tT0INTconfig *Tintcfg);
void T1_Interrupts(tT1INTconfig *Tintcfg);
void T2_Interrupts(tT2INTconfig *Tintcfg);
void configurarTimer0(tT0y2modo modoOperacionT0, tT0y1pre prescalerT0, tTsalida modoSalidaA,
																				tTsalida modoSalidaB);
void configurarTimer1(tT1modo modoOperacionT1, tT0y1pre prescalerT1, tTsalida modoSalidaA,
																				tTsalida modoSalidaB);
void configurarTimer2(tT0y2modo modoOperacionT2, tT2pre prescalerT2, tTsalida modoSalidaA,
																				tTsalida modoSalidaB);
uint16_t valorPrescalerT0y1(tT0y1pre prescalerT0y1);
uint16_t valorPrescalerT2(tT2pre prescalerT2);

#endif /* TIMERS_H_ */