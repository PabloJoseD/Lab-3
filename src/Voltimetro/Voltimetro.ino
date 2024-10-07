#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


// Definir los pines
int RST_PIN = 3;
int CE_PIN  = 4;
int DC_PIN  = 5;
int DIN_PIN = 6;
int CLK_PIN = 7;

int LED_CANAL_1 = 8;
int LED_CANAL_2 = 9;
int LED_CANAL_3 = 10;
int LED_CANAL_4 = 11;

int comunicacion_serial = 2;


// Crear un objeto para la pantalla
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK_PIN, DIN_PIN, DC_PIN, CE_PIN, RST_PIN);


// Definir los pines analógicos donde se conectarán los 4 canales
const int channel1Pin = A5;
const int channel2Pin = A4;
const int channel3Pin = A3;
const int channel4Pin = A2;

// Pin para seleccionar modo de lectura
const int voltageModePin = A1;

bool voltageACModeDetector() {
  // Leer el pin
  int voltageMode = analogRead(voltageModePin);
  // Si la lectura es mayor que la mitad del rango la lectura es AC, caso contrario es DC
  bool voltageIsAC = voltageMode > 512;
  return voltageIsAC;
}

float readVoltage(int pin) {
  // variables necesaria
  float voltage, convertedVoltage, rmsVoltage;
  int analogValue;
  
  if (voltageACModeDetector()) {
    int samples = 200;
    float sumVoltageSquared;
    
    for (int i=0; i<samples; i++){
      analogValue = analogRead(pin); // Leer el valor analógico (0 a 1023)
      // Convertir el valor analógico (0 a 1023) al voltaje de entrada original (-24V a 24V)
      // Relación: 0 a 1023 -> 0V a 5V (en el Arduino)
      voltage = analogValue * (5.0 / 1023.0);
      // Convertir el rango 0-5V al rango -34V a 34V 
      convertedVoltage = (-48/4.79) * voltage + 25.00;
      // Sumatoria de las tensiones al cuadrado
      sumVoltageSquared += convertedVoltage * convertedVoltage; 
      // Frecuencia de muestreo
      delayMicroseconds(83);
    }

    // Con 200 muestras se calcula el rms
    rmsVoltage = sqrt(sumVoltageSquared / samples);
    
    return rmsVoltage;

  } else {

    analogValue = analogRead(pin);  // Leer el valor analógico (0 a 1023)
    
    // Convertir el valor analógico (0 a 1023) al voltaje de entrada original (-24V a 24V)
    // Relación: 0 a 1023 -> 0V a 5V (en el Arduino)
    voltage = analogValue * (5.0 / 1023.0); // Convertir la lectura analógica a voltaje (0-5V)

    // Convertir el rango 0-5V al rango -24V a 24V 
    convertedVoltage = (-48/4.79) * voltage + 25.00;

    return convertedVoltage;
  }
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

  // Configurar pines de los leds
  pinMode(LED_CANAL_1, OUTPUT);
  pinMode(LED_CANAL_2, OUTPUT);
  pinMode(LED_CANAL_3, OUTPUT);
  pinMode(LED_CANAL_4, OUTPUT);
  pinMode(comunicacion_serial, INPUT);

  // Serial monitor
  Serial.begin(9600);
  
}


void mostrar_voltajes(){

  int switch_state = digitalRead(comunicacion_serial);

  // Leer los voltajes de los 4 canales
  float voltage1 = readVoltage(channel1Pin);
  float voltage2 = readVoltage(channel2Pin);
  float voltage3 = readVoltage(channel3Pin);
  float voltage4 = readVoltage(channel4Pin);

  

  if (voltageACModeDetector()){
    

    // Mostrar los valores de voltaje en la pantalla

    display.setCursor(0, 0);
    display.print("MODO AC (Vrms)");

    display.setCursor(0, 10);
    display.print("V1: ");
    display.print(voltage1, 2);  // Mostrar con 2 decimales

    display.setCursor(0, 20);
    display.print("V2: ");
    display.print(voltage2, 2);

    display.setCursor(0, 30);
    display.print("V3: ");
    display.print(voltage3, 2);

    display.setCursor(0, 40);
    display.print("V4: ");
    display.print(voltage4, 2);
   
    if (switch_state == HIGH){
      Serial.print("AC, ");
      Serial.print(voltage1);
      Serial.print(", ");
      Serial.print(voltage2);
      Serial.print(", ");
      Serial.print(voltage3);
      Serial.print(", ");  
      Serial.print(voltage4);
      Serial.println();
    }


    if (voltage1 > 14.2) {
      digitalWrite(LED_CANAL_1, HIGH);  // Encender LED
    } else {
      digitalWrite(LED_CANAL_1, LOW);   // Apagar LED
    }

    // Condición para encender el LED
    if (voltage2 > 14.2) {
      digitalWrite(LED_CANAL_2, HIGH); 
    } else {
      digitalWrite(LED_CANAL_2, LOW);   
    }

    // Condición para encender el LED
    if (voltage3 > 14.2) {
      digitalWrite(LED_CANAL_3, HIGH);  
    } else {
      digitalWrite(LED_CANAL_3, LOW);   
    }

    // Condición para encender el LED
    if (voltage4 > 14.2) {
      digitalWrite(LED_CANAL_4, HIGH);  
    } else {
      digitalWrite(LED_CANAL_4, LOW);   
    }

  } else {

    display.setCursor(0, 0);
    display.print("MODO DC (V)");

    display.setCursor(0, 10);
    display.print("V1: ");
    display.print(voltage1, 2);  // Mostrar con 2 decimales

    display.setCursor(0, 20);
    display.print("V2: ");
    display.print(voltage2, 2);

    display.setCursor(0, 30);
    display.print("V3: ");
    display.print(voltage3, 2);

    display.setCursor(0, 40);
    display.print("V4: ");
    display.print(voltage4, 2);

    if (switch_state == HIGH){
      Serial.print("DC, ");
      Serial.print(voltage1);
      Serial.print(", ");
      Serial.print(voltage2);
      Serial.print(", ");
      Serial.print(voltage3);
      Serial.print(", ");  
      Serial.print(voltage4);
      Serial.println();
    }
    

    if (voltage1 > 14.2) {
      digitalWrite(LED_CANAL_1, HIGH);  // Encender LED
    } else {
      digitalWrite(LED_CANAL_1, LOW);   // Apagar LED
    }

    // Condición para encender el LED
    if (voltage2 < -20 || voltage2 > 20) {
      digitalWrite(LED_CANAL_2, HIGH); 
    } else {
      digitalWrite(LED_CANAL_2, LOW);   
    }

    // Condición para encender el LED
    if (voltage3 < -20 || voltage3 > 20) {
      digitalWrite(LED_CANAL_3, HIGH);  
    } else {
      digitalWrite(LED_CANAL_3, LOW);   
    }

    // Condición para encender el LED
    if (voltage4 < -20 || voltage4 > 20) {
      digitalWrite(LED_CANAL_4, HIGH);  
    } else {
      digitalWrite(LED_CANAL_4, LOW);   
    }
  }

}

void loop() {
  
  // Limpiar la pantalla para actualizar los valores
  display.clearDisplay();
  
  mostrar_voltajes();
  
  display.display(); // Actualizar la pantalla
  
  delay(50); // Actualizar 

}