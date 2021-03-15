#!/usr/bin/env python3
import socket
import time
import serial

###################################################
## Obtener informacion por TCP/IP de cada sensor ##
###################################################

def controlRobot(flag):
    if (flag == True):
        # Articulacion 0
        HOST0 = '192.168.1.130'       # The server's hostname or IP address
        PORT0 = 65430                # The port used by the server

        # Articulacion 1 y 2
        HOST1 = '192.168.1.131'       # The server's hostname or IP address
        PORT1 = 65431                # The port used by the server

        # Articulacion 3 y 4
        HOST3 = '192.168.1.133'       # The server's hostname or IP address
        PORT3 = 65433                # The port used by the server

        while(True):
            
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s0:
                s0.connect((HOST0, PORT0))
                
                #Dato recibido
                data0 = float(s0.recv(1024))
            
                #La simulacion acepta radianes
                dataR0 = data0*2.22
            
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s1:
                s1.connect((HOST1, PORT1))
                
                #Dato recibido
                data = (s1.recv(1024))
                dataV = data.decode('ASCII')
                
                #Separar el string en partes
                dataN = dataV.split("/")
                
                #Altura Gripper
                data1 =float(dataN[0])
                #Apertura y cierre Gripper
                data2 =float(dataN[1])
                
                #print(float(data3), float(data4))
                
                #La simulacion acepta radianes
                dataR1 = data1*2.22
                #Escalamos los valores de la altura para evitar romper la simulacion
                dataR2 = data2*2.22
                
                #Movimiento relativo
                dataRR1 = dataR1 - dataR0
                dataRR2 = dataR2 - dataR1 - dataR0
            
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s3:
                s3.connect((HOST3, PORT3))
                
                #Dato recibido
                data = (s3.recv(1024))
                dataV = data.decode('ASCII')
                
                #Separar el string en partes
                dataN = dataV.split("/")
                
                #Altura Gripper
                data3 =float(dataN[0])
                #Apertura y cierre Gripper
                data4 =float(dataN[1])
                
                #print(float(data3), float(data4))
                
                #La simulacion acepta radianes
                dataR3 = data3
                #Escalamos los valores de la altura para evitar romper la simulacion
                dataR4 = data4*2.22
            
            #Concatenar datos
            cadena = str(dataR0) + str("/") + str(dataRR1) + str("/") + str(dataRR2) + str("/") + str(dataR3) + str("/") + str(dataR4) + "\n"
            
            #Guardar instrucciones
            archivo = open('instrucciones.txt', 'a')  
            archivo.write(cadena)
            archivo.close()         
    else:
        print("Proceso terminado")

###################################
## Enviar informacion al Arduino ##
###################################

def sendArduino():
    
    #Puerto Serial Arduino
    #Arduino Nano
    puerto = "/dev/ttyUSB0"
    
    #Leer cada linea del txt
    f = open("instrucciones.txt", "r")
    lineas = f.readlines()
    cantidadLineas = len(lineas)
    f.close()
    
    with serial.Serial(puerto, 9600, bytesize=8, parity='N', stopbits=2) as ser:
        
            for i in range(cantidadLineas):
            
                #Enviar al Arduino
                dato = (lineas[i]).rstrip("\n")
                ser.write(bytes(dato + "\r" ,'utf-8'))
                
                print(dato + "\r")
                time.sleep(1.5)
            
            print("Listo") 
            time.sleep(4)
            
###############################################
## Realizar Test -> Comunicación Half Duplex ##
###############################################

def test():
    #Para Arduino Uno
    #port = '/dev/ttyACM0'
    
    #Para Arduino Nano
    port = '/dev/ttyUSB0'
    
    with serial.Serial(port, 9600, bytesize=8, parity='N', stopbits=1) as ser:
        
        
        # Al inicio recibimos 9 mensajes de parte del Arduino
        for i in range(9):
            
            # Si la linea que estoy leyendo no tiene \n se queda esperando
            line = ser.readline()   # read a '\n' terminated line
            # Hacemos la conversion de bit -> string
            print(line.decode(encoding='UTF-8',errors='strict'))
            time.sleep(1)
            
        while(1):
            # Enviar comandos
            data = input("Ingrese orden: ")
            ser.write(bytes(data + "\r",'utf-8'))
            print("Enviado")
            time.sleep(1)
            
            #Si la linea que estoy leyendo no tiene \n se queda esperando
            line = ser.readline()   #
            print(line.decode(encoding='UTF-8',errors='strict'))
            time.sleep(1)
                    
        #ser.close()

###############
## Real Time ##
###############

def realTime(flag):
    if (flag == True):
        
        #Arduino Uno
        #puerto = '/dev/ttyACM0'
        
        #Arduino Nano
        puerto = '/dev/ttyUSB0'
        with serial.Serial(puerto, 9600, bytesize=8, parity='N', stopbits=1) as ser:
        
            while(1):
                # Articulacion 0
                HOST0 = '192.168.1.130'       # The server's hostname or IP address
                PORT0 = 65430                # The port used by the server

                # Articulacion 1 y 2
                HOST1 = '192.168.1.131'       # The server's hostname or IP address
                PORT1 = 65431                # The port used by the server

                # Articulacion 3 y 4
                HOST3 = '192.168.1.133'       # The server's hostname or IP address
                PORT3 = 65433                # The port used by the server

                while(True):
                    
                    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s0:
                        s0.connect((HOST0, PORT0))
                        
                        #Dato recibido
                        data0 = float(s0.recv(1024))
                        
                        #print("data0: ", data0)
                        ser.write(bytes(":B" + str(data0) + "\r",'utf-8'))
                        #time.sleep(0.1)
                    
                    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s1:
                        s1.connect((HOST1, PORT1))
                        
                        #Dato recibido
                        data = (s1.recv(1024))
                        dataV = data.decode('ASCII')
                        
                        #Separar el string en partes
                        dataN = dataV.split("/")
                        
                        #Altura Gripper
                        data1 =float(dataN[0])
                        #Apertura y cierre Gripper
                        data2 =float(dataN[1])
                        
                        print("data1: ", data1)
                        print("data2: ", data2)
                        
                        
                        ser.write(bytes(":M" + str(data1) + "\r",'utf-8'))
                        #time.sleep(0.1)
                        
                        ser.write(bytes(":G" + str(data2) + "\r",'utf-8'))
                        #time.sleep(0.1)
                        
                    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s3:
                        s3.connect((HOST3, PORT3))
                        
                        #Dato recibido
                        data = (s3.recv(1024))
                        dataV = data.decode('ASCII')
                        
                        #Separar el string en partes
                        dataN = dataV.split("/")
                        
                        #Altura Gripper
                        data3 =float(dataN[0])
                        #Apertura y cierre Gripper
                        data4 =float(dataN[1])
                        
                        #print(float(data3), float(data4))

                        print("data3: ", data3)
                        print("data4: ", data4)

                        ser.write(bytes(":A" + str(data3) + "\r",'utf-8'))
                        #time.sleep(0.1)
                        
                        ser.write(bytes(":C" + str(data4)+ "\r",'utf-8'))
                        #time.sleep(0.1)
                    
                    print("Ordenes enviadas")
                    #ser.close()
    else:
        print("Proceso terminado")
