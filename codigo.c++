
// ==========================================
// 1. DECLARACION DE VARIABLES Y PINES
// ==========================================

const int BUTTON_PIN = 4;   // Pin donde esta conectado el boton
const int BUZZER_PIN = 15;  // Pin donde esta conectado el buzzer

bool buzzerActivo = true;       // Indica si la sirena esta activa
bool ultimoEstadoBoton = LOW;   // Guarda el estado anterior del boton


// ==========================================
// 2. CONFIGURACION INICIAL
// ==========================================

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configura el boton con resistencia interna
  pinMode(BUZZER_PIN, OUTPUT);       // Configura el buzzer como salida

  Serial.begin(115200);              // Inicia la comunicacion serial
}


// ==========================================
// 3. FUNCION PARA CONTROLAR EL BOTON
// ==========================================

void controlarBoton() {

  int estadoBotonActual = digitalRead(BUTTON_PIN);

  // Detecta cuando se presiona el boton
  if (ultimoEstadoBoton == LOW && estadoBotonActual == HIGH) {

    buzzerActivo = !buzzerActivo; // Invierte el estado de la sirena

    delay(50); // Antirrebote
  }

  ultimoEstadoBoton = estadoBotonActual;
}


// ==========================================
// 4. FUNCION PARA REPRODUCIR LA SIRENA
// ==========================================

void reproducirSirena(int frecuenciaMinima, int frecuenciaMaxima, int incremento) {

  // Aumenta progresivamente la frecuencia
  for (int freq = frecuenciaMinima; freq <= frecuenciaMaxima; freq += incremento) {

    if (digitalRead(BUTTON_PIN) == LOW) break;

    tone(BUZZER_PIN, freq);
    delay(5);
  }

  // Disminuye progresivamente la frecuencia
  for (int freq = frecuenciaMaxima; freq >= frecuenciaMinima; freq -= incremento) {

    if (digitalRead(BUTTON_PIN) == LOW) break;

    tone(BUZZER_PIN, freq);
    delay(5);
  }
}


// ==========================================
// 5. LOGICA PRINCIPAL
// ==========================================

void loop() {

  controlarBoton(); // Verifica si se presiono el boton

  if (buzzerActivo == false) {

    noTone(BUZZER_PIN); // Apaga el buzzer

  } else {

    reproducirSirena(500, 1500, 50); // Reproduce la sirena
  }
}
