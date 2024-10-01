#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


// Definir los pines
int RST_PIN = 3;
int CE_PIN  = 4;
int DC_PIN  = 5;
int DIN_PIN = 6;
int CLK_PIN = 7;


// Crear un objeto para la pantalla
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK_PIN, DIN_PIN, DC_PIN, CE_PIN, RST_PIN);


// Definir los pines analógicos donde se conectarán los 4 canales
const int channel1Pin = A5;
const int channel2Pin = A4;
const int channel3Pin = A3;
const int channel4Pin = A2;


float readVoltage(int pin) {
  int analogValue = analogRead(pin);  // Leer el valor analógico (0 a 1023)
  
  // Convertir el valor analógico (0 a 1023) al voltaje de entrada original (-24V a 24V)
  // Relación: 0 a 1023 -> 0V a 5V (en el Arduino)
  float voltage = analogValue * (5.0 / 1023.0); // Convertir la lectura analógica a voltaje (0-5V)

  // Convertir el rango 0-5V al rango -24V a 24V 
   float convertedVoltage = (-48/4.79) * voltage + 25.00;

  return convertedVoltage;
}

void setup() {
  // Iniciar la pantalla
  display.begin();
  
  // Configurar el contraste
  display.setContrast(50);
  
  // Limpiar la pantalla
  display.clearDisplay();
  
  // Texto
  display.setTextSize(1);
  display.setTextColor(BLACK);
  
}

void loop() {

  // Leer los voltajes de los 4 canales
  float voltage1 = readVoltage(channel1Pin);
  float voltage2 = readVoltage(channel2Pin);
  float voltage3 = readVoltage(channel3Pin);
  float voltage4 = readVoltage(channel4Pin);
  
  // Limpiar la pantalla para actualizar los valores
  display.clearDisplay();
  
  // Mostrar los valores de voltaje en la pantalla
  display.setCursor(0, 0);
  display.print("V1: ");
  display.print(voltage1, 2);  // Mostrar con 2 decimales

  display.setCursor(0, 10);
  display.print("V2: ");
  display.print(voltage2, 2);

  display.setCursor(0, 20);
  display.print("V3: ");
  display.print(voltage3, 2);

  display.setCursor(0, 30);
  display.print("V4: ");
  display.print(voltage4, 2);
  
  display.display(); // Actualizar la pantalla
  
  delay(100); // Actualizar 

}