import serial

# Conectar al puerto serial /tmp/ttyS1
ser = serial.Serial('/tmp/ttyS1', baudrate=9600, timeout=1)

# Nombre del archivo donde se guardarán los datos
filename = 'datos_voltimetro.csv'

# Crear o sobrescribir el archivo al inicio
with open(filename, 'w') as file:
    file.write('Modo, Canal1, Canal2, Canal3, Canal4\n')  

print("Conectado a /tmp/ttyS1. Esperando datos...")

try:
    while True:
        # Leer los datos recibidos desde /tmp/ttyS1
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            print(data)
            
            # Abrir el archivo en modo escritura y agregar los datos
            with open(filename, 'a') as file:
                file.write(data + '\n')  # Escribir data en el archivo
except KeyboardInterrupt:
    print("\nCerrando la conexión...")
    ser.close()



