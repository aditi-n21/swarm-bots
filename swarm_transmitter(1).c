/*
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   - 
   Analog Joystick or two 10K potentiometers:
   GND to Arduino GND
   VCC to Arduino +5V
   X Pot to Arduino A0
   Y Pot to Arduino A1
   
 - V1.00 11/26/13
   Based on examples at http://www.bajdi.com/
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <OneSheeld.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
int LeftMotorForward = 7; // Pin 10 has Left
int LeftMotorReverse = 6; // Pin 9 has Left Motor
int RightMotorForward = 5; // Pin 12 has Right
int RightMotorReverse = 4; // Pin 13 has Right
// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
float Inch=0.00;
float cm=0.00;
int SonarPin=A5;
int  sensorValue;

/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/
int joystick[1];  // 2 element array holding Joystick readings


void setup()   /****** SETUP: RUNS ONCE ******/
{
    OneSheeld.begin();

//  Serial.begin(57600  );
 pinMode(LeftMotorForward, OUTPUT); //initialize the pin as an output.
pinMode(RightMotorForward, OUTPUT); //initialize the pin as an output.
pinMode(LeftMotorReverse, OUTPUT); // initializethe pin as an output.
pinMode(RightMotorReverse, OUTPUT); //initialize the pin as an output.
    
    pinMode(SonarPin,INPUT);
//Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{


 /* Blink the cursor and for 5 seconds. */
    sensorValue=analogRead(SonarPin);
Inch= (sensorValue*0.497);
cm=Inch*2.54;


 if(GamePad.isUpPressed())
  {
   // forward();
   if(cm<30)
  {
    //for(int i=0;i<1000;i++)
    {
      joystick[0]=3;
    left();
   
    delay(1500);
    }


   // Serial.println("p=0");
  }
  else
  {
    forward();
    joystick[0]=8;
    
   // Serial.println("forward");

  }
  }
  /* If down is pressed, move the car backwards. */
  else if (GamePad.isDownPressed())
  {
   if(cm<30)
  {
  
    {
    left();

        joystick[0]=3;

    delay(1500);
    }


   // Serial.println("p=0");
  }
  else
  {back();
  
        joystick[0]=2;
}
    // Serial.println("back");
}
    
  
  /* If right is pressed, turn the car to the right. */
  else if (GamePad.isRightPressed())
  {
    if(cm<30)
  {
  
    {
              joystick[0]=3;

    left();

    delay(1500);
    }


   // Serial.println("p=0");
  }
  else
  {
            joystick[0]=6;

    right();
   
  }
  }
    /* If left is pressed, turn the car to the left. */
  else if(GamePad.isLeftPressed())
  {
    if(cm<30)
  {
  
    {
              joystick[0]=3;

    left();
 
    delay(1500);
    }


   // Serial.println("p=0");
  }
  else
  {
            joystick[0]=3;

   left();
  
  }
  }
  /* If nothing is pressed stop all motors. */
  else 
  {
  // forward();
          joystick[0]=5;

   Stop();
  
  }

  
 radio.write( joystick, sizeof(joystick) );
 Serial.println(joystick[0]); 


}
//--(end main loop )---

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
