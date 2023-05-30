#include <TimeLib.h>

// Incluimos la librería Stepper
#include <Stepper.h>

// Definimos los pines de conexión al módulo de control del motor paso a paso
const int motorPin1 = 8;
const int motorPin2 = 9;
const int motorPin3 = 10;
const int motorPin4 = 11;

// Configuramos el número de pasos por revolución del motor
const int stepsPerRevolution = 200;

// Creamos un objeto Stepper
Stepper myStepper(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4);

// Variables para controlar el tiempo
unsigned long tiempoInicio;
const unsigned long duracionMovimiento = 5000;  // Duración del movimiento en milisegundos (5 segundos)

void setup() {
  // Inicializamos la comunicación serie
  Serial.begin(9600);

  // Establecemos la velocidad del motor (en RPM)
  myStepper.setSpeed(185);
}

void loop() {
  // Verificamos si es la hora programada para el movimiento (7:00 AM)
  if (esHoraProgramada(7, 0, 0)) {
    // Si es la hora programada, iniciamos el movimiento del motor
    if (tiempoInicio == 0) {
      tiempoInicio = millis();  // Guardamos el tiempo de inicio
      Serial.println("Girando en una dirección...");
    }

    // Verificamos si ha pasado el tiempo de movimiento
    if (millis() - tiempoInicio >= duracionMovimiento) {
      // Si ha pasado el tiempo, detenemos el motor
      myStepper.step(0);
      tiempoInicio = 0;  // Reiniciamos el tiempo de inicio para la próxima vez
      Serial.println("Motor detenido");
    } else {
      // Realizamos una vuelta completa (200 pasos) en sentido horario
      myStepper.step(stepsPerRevolution);
    }
  }
}

// Función para verificar si es la hora programada
bool esHoraProgramada(int hora, int minuto, int segundo) {
  // Obtenemos la hora actual
  int horaActual = hour();
  int minutoActual = minute();
  int segundoActual = second();
  
  Serial.println(segundoActual);

  // Verificamos si coincide con la hora programada
  if (horaActual == hora && minutoActual == minuto && segundoActual == segundo) {
    return true;
  } else {
    return false;
  }
}
