

// ================================
// ROBÔ SUMÔ - ESP32 + L298N
// Motores + sensores de linha
// ================================

// ----- Motor esquerdo -----
#define ENA 26
#define IN1 15
#define IN2 14

// ----- Motor direito -----
#define ENB 25
#define IN3 12
#define IN4 13

// ----- Sensores de linha -----
#define SENSOR_ESQUERDO 16
#define SENSOR_DIREITO 4

//----- Sensores de Frente ------

#define SENSOR_ESQUERDO_FRENTE 35
#define SENSOR_DIREITO_FRENTE 34

// Velocidade dos motores (0 a 255)
int velocidade = 68;


// ================================
// CONFIGURAÇÃO
// ================================
void setup() {

  Serial.begin(115200);

  // Motores
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Sensores
  pinMode(SENSOR_ESQUERDO, INPUT);
  pinMode(SENSOR_DIREITO, INPUT);

  pinMode(SENSOR_ESQUERDO_FRENTE, INPUT);
  pinMode(SENSOR_DIREITO_FRENTE, INPUT);

  // Garante que o robô fique parado
  parar();

  Serial.println("================================");
  Serial.println("       ROBÔ SUMÔ");
  Serial.println("================================");
  Serial.println("Iniciando em:");

  // Contagem regressiva de 10 segundos
  for (int i = 10; i > 0; i--) {

    Serial.print(i);
    Serial.println("...");

    delay(1000);
  }

  Serial.println("VALENDO!");
}


// ================================
// LOOP PRINCIPAL
// ================================
void loop() {

  // Leitura dos sensores
  int esquerdo = digitalRead(SENSOR_ESQUERDO);
  int direito = digitalRead(SENSOR_DIREITO);

  Serial.print("Sensor esquerdo: ");
  Serial.print(esquerdo);

  Serial.print(" | Sensor direito: ");
  Serial.println(direito);

  float valorSensorEsq = analogRead(SENSOR_ESQUERDO_FRENTE);
  int cmSensorEsq = 13*pow(valorSensorEsq * 0.0048828125 , -1);
  Serial.print("Valor lido ESQ = ");
  Serial.print(valorSensorEsq);
  Serial.println(" cm");

  float valorSensorDir = analogRead(SENSOR_DIREITO_FRENTE);
  int cmSensorDir = 13*pow(valorSensorDir * 0.0048828125 , -1);
  Serial.print("Valor lido DIR = ");
  Serial.print(valorSensorDir);
  Serial.println(" cm");

  delay(500);
  // ========================================
  // OS DOIS SENSORES DETECTARAM A LINHA
  // ========================================
  if (esquerdo == LOW && direito == LOW) {

    Serial.println("!!! LINHA NOS DOIS SENSORES !!!");

    // Para
    //parar();

    // Recuar
    tras(velocidade);
//    delay(500);

    // Girar para a direita
    direita(velocidade);
//    delay(350);

    // Para
    parar();
  }


  // ========================================
  // SENSOR ESQUERDO DETECTOU A LINHA
  // ========================================
  else if (esquerdo == LOW) {

    Serial.println("!!! LINHA NO SENSOR ESQUERDO !!!");

    // Para
    //parar();

    // Recuar um pouco
    tras(velocidade);
//    delay(500);

    // Girar para a direita
    direita(velocidade);
//    delay(350);

    // Para
    parar();
  }


  // ========================================
  // SENSOR DIREITO DETECTOU A LINHA
  // ========================================
  else if (direito == LOW) {

    Serial.println("!!! LINHA NO SENSOR DIREITO !!!");

    // Para
    //parar();

    // Recuar um pouco
    tras(velocidade);
//    delay(500);

    // Girar para a esquerda
    esquerda(velocidade);
//    delay(350);

    // Para
    parar();
  }

  
  


  // ========================================
  // NENHUMA LINHA DETECTADA
  // ========================================
  else {
    frente(velocidade);
  }

  if((cmSensorEsq >= 4 && cmSensorEsq <= 30) && (cmSensorEsq < cmSensorDir)){

    direita(velocidade);
    Serial.println("direito");
//    delay(200);
    
  }

  else if((cmSensorDir >= 4 && cmSensorDir <= 30) && (cmSensorDir < cmSensorEsq)){

    esquerda(velocidade);
    Serial.println("esquerdo");
//    delay(200);
  }
  
  // Pequena pausa
  delay(20);
}


// ================================
// FRENTE
// ================================
void frente(int vel) {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}


// ================================
// TRÁS
// ================================
void tras(int vel) {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, vel * 1.2);
  analogWrite(ENB, vel * 1.2);
}


// ================================
// GIRAR PARA A ESQUERDA
// ================================
void esquerda(int vel) {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}


// ================================
// GIRAR PARA A DIREITA
// ================================
void direita(int vel) {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}


// ================================
// PARAR
// ================================
void parar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
