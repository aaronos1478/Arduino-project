

// Incluimos la librería para la pantalla LCD
#include <LiquidCrystal.h>

// --- Pines de Componentes ---

// Pines de la pantalla LCD
// LiquidCrystal(RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin analógico para el sensor de temperatura (TMP36)
 int pinTemperatura = A0;

// Pin analógico para el potenciómetro (simulador de humedad)//falta sensor humedad 
 int pinHumedad = A1;


void setup() {
  
 
  pinMode(A3, INPUT);
  // Inicializamos la pantalla LCD con 16 columnas y 2 filas
  lcd.begin(16, 2);
  
  // Mensaje de bienvenida
  lcd.print("Estacion Meteo");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  
  // --- LECTURA DE TEMPERATURA ---
  
  // 1. Leemos el valor analógico (0-1023) del TMP36
  int lecturaTemp = analogRead(pinTemperatura);
  
  // 2. Convertimos esa lectura a voltaje (0.0 - 5.0 V)
  //    (lectura / 1023) * 5.0
  float voltajeTemp = lecturaTemp * 5.0 / 1023.0;
  
  // 3. Convertimos el voltaje a grados Celsius
  //    Fórmula del TMP36: (Voltaje - 0.5V de offset) * 100
  float temperaturaC = (voltajeTemp - 0.5) * 100.0;

  
  // --- LECTURA DE HUMEDAD (SIMULADA) ---
  
  // 1. Leemos el valor del sensor de humedad (0-1023)
  int lecturaHum = analogRead(A3);
  Serial.println(lecturaHum);
  
  // 2. Mapeamos ese valor al rango 0-100%
  float humedad = map(lecturaHum, 0, 876, 0, 100);

  
  // --- MOSTRAR DATOS EN LA PANTALLA LCD ---
  
  // 1. Limpiamos la pantalla para la nueva lectura
  lcd.clear();
  
  // 2. Mostramos la Temperatura en la primera fila (fila 0)
  lcd.setCursor(0, 0); // Columna 0, Fila 0
  lcd.print("Temp: ");
  lcd.print(temperaturaC);
  lcd.print(" C");
  
  // 3. Mostramos la Humedad en la segunda fila (fila 1)
  lcd.setCursor(0, 1); // Columna 0, Fila 1
  lcd.print("Hum:  "); 
  lcd.print(humedad);
  lcd.print(" %");
  
  
  // Esperamos 2 segundo antes de volver a medir
  delay(2000);
}