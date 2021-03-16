# Control-Robot-by-AVR
Control de robot mediante UART, con cliente en AVR y server en Python.

# Descripción

El proyecto consiste en un sistema que permite la programación de un brazo robótico industrial de forma rápida, sencilla y segura, mediante dispositivos de Interfaz Hombre Máquina (HMI) de uso ameno. Su finalidad es lograr que un usuario final, sin conocimientos de programación ni de robots, logre definir fácilmente el movimiento y todas las acciones necesarias a realizar por un robot físico.

Debido a su versatilidad y aplicación en la industria, decidimos orientar la idea de proyecto a un robot SCARA.

# Detalles

Comunicación Half Duplex por UART, entre la terminal y el Robot.
<img src="https://github.com/cabustillo13/Control-Robot-by-AVR/blob/main/Demo/Robot_Comandos_por_Terminal.png" width="600" height="300">

Mandar línea por línea de un archivo .txt, para ejecutarlas en el Robot. 
En el lado izquierdo de la terminal, se aprecia cada orden que se va ejecutando. 
Opción muy importante para ejecutar rutinas de trabajo.
<img src="https://github.com/cabustillo13/Control-Robot-by-AVR/blob/main/Demo/Robot_Instrucciones_Guardadas.png" width="600" height="300">

Ejecución de ordenes en tiempo real, controlado por el HMI.
<img src="https://github.com/cabustillo13/Control-Robot-by-AVR/blob/main/Demo/Robot_Tiempo_Real.png" width="600" height="300">

# Videos

Para observar a mayor profundidad el ṕroyecto, se adjunta videos de las simulaciones: ![Ver Simulaciones](https://drive.google.com/drive/folders/169MZiRC5xDAeVk2aE5PpOs9e-9WUKLkR)

También se adjunta el informe final: ![Ver Informe](https://github.com/cabustillo13/Control-Robot-by-AVR/blob/main/Proyecto%20de%20MyEP%20-%20Bustillo%20_%20Per%C3%A9z.pdf)

# Autores

- Carlos Bustillo   | cabustillo13@hotmail.com
- Rodrigo Pérez     | rodrigoperez2110@gmail.com
- Marzo 2021
