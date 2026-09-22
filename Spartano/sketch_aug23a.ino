

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

#define BRANCO 0
#define PRETO 1

//----- Sensores de Frente ------

#define SENSOR_ESQUERDO_FRENTE 34
#define SENSOR_DIREITO_FRENTE 35

// Velocidade dos motores (0 a 255)
int velocidadeFrenteEsq = 50;
int velocidadeFrenteDir = 65; //Compensaço de 30% na velocidade do motor
int velocidadeRe = 70;

// Delay para funcionamento dos motores
int tempoDelay = 500;

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

  //Serial.print("Sensor esquerdo: ");
  //Serial.print(esquerdo);

  //Serial.print(" | Sensor direito: ");
  //Serial.println(direito);


  float valorSensorEsq = analogRead(SENSOR_ESQUERDO_FRENTE);
  float cmSensorEsq = 13*pow(valorSensorEsq * 0.0048828125 , -1);
  Serial.print("Valor lido sensor esq = ");
  Serial.print(cmSensorEsq*5);
  Serial.println(" cm");
//  delay(250);

  float valorSensorDir = analogRead(SENSOR_DIREITO_FRENTE);
  float cmSensorDir = 13*pow(valorSensorDir * 0.0048828125 , -1);
  Serial.print("Valor lido sensor dir= ");
  Serial.print(cmSensorDir*5);
  Serial.println(" cm");
//  delay(250);

//  delay(500);

  /*
   * IF adversario perto (testar se está a frente, a direita ou a esquerda)
   *    acelerar enquanto possui adversário perto
   *    - frente, direita ou esquerdaá
   *    
   * ELSE 
   *    manter-se seguro (código abaixo)
   * 
   * 
   * 
   */


  // ========================================
  // OS DOIS SENSORES DETECTARAM A LINHA
  // ========================================
  
  if (esquerdo == BRANCO && direito == BRANCO) {

    Serial.println("!!! LINHA NOS DOIS SENSORES !!!");

    // Para
    parar();

    // Recuar
    tras(velocidadeRe);
    delay(tempoDelay);

    // Girar para a direita
    direita(velocidadeFrenteEsq, velocidadeFrenteDir);
    delay(tempoDelay);

    // Para
    parar();
  }


  // ========================================
  // SENSOR ESQUERDO DETECTOU A LINHA
  // ========================================
  else if (esquerdo == BRANCO) {

    Serial.println("!!! LINHA NO SENSOR ESQUERDO !!!");

    // Para
    parar();

    // Recuar um pouco
    tras(velocidadeRe);
    delay(tempoDelay);

    // Girar para a direita
    direita(velocidadeFrenteEsq, velocidadeFrenteDir);
    delay(tempoDelay);

    // Para
    parar();
  }


  // ========================================
  // SENSOR DIREITO DETECTOU A LINHA
  // ========================================
  else if (direito == BRANCO) {

    Serial.println("!!! LINHA NO SENSOR DIREITO !!!");

    // Para
    parar();

    // Recuar um pouco
    tras(velocidadeRe);
    delay(tempoDelay);

    // Girar para a esquerda
    esquerda(velocidadeFrenteEsq, velocidadeFrenteDir);
    delay(tempoDelay);

    // Para
    parar();
  }

  
  


  // ========================================
  // NENHUMA LINHA DETECTADA
  // ========================================
  else {
    frente(velocidadeFrenteEsq, velocidadeFrenteDir);
  }
/*
  if(cmSensorEsq < cmSensorDir){

    //esquerda(velocidade);
    Serial.println("direito é maior");
    
  }

  else if(cmSensorDir < cmSensorEsq){

    //direita(velocidade);
    Serial.println("esquerdo é maior");
  }

  else {
    
    //frente(velocidade);
    }
  */
  // Pequena pausa
//  delay(20);
}


// ================================
// FRENTE
// ================================
void frente(int velEsq, int velDir) {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velEsq);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, velDir);
}


// ================================
// TRÁS
// ================================
void tras(int vel) {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, vel * 1.2);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, vel * 1.2);
}


// ================================
// GIRAR PARA A ESQUERDA
// ================================
void esquerda(int velEsq, int velDir) {

  //Frente
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velDir);

  //Trás
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);  
  analogWrite(ENB, velEsq);
}


// ================================
// GIRAR PARA A DIREITA
// ================================
void direita(int velEsq, int velDir) {

  //Trás
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velEsq);

  //Frente
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, velDir);
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

// ================================
// 
// ================================
