#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
//#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

MPU6050 mpu6050(Wire);

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

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL; //Remember that this code should be the same for the receiver

RF24 radio(9, 10);  //Set CE and CSN pins

// The sizeof this struct should not exceed 32 bytes
struct Data_to_be_sent {
  byte ch1;
  byte ch2;
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
  
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(my_radio_pipe);

  //Reset each channel value
  sent_data.ch1 = 127; //motor A
  sent_data.ch2 = 127; //motor B
  sent_data.ch3 = 0; //direção
  sent_data.ch4 = 90; //eixo z
  sent_data.ch5 = 90; //eixo Y
//  sent_data.ch6 = 0;
//  sent_data.ch7 = 0;
}

/**************************************************/


void loop(){
  
  mpu6050.update();

  
  //Serial.print("AngleX : ");
  //Serial.print(mpu6050.getAngleX());
  //Serial.print(" - AngleY : ");
  //Serial.print(mpu6050.getAngleY());
  //Serial.print(" - AngleZ : ");
  //Serial.println(mpu6050.getAngleZ());
  
  /*If your channel is reversed, just swap 0 to 255 by 255 to 0 below
  EXAMPLE:
  Normal:    data.ch1 = map( analogRead(A0), 0, 1024, 0, 255);
  Reversed:  data.ch1 = map( analogRead(A0), 0, 1024, 255, 0);  */
  
//  sent_data.ch1 = map( analogRead(A1), 0, 1023, 0, 255);
//  sent_data.ch2 = map( analogRead(A2), 0, 1023, 0, 255);
//  sent_data.ch3 = map( analogRead(A2), 0, 1024, 0, 255);
//  sent_data.ch4 = map( analogRead(A3), 0, 1024, 0, 255);
//  sent_data.ch5 = digitalRead(2);
//  sent_data.ch6 = digitalRead(3);
//  sent_data.ch7 = map( analogRead(A4), 0, 1024, 0, 255);

//  Serial.print("Motor A: ");
//  Serial.print(sent_data.ch1);
//  Serial.print(" - Motor B: ");
//  Serial.println(sent_data.ch2);

//{
  // Print to Serial Monitor
  //Serial.println("Reading motorcontrol values ");
  
  // Read the Joystick X and Y positions
  joyposVert = analogRead(joyVert); 
  joyposHorz = analogRead(joyHorz);
  giroEixoZ = mpu6050.getAngleZ(); //obter dados do eixo z do giroscópio
  giroEixoY = mpu6050.getAngleY(); //obter dados do eixo y do giroscópio
 
  // Determine if this is a forward or backward motion
  // Do this by reading the Verticle Value
  // Apply results to MotorSpeed and to Direction
 
  if (joyposVert < 460)
  {
    // This is Backward
    // Set Motors backward
    motorcontrol[2] = 1;
 
    //Determine Motor Speeds
    // As we are going backwards we need to reverse readings
    motorcontrol[0] = map(joyposVert, 460, 0, 0, 255);
    motorcontrol[1] = map(joyposVert, 460, 0, 0, 255);
 
  }
  else if (joyposVert > 564)
  {
    // This is Forward
    // Set Motors forward
    motorcontrol[2] = 0;
 
    //Determine Motor Speeds
    motorcontrol[0] = map(joyposVert, 564, 1023, 0, 255);
    motorcontrol[1] = map(joyposVert, 564, 1023, 0, 255); 
 
  }
  else
  {
    // This is Stopped
    motorcontrol[0] = 0;
    motorcontrol[1] = 0;
    motorcontrol[2] = 0; 
 
  }
  
  // Now do the steering
  // The Horizontal position will "weigh" the motor speed
  // Values for each motor
 
  if (joyposHorz < 460)
  {
    // Move Left
    // As we are going left we need to reverse readings
    // Map the number to a value of 255 maximum
    joyposHorz = map(joyposHorz, 460, 0, 0, 255);
 
    motorcontrol[0] = motorcontrol[0] - joyposHorz;
    motorcontrol[1] = motorcontrol[1] + joyposHorz;
 
    // Don't exceed range of 0-255 for motor speeds
    if (motorcontrol[0] < 0)motorcontrol[0] = 0;
    if (motorcontrol[1] > 255)motorcontrol[1] = 255;
 
  }
  else if (joyposHorz > 564)
  {
    // Move Right
    // Map the number to a value of 255 maximum
    joyposHorz = map(joyposHorz, 564, 1023, 0, 255);
  
    motorcontrol[0] = motorcontrol[0] + joyposHorz;
    motorcontrol[1] = motorcontrol[1] - joyposHorz;


    // Don't exceed range of 0-255 for motor speeds
    if (motorcontrol[0] > 255)motorcontrol[0] = 255;
    if (motorcontrol[1] < 0)motorcontrol[1] = 0;      
 
  }
 
  // Adjust to prevent "buzzing" at very low speed
  if (motorcontrol[0] < 8)motorcontrol[0] = 0;
  if (motorcontrol[1] < 8)motorcontrol[1] = 0;


  if (giroEixoZ < -90)giroEixoZ = -90;
  if (giroEixoZ > 90)giroEixoZ = 90;
  if (giroEixoY < -90)giroEixoY = -90;
  if (giroEixoY > 90)giroEixoY = 90;

  giroEixoZ = map(giroEixoZ, -90, 90, 0, 180);
  giroEixoY = map(giroEixoY, -90, 90, 0, 180);

  sent_data.ch1 = motorcontrol[0];
  sent_data.ch2 = motorcontrol[1];
  sent_data.ch3 = motorcontrol[2];
  sent_data.ch4 = giroEixoZ;
  sent_data.ch5 = giroEixoY;

  Serial.print("Motor A: ");
  Serial.print(sent_data.ch1);
  Serial.print(" - Motor B: ");
  Serial.print(sent_data.ch2);
  Serial.print(" - Direction: ");
  Serial.print(sent_data.ch3);
  Serial.print(" - Eixo Z: ");
  Serial.print(sent_data.ch4);
  Serial.print(" - Eixo Y: ");
  Serial.println(sent_data.ch5);

  radio.write(&sent_data, sizeof(Data_to_be_sent));

  delay(100);  // Wait a bit before next transmission
}
