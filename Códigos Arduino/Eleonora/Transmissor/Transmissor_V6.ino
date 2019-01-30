//#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
//#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

//MPU6050 mpu6050(Wire);

/* Tranmsitter code for the Arduino Radio control with PWM output
 * Install the NRF24 library to your IDE
 * Upload this code to the Arduino UNO, NANO, Pro mini (5V,16MHz)
 * Connect a NRF24 module to it:
 
    Module // Arduino UNO,NANO
    
    GND    ->   GND
    Vcc    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12

This code transmits 7 channels with data from pins A0, A1, A2, A3, D2 and D3
Please, like share and subscribe : https://www.youtube.com/c/ELECTRONOOBS
*/

// Define Joystick Connections
#define joyVert    A0 
#define joyHorz    A1
 
// Define Joystick Values - Start at 512 (middle position)
int joyposVert = 512;
int joyposHorz = 512;
int giroEixoZ = 90;
int giroEixoY = 90;
int x,y;

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; //Remember that this code should be the same for the receiver

RF24 radio(9, 10);  //Set CE and CSN pins

// The sizeof this struct should not exceed 32 bytes
struct Data_to_be_sent {
  int ch1;
  int ch2;
  byte ch3;
  byte ch4;
  byte ch5;
//  byte ch6;
//  byte ch7;
};

//Create a variable with the structure above and name it sent_data
Data_to_be_sent sent_data;

// Declare unsigned 8-bit motorcontrol array
// 2 Bytes for motor speeds plus 1 byte for direction control
uint8_t motorcontrol[3];

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);
  Wire.begin();
  
 // mpu6050.begin();
 // mpu6050.calcGyroOffsets(true);
  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(my_radio_pipe);

  //Reset each channel value
  sent_data.ch1 = 127; //motor A
  sent_data.ch2 = 127; //motor B
  //sent_data.ch3 = 0; //direção
  //sent_data.ch4 = 90; //eixo z
  //sent_data.ch5 = 90; //eixo Y
//  sent_data.ch6 = 0;
//  sent_data.ch7 = 0;
}

/**************************************************/


void loop(){
  
  joyposVert = analogRead(joyVert); 
  joyposHorz = analogRead(joyHorz);
  
 
  x=map(joyposHorz, 1023, 0, -255, 255);
  y=map(joyposVert, 1023, 0, -255, 255);
  


  sent_data.ch1 = x;
  sent_data.ch2 = y;
 // sent_data.ch3 = motorcontrol[2];
 // sent_data.ch4 = giroEixoZ;
 // sent_data.ch5 = giroEixoY;

  Serial.print("Motor A: ");
  Serial.print(sent_data.ch1);
  Serial.print(" - Motor B: ");
  Serial.println(sent_data.ch2);
 // Serial.print(" - Direction: ");
//  Serial.print(sent_data.ch3);
 // Serial.print(" - Eixo Z: ");
 // Serial.print(sent_data.ch4);
 // Serial.print(" - Eixo Y: ");
 // Serial.println(sent_data.ch5);

  radio.write(&sent_data, sizeof(Data_to_be_sent));

  delay(100);  // Wait a bit before next transmission
}
