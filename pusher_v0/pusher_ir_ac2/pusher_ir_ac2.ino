#include <SPI.h>
#include <Ethernet.h>
#include <avr/pgmspace.h>
#include <PusherClient.h>
#include <IRremote.h>

IRsend irsend;
    int freeRam ()
    {
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    }

void setup() 
{

      freeRam();
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
    Serial.println(F("not connected"));
 
  delay(2000);
   Serial.println(F("reconnectin"));
  }
    // Pusher.subscribe("test_channel");
    // Pusher.bind("my_event",read);
    Pusher.subscribe("ac_channel");
    Pusher.bind("turnon", turnon);
    Pusher.bind("turnoff", turnoff);
    //Pusher.triggerPrivateEvent("private-ChannelName", "client-eventName", "\"\"");
    //Pusher.triggerPrivateEvent("private-ChannelName", "client-eventName", "\"1\"");
    Serial.println(freeRam());
}
void topntail(char *str) {
    size_t len = strlen(str);
     
    memmove(str, str+1, len-2);
    str[len-2] = 0;
}
  void read(const String& name,const String& data){
    String dat=data;
    char myArray[dat.length()+1];
    strcpy(myArray, dat.c_str());
    Serial.println(freeRam());
    
    topntail(myArray);
    char *array[59];
    int i=0;
    array[i]=strtok(myArray,",");
    unsigned int power[58];
    power[i]=atoi(array[i]);
    
    while(array[i]!=NULL){
         //puts(array[i]);
        
        i++; //or array[++i]
        array[i]=strtok(NULL,",");;
       power[i-1]=atoi(array[i-1]);
       
        
    }
    
    
    Serial.print(F(","));  
    Serial.print((power[22]));
    
  }
  void turnon(const String& name,const String& data){
unsigned int powerOn[60]={8400,4200,550,1600,550,550,550,550,550,550,500,1600,550,600,500,550,550,550,550,550,500,550,550,550,550,550,500,600,500,550,550,550,550,550,500,550,550,1600,600,1550,600,1600,550,550,550,550,500,1600,600,550,500,1600,600,550,500,550,550,1600,550};
Serial.print(data);
Serial.println(freeRam());
    digitalWrite(8,HIGH);
     for(int i=0;i<2;i++){
     irsend.sendRaw(powerOn,60,38); 
      delay(402);
     }
  }
  void turnoff(const String& name,const String& data){
     digitalWrite(8,LOW);
unsigned int powerOff[60]={8400,4200,550,1600,550,550,550,500,600,500,550,1600,600,500,550,550,550,500,600,1600,550,1600,550,550,550,500,600,500,550,550,550,550,550,500,600,500,550,550,550,500,600,500,550,550,550,1600,550,550,550,1600,550,550,550,550,550,500,550,1600,600};
Serial.println(freeRam());
     for(int i=0;i<2;i++){
         irsend.sendRaw(powerOff,60,38); 
          
     }
  }
  unsigned long lasttime;
void loop() 
  {   
    
  //TODO checkConnected();
  //if false reconnect();
  if(!Pusher.connected()){
      digitalWrite(9,LOW);
      Pusher.disconnect();
      
      }else {
   // Pusher.monitor();      
    digitalWrite(9,HIGH);
      }
    Pusher.monitor();   

  unsigned long time = millis();  
    if (time > lasttime + 10000)
    {
      
    Serial.println(freeRam());

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

