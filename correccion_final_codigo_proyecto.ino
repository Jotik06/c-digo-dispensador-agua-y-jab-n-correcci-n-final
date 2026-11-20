#include <Servo.h>        // Incluye la librería para controlar el servomotor.
#include <LiquidCrystal.h> // Incluye la librería para controlar la pantalla LCD.

// Define los pines de conexión de la pantalla LCD.
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

Servo servo1; // Crea el objeto que permite controlar el servomotor.

// Define los pines de los sensores infrarrojos.
int sensor2 = 8;
int sensor = 11;

int rele1 = 10; // Define el pin de conexión del relé.

int estado = 0; // Variable que almacena el estado de los sensores.

void setup() {
  Serial.begin(9600); // Inicia la comunicación serial a 9600 baudios.

  pinMode(sensor, INPUT);  // Configura el primer sensor como entrada.
  pinMode(sensor2, INPUT); // Configura el segundo sensor como entrada.

  pinMode(rele1, OUTPUT); // Configura el relé como salida.

  servo1.attach(9); // Conecta el servomotor al pin digital 9.

  lcd.begin(16, 2); // Inicializa la pantalla LCD de 16 columnas y 2 filas.
}

void loop() {

  // Lee el estado del primer sensor infrarrojo.
  estado = digitalRead(sensor);

  // Si el sensor detecta las manos (señal LOW):
  if (estado == LOW)
  {
    lcd.clear(); // Limpia la pantalla LCD.

    lcd.setCursor(0, 2); // Ubica el cursor en la pantalla.
    lcd.print("LAVANDO MANOS"); // Muestra el mensaje de lavado.

    digitalWrite(rele1, HIGH); // Activa el relé para permitir el paso del agua.

    delay(5000); // Mantiene el proceso durante 5 segundos.
  }
  else
  {
    lcd.clear(); // Limpia la pantalla LCD.

    lcd.setCursor(0, 3); // Ubica el cursor en la pantalla.
    lcd.print("BIENVENIDOS"); // Muestra el mensaje de bienvenida.

    digitalWrite(rele1, LOW); // Desactiva el relé y detiene el paso del agua.
  }

  // Lee el estado del segundo sensor infrarrojo.
  estado = digitalRead(sensor2);

  // Si el segundo sensor detecta las manos:
  if (estado == LOW)
  {
    delay(2000); // Espera 2 segundos antes de activar el servomotor.

    servo1.write(180); // Gira el servomotor hasta 180 grados.

    delay(1500); // Espera 1,5 segundos.
  }
  else
  {
    servo1.write(0); // Regresa el servomotor a su posición inicial.
  }
}
