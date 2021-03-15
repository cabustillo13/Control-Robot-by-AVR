#include "main.h"

//-----------------------------------------------------------------------------------------//
//								Rutinas de Interrupciones INT:							   //
//-----------------------------------------------------------------------------------------//
ISR(INT0_vect) { //Entra a esta rutina ante cualquier cambio (flanco de bajada o de subida).
	_delay_ms(77); //Delay y verificacion filtran ruidos electricos.
	if(INT0_test) {//Se elige con las verificacion "if" que actue como por flanco de subida inicamente.
		T0cfg.pre = des;	//Desactivacion de los tres Timers:
		T0_Init(&T0cfg);
		T1cfg.pre = des;
		T1_Init(&T1cfg);
		T2cfg.pre = des2;
		T2_Init(&T2cfg);
		LedVerdeC3_OFF;
		LedRojoC4_ON;
		Estado=E_desactivado;
		#ifdef HabilitarPrintf
			printf("ESTADO DESACTIVADO\n");
		#endif
	}
	flagINT0_OFF; //Es una buena practica apagar el flag de la interrupcion antes de salir de su ISR.
}
ISR(INT1_vect) {
	_delay_ms(77);
	if(INT1_test) {
		T0cfg.pre = prex1024;	//Activacion de los tres Timers:
		T0_Init(&T0cfg);
		T1cfg.pre = prex8;
		T1_Init(&T1cfg);
		T2cfg.pre = pre2x1024;
		T2_Init(&T2cfg);
		LedVerdeC3_ON;
		LedRojoC4_OFF;
		Estado=E_activado;
		#ifdef HabilitarPrintf
			printf("ESTADO ACTIVADO\n");
		#endif
	}
	flagINT1_OFF;
}

//-----------------------------------------------------------------------------------------//
//								Interprete de Comandos UART:							   //
//-----------------------------------------------------------------------------------------//
void interpretarComando(void) {
	uint16_t B;	//servo Base
	uint16_t M;	//servo Medio
	uint16_t G;	//sevo Giro gripper
	uint16_t A;	//sevo Altura gripper
	uint16_t C;	//sevo Cierre gripper
	LedAmarilloC2_OFF;
	switch(comando[0]) {  //Analiza primer caracter del buffer:
		case 'B':
		case 'b':
		if(comando[1]) {              //Si es distinto de 0
			B = atoi(&comando[1]);    //Convierte string(cadena de caracteres) a entero
			if( (0<=B) && (B<=180) ) {
				#ifdef HabilitarPrintf
					printf("ANGULO B ingresado: %u grados\n",B);
				#endif
				anguloB_CONSIGNA=B;
				//Mapeo del rango [0;180]grados al rango [0.500;2.500]ms: dutyCycleA=2ms*(%Angulo)+0.5ms
				duracionPulsoB=2.000*(anguloB_CONSIGNA/180.0)+0.500;
				OCR1A = (uint16_t)( (duracionPulsoB/1000.0)*(F_CPU/valorPrescaler__T1) +1 );
				}else {
				#ifdef HabilitarPrintf
					printf("Angulo B ingresado fuera de rango [0,180] grados\n");
				#endif
			}
			}else {
			#ifdef HabilitarPrintf
				//Para un comando sin valor numerico:
				printf("Angulo B Actual = %u grados\n",anguloB_CONSIGNA);
			#endif
		}
		break;
		case 'M':
		case 'm':
		if(comando[1]) {
			M = atoi(&comando[1]);
			if( (0<=M) && (M<=180) ) {
				#ifdef HabilitarPrintf
					printf("ANGULO M ingresado: %u grados\n",M);
				#endif
				anguloM_CONSIGNA=M;
				duracionPulsoM=2.000*(anguloM_CONSIGNA/180.0)+0.500;
				OCR1B = (uint16_t)( (duracionPulsoM/1000)*(F_CPU/valorPrescaler__T1) +1 );
				}else {
				#ifdef HabilitarPrintf
					printf("Angulo M ingresado fuera de rango [0,180] grados\n");
				#endif
			}
			}else {
			#ifdef HabilitarPrintf
				printf("Angulo M Actual = %u grados\n",anguloM_CONSIGNA);
			#endif
		}
		break;
		case 'G':
		case 'g':
		if(comando[1]) {
			G = atoi(&comando[1]);
			if( (0<=G) && (G<=180) ) {
				#ifdef HabilitarPrintf
					printf("ANGULO G ingresado: %u grados\n",G);
				#endif
				anguloG_CONSIGNA=G; //(Inicia en 143 grados)
				//duracionPulsoG: [0,1333;2,6167]ms (Inicia en 2,100)
				//Nota: El rango no común se debe a que el servo puede girar 360 grados
				duracionPulsoG=2.4834*(anguloG_CONSIGNA/180.0)+0.1333;
				OCR0B = (uint16_t)( (duracionPulsoG/1000.0)*(F_CPU/valorPrescaler__T0) +1 );
				}else {
				#ifdef HabilitarPrintf
					printf("Angulo G ingresado fuera de rango [0,180] grados\n");
				#endif
			}
			}else {
			#ifdef HabilitarPrintf
				printf("Angulo G Actual = %u grados\n",anguloG_CONSIGNA);
			#endif
		}
		break;
		case 'A':
		case 'a':
		if(comando[1]) {
			A = atoi(&comando[1]);
			if( (0<=A) && (A<=180) ) {
				#ifdef HabilitarPrintf
					printf("ANGULO A ingresado: %u grados\n",A);
				#endif
				anguloA_CONSIGNA=A; //(Inicia en 180 grados)
				//duracionPulsoA: [0,500;2,500]ms (Inicia en 2,500ms)
				duracionPulsoA=2.000*(anguloA_CONSIGNA/180.0)+0.500;
				OCR0A = (uint16_t)( (duracionPulsoA/1000)*(F_CPU/valorPrescaler__T0) +1 );
				}else {
				#ifdef HabilitarPrintf
					printf("Angulo A ingresado fuera de rango [0,180] grados\n");
				#endif
			}
			}else {
			#ifdef HabilitarPrintf
				printf("Angulo A Actual = %u grados\n",anguloA_CONSIGNA);
			#endif
		}
		break;
		case 'C':
		case 'c': 
		if(comando[1]) {
			C = atoi(&comando[1]);
			if( (0<=C) && (C<=180) ) {
				#ifdef HabilitarPrintf
					printf("ANGULO C ingresado: %u grados\n",C);
				#endif
				anguloC_CONSIGNA=C; //(Inicia en 0 grados)
				//anguloC_CONSIGNA: [0,250;1,350]ms (Inicia en 0,250ms)
				//Nota: El rango no común se debe a que el movimiento del servo está restringido por el gripper
				duracionPulsoC=1.100*(anguloC_CONSIGNA/180.0)+0.250;
				OCR2A = (uint16_t)( (duracionPulsoC/1000.0)*(F_CPU/valorPrescaler__T2) +1 );
				}else {
				#ifdef HabilitarPrintf
					printf("Angulo C ingresado fuera de rango [0,180] grados\n");
				#endif
			}
			}else {
			#ifdef HabilitarPrintf
				printf("Angulo C Actual = %u grados\n",anguloC_CONSIGNA);
			#endif
		}
		break;
		default:
		LedAmarilloC2_ON;
		#ifdef HabilitarPrintf
			printf("Consigna invalida\n");
		#endif
	}
}

//-----------------------------------------------------------------------------------------//
//											 Main										   //
//-----------------------------------------------------------------------------------------//
int main(void) {
	ApagarTodosLosPines;
	C2_OUT; //Led Amarillo de consigna invalida
	C3_OUT; //Led Verde de Estado Activado
	C4_OUT; //Led Rojo de Estado Desactivado
	LedAmarilloC2_OFF;
	bandera=1;
	#ifdef EstadoInicialActivado
		Estado=E_activado;	//Estado inicial
		LedVerdeC3_ON;
		LedRojoC4_OFF;
	#endif
	#ifdef EstadoInicialDesactivado
		Estado=E_desactivado;	//Estado inicial
		LedVerdeC3_OFF;
		LedRojoC4_ON;
	#endif
	
	//_________________________________InterrupcionesINT___________________________________//
	D2_IN;
	D3_IN;
	configurarINT0();
	configurarINT1();
	//_____________________________________________________________________________________//
	//______________________________________UART___________________________________________//
	anguloB_CONSIGNA=90;	//angulo servo Base
	anguloM_CONSIGNA=90;	//angulo servo Medio
	anguloG_CONSIGNA=143;	//angulo servo Giro gripper	  (angulo inicio debido a limitación muneca humana)
	anguloA_CONSIGNA=180;	//angulo servo Altura gripper (gripper inicia lejos del suelo)
	anguloC_CONSIGNA=0;		//angulo servo Cierre gripper (gripper inicia cerrado)
	configurarUART(9600,1,0); //(baudrate,interrupcionRx,interrupcionTx)
	#ifdef HabilitarPrintf
		printf("	Proyecto MyEP 2021\n");
		printf("Ingrese el angulo, entre 0 y 180 grados, de cada servomotor,\n");
		printf("mediante el comando: :Xnnn\n");
		printf("donde X representa la letra caracteristica de los 5 servos:\n");
		printf("	B [0_Base]\n");
		printf("	M [1_Medio]\n");
		printf("	G [2_Giro-gripper]\n");
		printf("	A [3_Altura-gripper]\n");
		printf("	C [4_Cierre-gripper]\n");
	#endif
	//_____________________________________________________________________________________//
	//______________________________________Timers_________________________________________//
	B1_SERVO_BASE;
	B2_SERVO_MEDIO;
	D5_SERVO_GIRO_GRIPPER;
	D6_SERVO_ALTURA_GRIPPER;
	B3_SERVO_CIERRE_GRIPPER;
	//configurarTimer0(modoOperacionT0y2, prescalerT0y1, modoSalidaA, modoSalidaB)
	configurarTimer0(FAST_PWM_8b, prex1024, sClear, sClear);
	//configurarTimer1(modoOperacionT1, prescalerT0y1, modoSalidaA, modoSalidaB)
	configurarTimer1(FAST_PWM_ICR1, prex8, sClear, sClear);
	//configurarTimer2(modoOperacionT0y2, prescalerT2, modoSalidaA, modoSalidaB)
	configurarTimer2(FAST_PWM_8b, pre2x1024, sClear, sNo);
	//_____________________________________________________________________________________//
	sei();        //Habilitacion global de Interrupciones
	while(1) {
	}
}