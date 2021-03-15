#ifndef INTERRUPCIONESINT_H_
#define INTERRUPCIONESINT_H_

#define INT0_ON				 (EIMSK |=  (1<<INT0))	//Habilita la interrupcion externa en INT0 (Pin Digital 2)
#define INT0_OFF			 (EIMSK &=~ (1<<INT0))	//-
#define flagINT0_OFF		 (EIFR  &=~ (1<<INTF0)) //Apaga el Flag de la interrupcion externa en INT0 (Pin Digital 2)
#define INT0_test 			 (PIND   &  (1<<PIND2)) //Verifica si INT0 (Pin Digital 2) se encuentra en alto
#define INT0_nivelBajo       (EICRA &=~ (3<<ISC00))	//-
#define INT0_cualquierFlanco (EICRA |=  (1<<ISC00))	//-
#define INT0_flancoBajada    (EICRA |=  (2<<ISC00))	//-
#define INT0_flancoSubida    (EICRA |=  (3<<ISC00)) //Elige el evento 'Flanco de Subida' para la activacion del flag de INT0

#define INT1_ON				 (EIMSK |=  (1<<INT1))	//Habilita la interrupcion externa en INT1 (Pin Digital 3)
#define INT1_OFF			 (EIMSK &=~ (1<<INT1))	//-
#define flagINT1_OFF		 (EIFR  &=~ (1<<INTF1)) //Apaga el Flag de la interrupcion externa en INT1 (Pin Digital 3)
#define INT1_test			 (PIND   &  (1<<PIND3)) //Verifica si INT1 (Pin Digital 3) se encuentra en alto
#define INT1_nivelBajo       (EICRA &=~ (3<<ISC10))	//-
#define INT1_cualquierFlanco (EICRA |=  (1<<ISC10))	//-
#define INT1_flancoBajada    (EICRA |=  (2<<ISC10))	//-
#define INT1_flancoSubida    (EICRA |=  (3<<ISC10)) //Elige el evento 'Flanco de Subida' para la activacion del flag de INT1

void configurarINT0(void);
void configurarINT1(void);

#endif /* INTERRUPCIONESINT_H_ */