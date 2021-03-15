#include "main.h"
#include "InterrupcionesINT.h"

void configurarINT0(void) {
	INT0_flancoSubida; //Elige el evento 'Flanco de Subida' para la activacion del flag de INT0.
	flagINT0_OFF; //Es una buena practica apagar el flag de la interrupcion antes de habilitarla.
	INT0_ON; //Habilita la interrupcion externa INT0.
}
void configurarINT1(void) {
	INT1_flancoSubida; //Elige el evento 'Flanco de Subida' para la activacion del flag de INT1.
	flagINT1_OFF; //Es una buena practica apagar el flag de la interrupcion antes de habilitarla.
	INT1_ON; //Habilita la interrupcion externa INT1.
}
