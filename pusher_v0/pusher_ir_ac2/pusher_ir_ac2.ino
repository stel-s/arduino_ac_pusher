#include <SPI.h>
#include <Ethernet.h>
#include <avr/pgmspace.h>
#include <PusherClient.h>
#include <IRremote.h>

IRsend irsend;
unsigned int powerOn[60]={8400,4200,550,1600,550,550,550,550,550,550,500,1600,550,600,500,550,550,550,550,550,500,550,550,550,550,550,500,600,500,550,550,550,550,550,500,550,550,1600,600,1550,600,1600,550,550,550,550,500,1600,600,550,500,1600,600,550,500,550,550,1600,550};
unsigned int powerOff[60]={8400,4200,550,1600,550,550,550,500,600,500,550,1600,600,500,550,550,550,500,600,1600,550,1600,550,550,550,500,600,500,550,550,550,550,550,500,600,500,550,550,550,500,600,500,550,550,550,1600,550,550,550,1600,550,550,550,550,550,500,550,1600,600};

void setup() 
{
  
  Serial.begin(9600);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT); 
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  if (Ethernet.begin(mac) == 0)
  {
    for(;;);
  }
  //TODO try connecting until success
  while(!Pusher.connect()){
    Serial.println("not connected");
 
  delay(2000);
   Serial.println("reconnectin");
  }
  // Pusher.subscribe("test_channel");
  // Pusher.bind("my_event",read);
   Pusher.subscribe("ac_channel");
    Pusher.bind("turnon", turnon);
    Pusher.bind("turnoff", turnoff);
  //Pusher.triggerPrivateEvent("private-ChannelName", "client-eventName", "\"\"");
 //Pusher.triggerPrivateEvent("private-ChannelName", "client-eventName", "\"1\"");

}

  void read(const String& name,const String& data){
    Serial.println(data);
  }
  void turnon(const String& name,const String& data){
     digitalWrite(8,HIGH);
     for(int i=0;i<2;i++){
      irsend.sendRaw(powerOn,60,38); 
      delay(402);
     }
  }
  void turnoff(const String& name,const String& data){
     digitalWrite(8,LOW);

     for(int i=0;i<2;i++){
          irsend.sendRaw(powerOff,60,38); 
          
     }
  }
  unsigned long lasttime;
void loop() 
  {   
    Serial.println(Pusher.connected());
  //TODO checkConnected();
  //if false reconnect();
  if(!Pusher.connected()){
      digitalWrite(9,HIGH);
      Pusher.disconnect();
      
      }else {
   // Pusher.monitor();      
    digitalWrite(9,LOW);
      }
    Pusher.monitor();   

  unsigned long time = millis();  
    if (time > lasttime + 100000)
    {
      
    
      lasttime = time;
      Serial.println(time);
      if(!Pusher.connected()){
      while(!Pusher.connect()){
    Serial.println(F("not connected"));
 
  delay(2000);
   Serial.println(F("reconnectin"));
  }
      Pusher.connect();
       Pusher.subscribe("ac_channel");
    Pusher.bind("turnon", turnon);
    Pusher.bind("turnoff", turnoff);
      
      //client.unsubscribe("my-channel"); 
    //signalActualState();
    
    }
    }
}

