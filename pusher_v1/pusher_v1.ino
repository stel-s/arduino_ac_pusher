#include <SPI.h>
#include <Ethernet.h>
#include <PusherClient.h>
#include <IRremote.h>

IRsend irsend;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

unsigned int powerOff[60]={8400,4200,550,1600,550,550,550,500,600,500,550,1600,600,500,550,550,550,500,600,1600,550,1600,550,550,550,500,600,500,550,550,550,550,550,500,600,500,550,550,550,500,600,500,550,550,550,1600,550,550,550,1600,550,550,550,550,550,500,550,1600,600};
unsigned int powerOn[60]={8400,4200,550,1600,550,550,550,550,550,550,500,1600,550,600,500,550,550,550,550,550,500,550,550,550,550,550,500,600,500,550,550,550,550,550,500,550,550,1600,600,1550,600,1600,550,550,550,550,500,1600,600,550,500,1600,600,550,500,550,550,1600,550};

PusherClient client;
 int freeRam ()
    {
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    }

void setup() {
 pinMode(8,OUTPUT); 
  pinMode(9,OUTPUT); 
  freeRam();
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Init Ethernet failed"));
    
      
  }
  
  while(!client.connect("599a9eb32ff37b5469f7")) {
      
    
    
  delay(444);
 Serial.println("reconncinc"); 
     
  }
     Serial.println("connected");
    client.subscribe("ac_channel");
    client.bind("turnon", turnOn);
    client.bind("turnoff", turnOff);
  Serial.println(freeRam());

}
unsigned long lasttime;
void loop() {
   

  unsigned long time = millis();  
    if (time > lasttime + 20000)
    {
      Serial.println(freeRam());

      //client.unsubscribe("my-channel"); 
    //signalActualState();
    lasttime = time;
    }
  
  if(client.connected()){
    client.monitor();
      digitalWrite(9,HIGH);
      }else digitalWrite(9,LOW);
//  if (client.connected()) {
//    client.monitor();
//    digitalWrite(9,LOW);
//  }
   // while(!client.connect("599a9eb32ff37b5469f7")){
     //  Serial.println("try connected");
// if(client.connect("599a9eb32ff37b5469f7")){
//   
//   //Serial.println("reconnectin");
//  client.bind("turnon", turnOn);
//    client.bind("turnoff", turnOff);
//
//    client.subscribe("ac_channel");
//    
//    //client.bind("turnon", turnOn);
//    //client.bind("turnoff", turnOff);
//
//    //client.subscribe("ac_channel");
//     digitalWrite(8,LOW);
// }
  //}
}


void turnOn(String data){

  Serial.println(data);
Serial.println(freeRam());

  digitalWrite(8,HIGH);
     for(int i=0;i<2;i++){
      irsend.sendRaw(powerOn,60,38); 
      delay(402);
     }
  }
void turnOff(String data){
  
     digitalWrite(8,LOW);
Serial.println(freeRam());

     for(int i=0;i<2;i++){
          irsend.sendRaw(powerOff,60,38); 
          
     }
  }

