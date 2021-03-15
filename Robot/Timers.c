#include "main.h"
#include "Timers.h"

//Incializa estructura Tcfg de forma que T0_Init configure
//al TIMER0 con los valores de Reset (no modifica registros):
void T0_deInit(tT0config * Tcfg) {
	Tcfg->modo=Normal;
	Tcfg->pre=des;
	Tcfg->OCA=sNo;
	Tcfg->OCB=sNo;
}
//Incializa estructura Tcfg de forma que T1_Init configure
//al TIMER1 con los valores de Reset (no modifica registros):
void T1_deInit(tT1config * Tcfg) {
	Tcfg->modo=Normal1;
	Tcfg->pre=des;
	Tcfg->OCA=sNo;
	Tcfg->OCB=sNo;
}
//Incializa estructura Tcfg de forma que T2_Init configure
//al TIMER2 con los valores de Reset (no modifica registros):
void T2_deInit(tT2config * Tcfg) {
	Tcfg->modo=Normal;
	Tcfg->pre=des2;
	Tcfg->OCA=sNo;
	Tcfg->OCB=sNo;
}

//Configura pines como salidas, y sus Modos de Salida: toggle, clear o set (1, 2 o 3):
void T0_Init(tT0config * Tcfg) {
	if (Tcfg->OCA) DDRD|=(1<<DDB6);  //OC0A es PD6 en Atmega328
	if (Tcfg->OCB) DDRD|=(1<<DDB5);	 //OC2B es PD5
	//Los tipos enumerados son tipo int.
	TCCR0A = (Tcfg->OCA <<COM0A0)|(Tcfg->OCB<<COM0B0)|(Tcfg->modo&0x03); //Configura Modo Operacional,..
	TCCR0B = (((Tcfg->modo)<<1)&8)|Tcfg->pre;  //..Prescaler y Modo de Salida en los dos registros TCCR.
}
void T1_Init(tT1config * Tcfg) {
	if (Tcfg->OCA) DDRB|=(1<<DDB1); //OC1A es PB1
	if (Tcfg->OCB) DDRB|=(1<<DDB2); //OC1B es PB2
	TCCR1A = (Tcfg->OCA <<COM1A0)|(Tcfg->OCB<<COM1B0)|(Tcfg->modo&0x03);
	TCCR1B = (((Tcfg->modo)<<1)&0x18)|(Tcfg->pre);
}
void T2_Init(tT2config * Tcfg) {
	if (Tcfg->OCA) DDRB|=(1<<DDB3);  //OC2A es PB3
	if (Tcfg->OCB) DDRD|=(1<<DDB3);	 //OC2B es PD3
	TCCR2A = (Tcfg->OCA <<COM2A0)|(Tcfg->OCB<<COM2B0)|(Tcfg->modo&0x03);
	TCCR2B = (((Tcfg->modo)<<1)&8)|Tcfg->pre;
}

//Habilitacion de interrupciones de software de los timers:
void T0_Interrupts(tT0INTconfig *T0i) {
	TIMSK0=(T0i->IT_compb)<<OCIE0B|(T0i->IT_compa)<<OCIE0A|(T0i->IT_ovf)<<TOIE0; 
	TIFR0=(T0i->IT_compb)<<OCF0B|(T0i->IT_compa)<<OCF0A|(T0i->IT_ovf)<<TOV0; //apagado de flag
}
void T1_Interrupts(tT1INTconfig *T1i) {
	TIMSK1=(T1i->IT_ic)<<ICIE1|(T1i->IT_compb)<<OCIE1B|(T1i->IT_compa)<<OCIE1A|(T1i->IT_ovf)<<TOIE1;
	TIFR1=(T1i->IT_ic)<<ICF1|(T1i->IT_compb)<<OCF1B|(T1i->IT_compa)<<OCF1A|(T1i->IT_ovf)<<TOV1;
}
void T2_Interrupts(tT2INTconfig *T2i) {
	TIMSK2=(T2i->IT_compb)<<OCIE2B|(T2i->IT_compa)<<OCIE2A|(T2i->IT_ovf)<<TOIE2;
	TIFR2=(T2i->IT_compb)<<OCF2B|(T2i->IT_compa)<<OCF2A|(T2i->IT_ovf)<<TOV2; //borra solo.. 
}															//..los flags de int habilitadas

void configurarTimer0(tT0y2modo modoOperacionT0, tT0y1pre prescalerT0, tTsalida modoSalidaA, tTsalida modoSalidaB) {
	T0_deInit(&T0cfg);
	T0cfg.modo = modoOperacionT0;
	#ifdef EstadoInicialActivado
		T0cfg.pre = prescalerT0;
	#endif
	#ifdef EstadoInicialDesactivado
		T0cfg.pre = des; //TIMER0 comienza en Estado Desactivado
	#endif
	T0cfg.OCA = modoSalidaA;
	T0cfg.OCB = modoSalidaB;
	T0_Init(&T0cfg);
	valorPrescaler__T0=valorPrescalerT0y1(prescalerT0);
	OCR0A = (uint16_t)( (ANCHO_PULSO_INICIAL_A/1000)*(F_CPU/valorPrescaler__T0) +1 ); //Servo A
	OCR0B = (uint16_t)( (ANCHO_PULSO_INICIAL_G/1000)*(F_CPU/valorPrescaler__T0) +1 ); //Servo G
}
void configurarTimer1(tT1modo modoOperacionT1, tT0y1pre prescalerT1, tTsalida modoSalidaA,
																		tTsalida modoSalidaB) {
	/* Config Timer1:
	T1cfg esta declarada en Timers.h como variable tipo tT1config
	tT1config esta definida en Timers.h como una estructura con campos
	de diversos tipos enumerados, lo que facilita su llenado.*/
	T1_deInit(&T1cfg); //Incializa estructura de forma que T1_Init configure al TIMER1 con los valores
					   //de Reset (buena practica), aunque no es necesario si llenamos todos los parametros.
	T1cfg.modo = modoOperacionT1;
	#ifdef EstadoInicialActivado
		T1cfg.pre = prescalerT1;
	#endif
	#ifdef EstadoInicialDesactivado
		T1cfg.pre = des; //TIMER1 comienza en Estado Desactivado
	#endif
	T1cfg.OCA = modoSalidaA;
	T1cfg.OCB = modoSalidaB;
	// Hasta aqui solamente se ha cargado la variable T1cfg con datos, no se ha 
	// modificado ningun registro del Timer1 del micro.
	T1_Init(&T1cfg); // Llama a la funcion que va a configurar al Timer1 con los
	                 // parametros cargados en T1cfg.
	valorPrescaler__T1=valorPrescalerT0y1(prescalerT1);
	ICR1  = (uint16_t)( (T_ms/1000)*(F_CPU/valorPrescaler__T1) +1 ); //Controla Periodo de los PWM en Timer1
	OCR1A = (uint16_t)( (ANCHO_PULSO_INICIAL/1000)*(F_CPU/valorPrescaler__T1) +1 ); //Servo B
	OCR1B = (uint16_t)( (ANCHO_PULSO_INICIAL/1000)*(F_CPU/valorPrescaler__T1) +1 ); //Servo M
}
void configurarTimer2(tT0y2modo modoOperacionT0y2,tT2pre prescalerT2, tTsalida modoSalidaA,
																			tTsalida modoSalidaB) {
	T2_deInit(&T2cfg);
	T2cfg.modo = modoOperacionT0y2;
	#ifdef EstadoInicialActivado
		T2cfg.pre = prescalerT2;
	#endif
	#ifdef EstadoInicialDesactivado
		T2cfg.pre = des2; //TIMER2 comienza en Estado Desactivado
	#endif
	T2cfg.OCA = modoSalidaA;
	T2cfg.OCB = modoSalidaB;
	T2_Init(&T2cfg);
	valorPrescaler__T2=valorPrescalerT2(prescalerT2);
	OCR2A = (uint16_t)( (ANCHO_PULSO_INICIAL_C/1000)*(F_CPU/valorPrescaler__T2) +1 ); //Servo C
	//OCR2B = (uint16_t)( (ANCHO_PULSO_INICIAL/1000)*(F_CPU/valorPrescaler__T2) +1 );
}
uint16_t valorPrescalerT0y1(tT0y1pre prescalerT0y1) { //Valor numerico del prescaler para TIMER0 y TIMER1
	switch(prescalerT0y1) {
			case des:
					return 0;
					break;
			case prex1:
					return 1;
					break;
			case prex8:
					return 8;
					break;
			case prex64:
					return 64;
					break;
			case prex256:
					return 256;
					break;
			case prex1024:
					return 1024;
					break;
			case Ext_Fneg:
					return 0;
					break;
			case Ext_Fpos:
					return 0;
					break;
			default:
					return 0;
					break;
	}
}
uint16_t valorPrescalerT2(tT2pre prescalerT2) { //Valor numerico del prescaler para TIMER2
	switch(prescalerT2) {
			case des2:
					return 0;
					break;
			case pre2x1:
					return 1;
					break;
			case pre2x8:
					return 8;
					break;
			case pre2x32:
					return 32;
					break;
			case pre2x64:
					return 64;
					break;
			case pre2x128:
					return 128;
					break;
			case pre2x256:
					return 256;
					break;
			case pre2x1024:
					return 1024;
					break;
			default:
					return 0;
					break;
	}
}