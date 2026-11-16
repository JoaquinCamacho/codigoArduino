
// ==========================================
// 1. DECLARACION DE VARIABLES Y PINES
// ==========================================

// Se declaran las constantes que indican los pines
// donde estan conectados el boton y el buzzer.
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 15;

// Variable que indica si el buzzer esta activo.
// Comienza en true, por lo tanto, la sirena inicia encendida.
bool buzzerActivo = true;

// Guarda el estado anterior del boton para detectar
// cuando se produce un cambio en su estado.
bool ultimoEstadoBoton = LOW;


// ==========================================
// 2. CONFIGURACION INICIAL - SETUP()
// ==========================================

void setup() {

  // Configura el pin del boton como entrada con
  // resistencia pull-up interna.
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Configura el pin del buzzer como salida.
  pinMode(BUZZER_PIN, OUTPUT);

  // Inicia la comunicacion serial a 115200 baudios.
  Serial.begin(115200);
}


// ==========================================
// 3. LOGICA PRINCIPAL - LOOP()
// ==========================================

void loop() {

  // Lee el estado actual del boton.
  int estadoBotonActual = digitalRead(BUTTON_PIN);

  // Detecta el cambio de estado del boton.
  // Si se cumple la condicion, cambia el estado del buzzer.
  if (ultimoEstadoBoton == LOW && estadoBotonActual == HIGH) {

    // Invierte el estado: si estaba activo, lo desactiva
    // y si estaba desactivado, lo activa.
    buzzerActivo = !buzzerActivo;

    // Pequeña pausa para evitar rebotes del boton.
    delay(50);
  }

  // Guarda el estado actual para compararlo
  // con el estado del boton en la siguiente iteracion.
  ultimoEstadoBoton = estadoBotonActual;


  // Verifica si el buzzer debe estar encendido o apagado.
  if (buzzerActivo == false) {

    // Detiene la reproduccion del sonido.
    noTone(BUZZER_PIN);

  }
  else {

    // Si el buzzer esta activo, comienza a reproducir
    // una sirena aumentando progresivamente la frecuencia.

    // Primer recorrido: aumenta la frecuencia desde 500 Hz hasta 1500 Hz.
    for (int freq = 500; freq <= 1500; freq += 50) {

      // Si se presiona el boton, interrumpe el recorrido.
      if (digitalRead(BUTTON_PIN) == LOW) break;

      // Genera un sonido con la frecuencia correspondiente.
      tone(BUZZER_PIN, freq);

      // Pequeña pausa entre cada cambio de frecuencia.
      delay(5);
    }

    // Segundo recorrido: disminuye la frecuencia desde 1500 Hz hasta 500 Hz.
    for (int freq = 1500; freq >= 500; freq -= 50) {

      // Si se presiona el boton, interrumpe el recorrido.
      if (digitalRead(BUTTON_PIN) == LOW) break;

      // Genera un sonido con la frecuencia correspondiente.
      tone(BUZZER_PIN, freq);

      // Pequeña pausa entre cada cambio de frecuencia.
      delay(5);
    }
  }
}
