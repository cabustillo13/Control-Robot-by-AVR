# Control-Robot-by-AVR
Control de robot mediante UART, con cliente en AVR y server en Python.

# Descripción

El proyecto consiste en un sistema que permite la programación de un brazo robótico industrial de forma rápida, sencilla y segura, mediante dispositivos de Interfaz Hombre Máquina (HMI) de uso ameno. Su finalidad es lograr que un usuario final, sin conocimientos de programación ni de robots, logre definir fácilmente el movimiento y todas las acciones necesarias a realizar por un robot físico.

Debido a su versatilidad y aplicación en la industria, decidimos orientar la idea de proyecto a un robot SCARA.

# Detalles

Se aprecia la comunicación Half Duplex por UART, entre la terminal y el Robot.
<img src="https://github.com/cabustillo13/Control-Robot-by-AVR/blob/main/Demo/Robot_Comandos_por_Terminal.png" width="600" height="300">

Se tiene un archivo .txt con distintas órdenes a ejecutarse línea por línea en el Robot. En el lado izquierdo de la terminal, se aprecia cada orden que se va ejecutando. Opción muy importante para ejecutar rutinas de trabajo.
<img src="https://github.com/cabustillo13/Control-Robot-by-AVR/blob/main/Demo/Robot_Instrucciones_Guardadas.png" width="600" height="300">
