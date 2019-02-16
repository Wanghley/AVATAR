//Programa : Recepção Robô teleguiado AVATAR
//Autor : Wanghley Soares Martins 

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

//Armazena os dados recebidos
int recebidos[1];

//Inicializa na placa nos pinos 9 (CE) e 10 (CS) referentes ao nRF24L01
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;

//motor A
#define enA  6 // PINO PWM
#define in1  7
#define in2  5

//motor B
#define enB  3 // PINO PWM
#define in3  4
#define in4  2

//Servos Pins
#define servoXPin A5
#define servoYPin A4
Servo servox;
Servo servoy;

void setup()
{
  //Inicia as saídas de dados da Ponte H
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  //Define a potência dos motores
  analogWrite(enA,100);
  analogWrite(enB,100);

  //Inicia os servos
  servox.attach(servoXPin);
  servoy.attach(servoYPin);
  servox.write(95);
  servoy.write(75);
  //Inicializa a comunicação
  radio.begin();
  //Entra em modo de recepção de dados
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop()
{
  //Verifica se há sinal de radio
  if (radio.available())
  {
    bool done = false;    
      switch(recebidos[0]){
        case 1:
          delay(5);
          Front();
          break;
        case 2:
          delay(5);
          Back();
          break;
        case 3:
          delay(5);
          Left();
          break;
        case 4:
          delay(5);
          Right();
          break;
        default:
          delay(5);
          TurnOFF();
          break;
      }
  }
}
void TurnOFF(){
  analogWrite(enA,0);
  analogWrite(enB,0);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void Back(){
  analogWrite(enA,100);
  analogWrite(enB,100);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);  
}
void Front(){
  analogWrite(enA,100);
  analogWrite(enB,100);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);  
}
void Left(){
  analogWrite(enA,85.2);
  analogWrite(enB,85.2);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH); 
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);  
}
void Right(){
  analogWrite(enA,85.2);
  analogWrite(enB,85.2);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);  
}
