const int pin_velocidadeMotorEsq = 26;
const int pin_velocidadeMotorDir = 25;

const int pin_MotorEsqSentidoHorario = 14;
const int pin_MotorEsqSentidoAntHorario = 15;

const int pin_MotorDirSentidoHorario = 12;
const int pin_MotorDirSentidoAntHorario = 13;

const int pin_SensorEsq = 0;
const int pin_SensorDir = 4;

int vel = 255;
int velCurva;
int limiar = 800;
int sensorEsq, sensorDir;

void setup() {

  Serial.begin(115200);
  
  pinMode(pin_velocidadeMotorEsq, OUTPUT);
  pinMode(pin_velocidadeMotorDir, OUTPUT);



  pinMode(pin_MotorEsqSentidoHorario, OUTPUT);
  pinMode(pin_MotorEsqSentidoAntHorario, OUTPUT);

  pinMode(pin_MotorDirSentidoHorario, OUTPUT);
  pinMode(pin_MotorDirSentidoAntHorario, OUTPUT);
  
}

void loop() {
  
// paraFrente();

   lerSensores();

   

//Dois 

}


void pararMotores(){
  
///Para motor esquerdo
  digitalWrite(pin_MotorEsqSentidoHorario, HIGH);
  digitalWrite(pin_MotorEsqSentidoAntHorario, HIGH);
///Para motor direito
  digitalWrite(pin_MotorDirSentidoHorario, HIGH);
  digitalWrite(pin_MotorDirSentidoAntHorario, HIGH);
}

void paraFrente(){

  // Configura a velocidade dos Motores
  analogWrite(pin_velocidadeMotorEsq, 255);
  analogWrite(pin_velocidadeMotorDir, 255);

  // Aciona os motores
  digitalWrite(pin_MotorEsqSentidoHorario, HIGH);
  digitalWrite(pin_MotorEsqSentidoAntHorario, LOW);
  digitalWrite(pin_MotorDirSentidoHorario, HIGH);
  digitalWrite(pin_MotorDirSentidoAntHorario, LOW);
      
  
}


void lerSensores(){

  sensorEsq = analogRead(pin_SensorEsq);
  sensorDir = analogRead(pin_SensorDir);


  Serial.println("Sensor Esquerdo: "+ String(sensorEsq));
  Serial.println("Sensor Direito: "+ String(sensorDir));
  delay(2000);





//  if(sensorDir < limiar){
//    pararMotores();
//  }

  if(sensorEsq < limiar){
//    pararMotores();
  }

  if(sensorEsq > limiar){
//    paraFrente();
  }

  
}
