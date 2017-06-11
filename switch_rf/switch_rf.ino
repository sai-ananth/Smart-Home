/* 
 * rf12 pin configuuration
 * SDI - digital  11
 * N SEL - digital  10
 * N IRQ - digital  2
 * SCK - digital  13
 * SDO - digital  12
*/

#include <Keypad.h>
#include <JeeLib.h>

#define MAX_SIZE 1

int switchPins[MAX_SIZE] ={3};
int livePins[MAX_SIZE]={13};
int feedbackPins[MAX_SIZE] ={4};
byte state = LOW;
bool canSend =false;

int value=0;
typedef struct{byte buttonState[MAX_SIZE];byte feedback[MAX_SIZE];}              //analog valuess to be sent
DataTransferObject;                         
DataTransferObject packet;
byte needToSend;
byte received;


void setup(){
  Serial.begin(57600);
  rf12_initialize(5, RF12_433MHZ, 135);

    for(int i=0;i<MAX_SIZE;i++){
     pinMode(switchPins[i], INPUT);
     attachInterrupt(digitalPinToInterrupt(switchPins[i]), toggle, RISING);
     pinMode(feedbackPins[i],INPUT);
     pinMode(livePins[i],OUTPUT);
  }
}
  
void loop(){
  if(canSend){
    RFSend();
  } 
  RFReceive();
}



void RFSend(){
  if (rf12_canSend()) {
      rf12_sendStart(0, &packet, sizeof packet);
  }
}
void RFReceive(){
  if (rf12_recvDone() && rf12_crc == 0) {
    packet=*(DataTransferObject*)rf12_data; 
    buttonStateUpdate();   
  }
}

void toggle(){
  feedbackUpdate();
  canSend =true;
}
void buttonStateUpdate(){
  for(int i=0;i<MAX_SIZE;i++)
    digitalWrite(packet.buttonState[i], state);
}
void feedbackUpdate()
{
  for(int i=0;i<MAX_SIZE;i++)
    packet.feedback[i]=digitalRead(feedbackPins[i]);
}

