#include <VirtualWire.h>
#include <VirtualWire_Config.h>

int state=0;
char *data;
const int inputPin1 =2;    // Pin 15 of L293D IC
const int inputPin2 =3;
const int inputPin3 =5;
const int inputPin4 =4;
void setup() 
{
  Serial.begin(38400);
 // vw_set_ptt_inverted(true); //
vw_set_tx_pin(12);
vw_setup(2000);// speed of data transfer Kbps

pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
      
  // put your setup code here, to run once:

}

void loop()
{
  if(Serial.available()>0)
  {
    state=Serial.read();
    Serial.println(state);
  }

  if(state=='F')
  {
    
    data="1" ;
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx(); // Wait until the whole message is gone
    forward() ;
    
  }

  if(state=='S')
  {
    data="3";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx(); // Wait until the whole message is gone
    stops() ;
    
  }

  if(state=='B')
  {
    data="0" ;
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx(); // Wait until the whole message is gone
    backward();
    
  }

  

    if(state=='L')
    {
    data="4";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx(); // Wait until the whole message is gone
    left() ;
   
    }

    if(state=='R')
    {
    data="2";
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx(); // Wait until the whole message is gone
    right() ;
    
    }
    
    
    
  }

  

void forward()    
{
  //Serial.println("hy forward");
   digitalWrite(2, LOW); 
    digitalWrite(3,HIGH);
    digitalWrite(5,LOW); 
    digitalWrite(4,HIGH);
}       

void backward()    
{
  //Serial.println("hy backward");
   digitalWrite(2, HIGH); 
    digitalWrite(3,LOW);
    digitalWrite(5,HIGH); 
    digitalWrite(4,LOW);
}  
void stops()    
{
  //Serial.println("hy stops");
   digitalWrite(2, LOW); 
    digitalWrite(3,LOW);
    digitalWrite(5,LOW); 
    digitalWrite(4,LOW);
}

void left()    
{
  //Serial.println("hy left");
   digitalWrite(3, HIGH); 
    digitalWrite(2,LOW);
    digitalWrite(5,LOW); 
    digitalWrite(4,LOW);
}       

void right()    
{
  //Serial.println("hy right");
   digitalWrite(2, LOW); 
    digitalWrite(3,LOW);
    digitalWrite(5,HIGH); 
    digitalWrite(4,LOW);
}       
