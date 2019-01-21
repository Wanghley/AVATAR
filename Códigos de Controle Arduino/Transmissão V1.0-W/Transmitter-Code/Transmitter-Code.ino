//Programa : Transmissão Robô teleguiado AVATAR
//Autor : Wanghley Soares Martins

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Armazena os dados enviados
int dados[1];

//Inicializa a placa nos pinos 9 (CE) e 10 (CS) do nRF24L01
RF24 radio(9,10);

//Define o endereco para comunicacao entre os modulos
const uint64_t pipe = 0xE14BC8F482LL;

//Define os pinos dos botoes
int frente = 7;
int tras = 6;
int esquerda = 5;
int direita = 4;

void setup()
{
  //Define os botoes como entrada e ativa pull-up
  pinMode(frente,INPUT_PULLUP);
  pinMode(tras,INPUT_PULLUP);
  pinMode(esquerda,INPUT_PULLUP);
  pinMode(direita,INPUT_PULLUP);

  //Inicializa a serial
  Serial.begin(57600);
  Serial.println("Pressione botao 1 ou 2 para iniciar a comunicacao...");
  
  //Inicializa a comunicacao
  radio.begin();
  //Entra em modo de transmissao
  radio.openWritingPipe(pipe);
}

void loop()
{
  if (digitalRead(frente) == LOW)
  {
    Serial.println("Frente pressionado !");
    dados[0] = 1;
    radio.write(dados, 1);
  }
  if (digitalRead(tras) == LOW)
  {
    Serial.println("trás pressionado !");
    dados[0] = 2;
    radio.write(dados, 1);
  }
  if (digitalRead(esquerda) == LOW)
  {
    Serial.println("esquerda pressionado !");
    dados[0] = 3;
    radio.write(dados, 1);
  }
  if (digitalRead(direita) == LOW)
  {
    Serial.println("esquerda pressionado !");
    dados[0] = 4;
    radio.write(dados, 1);
  }
}

