#include <Servo.h> // Incluye la librería para controlar el servomotor.
#include <LiquidCrystal.h> // Incluye la librería para controlar la pantalla LCD.
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Define los pines de conexión de la pantalla LCD.
Servo servo1; // Crea el objeto que permite controlar el servomotor.

int sensor2 = 8; // Define el pin del sensor infrarrojo para el jabón.
int sensor = 11; // Define el pin del sensor infrarrojo para el agua.
int rele1 = 10; // Define el pin de conexión del relé.
int estado = 0; // Variable que almacena el estado de los sensores.

void setup() {
  
  Serial.begin(9600); // Inicia la comunicación serial a 9600 baudios.
  pinMode(sensor, INPUT);  // Configura el sensor del agua como entrada.
  pinMode(sensor2, INPUT); // Configura el sensor del jabón como entrada.
  pinMode(rele1, OUTPUT); // Configura el relé como salida.
  servo1.attach(9); // Conecta el servomotor al pin digital 9.
  lcd.begin(16, 2); // Inicializa la pantalla LCD de 16 columnas y 2 filas.
}

void loop() {
  
  estado = digitalRead(sensor);// Lee el estado del sensor infrarrojo para el agua.
if (estado == LOW)// Si el sensor del agua detecta las manos (señal LOW), entonces:
  {
    lcd.clear(); // Limpia la pantalla LCD.
    lcd.setCursor(0, 2); // Ubica el cursor en la pantalla LCD.
    lcd.print("LAVANDO MANOS"); // Muestra el mensaje de lavado en la pantalla LCD.
    digitalWrite(rele1, HIGH); // Activa el relé para permitir el paso del agua.
    delay(5000); // Mantiene el proceso de la activación del relé durante 5 segundos.
  }
else
  {
    lcd.clear(); // Limpia la pantalla LCD.
    lcd.setCursor(0, 3); // Ubica el cursor en la pantalla.
    lcd.print("BIENVENIDOS"); // Muestra el mensaje de bienvenida.
    digitalWrite(rele1, LOW); // Desactiva el relé y detiene el paso del agua.
  }
    
  estado = digitalRead(sensor2);// Lee el estado del sensor infrarrojo para el jabón.
if (estado == LOW)// Si el sensor del jabón detecta las manos, entonces:
  {
    delay(2000); // Espera 2 segundos antes de activar el servomotor.
    servo1.write(180); // Gira el servomotor hasta 180 grados.
    delay(1500); // Espera 1,5 segundos.
  }
  else // Si se mantiene HIGH el sensor del jabón, entonces:
  {
    servo1.write(0); // Regresa el servomotor a su posición inicial.
  }
}
