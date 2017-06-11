#define MAX_SIZE 1

int switchPin =2;
int switchLive=13;
int switchFB =4;
byte state = LOW;
bool canSend =false;
void setup() {
  Serial.begin(9600);
  for(int i=0;i<MAX_SIZE;i++){
     pinMode(switchPin, INPUT);
     attachInterrupt(digitalPinToInterrupt(switchPin), toggle, RISING);
     pinMode(switchFB,INPUT);
     pinMode(switchLive,OUTPUT);
  }
}

void loop() {
  if(canSend){
    Serial.print("send ");
    Serial.println(digitalRead(switchFB));
    canSend=false;
  }

}
void toggle()
{
  state = !state;
  digitalWrite(switchLive, state);
  digitalWrite(switchFB, state);
  canSend =true;
}
