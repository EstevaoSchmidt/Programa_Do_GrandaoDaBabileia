const int pin_velocidadeMotorEsq = //nome da porta;
const int pin_velociadeMotorDir = //nome da porta;

const int pin_MotorEsqSentidoHorario = //nome da porta;
const int pin_MotorEsqSentidoAntHorario = //nome da porta;

const int pin_MotorDirSentidoHorario = //nome da porta;
const int pin_MotorDirSentidoAntHorario = //nome da porta;

void setup() {
  
  pinMode(pin_velocidadeMotorEsq, OUTPUT);
  pinMode(pin_velocidadeMotorDir, OUTPUT);

  pinMode(pin_MotorEsqSentidoHorario, OUTPUT);
  pinMode(pin_MotorEsqSentidoAntiHorario, OUTPUT);

  pinMode(pin_MotorDirSentidoHorario, OUTPUT);
  pinMode(pin_MotorDirSentidoAntiHorario, OUTPUT);

}

void loop() {
  
  analogWrite(pin_velocidadeMotorEsq, 255);
  analogWrite(pin_velocidadeMotorDir, 255);

  digitalWrite(pin_MotorEsqSentidoHorario, HIGH);
  digitalWrite(pin_MotorEsqSentidoAntHorario, LOW);
  
  digitalWrite(pin_MotorDirSentidoHorario, HIGH);
  digitalWrite(pin_MotorDirSentidoAntHorario, LOW);

}
