#include <SPI.h>
#include <Ethernet.h>
#include <PusherClient.h>
#include <IRremote.h>

IRsend irsend;
unsigned int powerOn[60]={8400,4200,550,1600,550,550,550,550,550,550,500,1600,550,600,500,550,550,550,550,550,500,550,550,550,550,550,500,600,500,550,550,550,550,550,500,550,550,1600,600,1550,600,1600,550,550,550,550,500,1600,600,550,500,1600,600,550,500,550,550,1600,550};
unsigned int powerOff[60]={8400,4200,550,1600,550,550,550,500,600,500,550,1600,600,500,550,550,550,500,600,1600,550,1600,550,550,550,500,600,500,550,550,550,550,550,500,600,500,550,550,550,500,600,500,550,550,550,1600,550,550,550,1600,550,550,550,550,550,500,550,1600,600};
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

PusherClient client;
 

void setup() {
 pinMode(8,OUTPUT); 
  pinMode(9,OUTPUT); 
  
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Init Ethernet failed");
    for(;;)
      ;
  }
  
  if(client.connect("599a9eb32ff37b5469f7")) {
     client.subscribe("ac_channel");
    client.bind("turnon", turnOn);
    client.bind("turnoff", turnOff);
   
   
  }
  else {
    while(1) {}
  }
}

void loop() {
   int lasttime;

  unsigned long time = millis();  
    if (time > lasttime + 20000)
    {
      
      //client.unsubscribe("my-channel"); 
    //signalActualState();
    lasttime = time;
    }
  
  if(!client.connected()){
      digitalWrite(9,HIGH);
      }
  if (client.connected()) {
    client.monitor();
    digitalWrite(9,LOW);
  }
  else {
   delay(200);
    Serial.println("disconnected");
          digitalWrite(9,HIGH);

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
}

void turnOn(String data){
     digitalWrite(8,HIGH);
     for(int i=0;i<2;i++){
      irsend.sendRaw(powerOn,60,38); 
      delay(402);
     }
  }
void turnOff(String data){
     digitalWrite(8,LOW);

     for(int i=0;i<2;i++){
          irsend.sendRaw(powerOff,60,38); 
          
     }
  }

