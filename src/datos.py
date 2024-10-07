import serial

# Conectar al puerto serial /tmp/ttyS1
ser = serial.Serial('/tmp/ttyS1', baudrate=9600, timeout=1)

print("Conectado a /tmp/ttyS1.")

try:
    while True:
        # Leer los datos recibidos desde /tmp/ttyS1
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            print(data)
except KeyboardInterrupt:
    print("\nCerrando la conexión...")
    ser.close()

