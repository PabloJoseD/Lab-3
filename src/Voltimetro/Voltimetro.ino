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
  
  // Primer canal
  display.setCursor(0, 0);
  display.print("V1:");

  // Segundo canal
  display.setCursor(0, 10);
  display.print("V2:");
  
  // Tercer canal
  display.setCursor(0, 20);
  display.print("V3:");
  
  // Cuarto canal
  display.setCursor(0, 30);
  display.print("V4:");
  
  display.display(); // Actualizar la pantalla
  
}

void loop() {

}