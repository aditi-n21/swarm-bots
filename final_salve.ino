#include <VirtualWire.h>

//const int datain = 12;
int state =0;
const int inputPin1 =2;    // Pin 15 of L293D IC
const int inputPin2 =3;
const int inputPin3 =5;
const int inputPin4 =4;
void setup() 
{
   Serial.begin(9600);
   Serial.println("setup");
    vw_set_ptt_inverted(true);
    vw_set_rx_pin(12);
    vw_setup(2000);
    vw_rx_start();
    Serial.println("start");
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
}


void loop() 
{
  vw_wait_rx();
  uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN; 
    Serial.println("start reciever");
    if (vw_get_message(buf, &buflen))
    {
      Serial.println("in loop");
      
      if(buf[0]=='1')
      {  
        forward();
    Serial.println("FORWARD");
    delay(600);
      }  
       if(buf[0]=='3')
      {  
        stops();
    Serial.println("stop");
    delay(600);
      }  
      if(buf[0]=='0')
      {
       backward() ;
       Serial.println("Backward");
       delay(600);
      }
      if(buf[0]=='4')
      {
       left() ;
       Serial.println("left");
       delay(600);
      }
      if(buf[0]=='2')
      {
       right() ;
       Serial.println("right");
       delay(600);
      }
      
      }
    
  // put your main code here, to run repeatedly:

}
void backward()    
{
  Serial.println("in forward");
   digitalWrite(2, LOW); 
    digitalWrite(3,HIGH);
    digitalWrite(5,LOW); 
    digitalWrite(4,HIGH);
}       
void forward()    
{
  Serial.println("in backward");
   digitalWrite(2, HIGH); 
    digitalWrite(3,LOW);
    digitalWrite(5,HIGH); 
    digitalWrite(4,LOW);
} 
void stops()    
{
   digitalWrite(2, LOW); 
    digitalWrite(3,LOW);
    digitalWrite(5,LOW); 
    digitalWrite(4,LOW);
}
void left()    
{
   digitalWrite(2, HIGH); 
    digitalWrite(3,LOW);
    digitalWrite(5,LOW); 
    digitalWrite(4,LOW);
}
void right()    
{
   digitalWrite(2, LOW); 
    digitalWrite(3,LOW);
    digitalWrite(4,LOW); 
    digitalWrite(5,HIGH);
}       
       
 
