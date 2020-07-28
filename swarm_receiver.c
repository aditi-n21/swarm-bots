/* YourDuinoStarter Example: nRF24L01 Receive Joystick values

 - WHAT IT DOES: Receives data from another transceiver with
   2 Analog values from a Joystick or 2 Potentiometers
   Displays received values on Serial Monitor
 - SEE the comments after "//" on each line below
 - CONNECTIONS: nRF24L01 Modules See:
 http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   
 - V1.00 11/26/13
   Based on examples at http://www.bajdi.com/
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10
int LeftMotorForward = 7; // Pin 10 has Left
int LeftMotorReverse = 6; // Pin 9 has Left Motor
int RightMotorForward = 5; // Pin 12 has Right
int RightMotorReverse = 4; // Pin 13 has Right
int p = 3;

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe


/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/
int joystick[1];  // 2 element array holding Joystick readings

void setup()   /****** SETUP: RUNS ONCE ******/
{
   pinMode(LeftMotorForward, OUTPUT); //initialize the pin as an output.
pinMode(RightMotorForward, OUTPUT); //initialize the pin as an output.
pinMode(LeftMotorReverse, OUTPUT); // initializethe pin as an output.
pinMode(RightMotorReverse, OUTPUT); //initialize the pin as an output.
pinMode(p, INPUT);

  Serial.begin(9600);
  delay(1000);
  Serial.println("Nrf24L01 Receiver Starting");
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();;
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  if ( radio.available() )
  {
    // Read the data payload until we've received everything
    bool done = false;
    while (!done)
    {
      // Fetch the data payload
      done = radio.read( joystick, sizeof(joystick) );
      //Serial.println("X = ");
     /* if(joystick[0]==10)
      {
        digitalWrite(2,HIGH);
      }*/
      Serial.println(joystick[0]);
      //Serial.print(" Y = ");      
      //Serial.println(joystick[1]);*/
      
      
      
       if(joystick[0]==8)
  {
     forward();
  
  if(digitalRead(p)==0)
{
  left();
}
   
  }
  /* If down is pressed, move the car backwards. */
  else if (joystick[0]==2)
  {
   back();
        
}
    // Serial.println("back");

    
  
  /* If right is pressed, turn the car to the right. */
  else if (joystick[0]==6)
  {
   

   // Serial.println("p=0");
         

    right();
  
  }
    /* If left is pressed, turn the car to the left. */
  else if(joystick[0]==4)
  {
            

   left();
  
  }
  else if (joystick[0]==3)
  {
   left();
        
}
  /* If nothing is pressed stop all motors. */
  else 
  {
  // forward();

   Stop();
  }


      
      
      
      
    }
  }
  else
  {    
      Serial.println("No radio available");
              digitalWrite(2,LOW);

  }

}//--(end main loop )---

/*-----( Declare User-written Functions )-----*/

//NONE
//*********( THE END )***********
void forward()
{
digitalWrite(RightMotorForward, HIGH); // turnthe Right Motor ON
digitalWrite(LeftMotorForward, HIGH); 
}

void back()
{
  digitalWrite(RightMotorReverse, HIGH); // turnthe Right Motor ON
digitalWrite(LeftMotorReverse, HIGH); 

}
void Stop()
{
 digitalWrite(RightMotorForward,LOW); // turn Right Motor OFF
 digitalWrite(LeftMotorForward, LOW);  
}

void left()
{
  digitalWrite(RightMotorForward,LOW); // turn Right Motor OFF
 digitalWrite(LeftMotorForward, HIGH);  
}

void right()
{
  digitalWrite(RightMotorForward,HIGH); // turn Right Motor OFF
 digitalWrite(LeftMotorForward, LOW);  
}

void softright()
{
digitalWrite(RightMotorForward,HIGH); // turn Right Motor OFF
 digitalWrite(LeftMotorReverse, HIGH);   
}
void softleft()
{
digitalWrite(RightMotorReverse,HIGH); // turn Right Motor OFF
 digitalWrite(LeftMotorForward, HIGH);   
}
