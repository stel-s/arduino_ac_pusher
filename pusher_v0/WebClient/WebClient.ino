/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
IPAddress server(192,168,2,155);   // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192,168,2,177);

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 5000)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /api/getturnon HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}
int i=0;
char s[10];
unsigned int powerOn[60];
boolean begin=false;
int counter=0;

void process_data(const char * data){
  //Serial.println("inside");
 
 int val = atoi(data);
 powerOn[counter]=val;
 counter++;


}

void loop()
{
  
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
     if(c=='[' ||begin){
       if (begin){
         s[i]=c;
         i++;
          if(c==','){
            process_data(&s[0]);
            i=0;
          }
       }
       if(c==']') {
        process_data(&s[0]); 
      begin=false;  
      }
    
    begin=true;
   }
  Serial.print(c);
 }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  for(int i=0;i<59;i++)
  Serial.println(powerOn[i]);
    // do nothing forevermore:
    while(true);
  }
}

