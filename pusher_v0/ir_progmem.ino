/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <avr/pgmspace.h>
PROGMEM prog_uint16_t uSendBuff_Toggle_Cool_Auto_25[] = {233, 2050, 900, 1050, 850, 1050, 900, 1050, 900, 1050, 1850, 1950, 1850, 2050, 850, 1050, 850, 1050, 900, 1050, 900, 1050, 900, 1050, 850, 1050, 900, 1050, 900, 1050, 900, 1050, 850, 1050, 900, 1050, 850, 1050, 900, 1050, 850, 1050, 900, 1050, 900, 1050, 900, 1050, 1750, 2050, 800, 3000, 3750, 2050, 900, 1050, 1800, 1050, 850, 1100, 800, 2050, 900, 1050, 850, 1050, 900, 1050, 900, 1050, 1800, 2000, 1850, 2050, 900, 1050, 850, 1050, 900, 1050, 900, 1050, 900, 1050, 800, 1050, 900, 1050, 900, 1050, 900, 1050, 850, 1050, 900, 1050, 900, 1050, 900, 1050, 800, 1050, 900, 1050, 900, 1050, 850, 1050, 1750, 2050, 850, 3000, 3750, 2050, 900, 1050, 1850, 1050, 850, 1100, 800, 2050, 900, 1050, 800, 1050, 900, 1050, 900, 1050, 1800, 2000, 1800, 2050, 900, 1050, 800, 1050, 900, 1050, 900, 1050, 900, 1050, 850, 1050, 900, 1050, 850, 1050, 900, 1050, 850, 1050, 900, 1050, 900, 1050, 900, 1050, 850, 1050, 900, 1050, 900, 1050, 900, 1050, 1750, 2050, 850, 3950};
PROGMEM prog_uint16_t power[]={8400,4200,600,1550,600,500,550,550,550,550,550,1600,550,550,550,500,600,500,550,550,550,500,600,500,550,550,550,550,550,500,600,500,550,550,550,500,600,1600,550,1600,550,1600,600,500,550,550,550,1600,550,550,550,1600,550,550,550,500,600,1600,550};
unsigned int uSendBuff[RAWBUF];
unsigned int uSend[RAWBUF];

IRsend irsend;

void setup()
{
  Serial.begin(9600);
  Serial.println("what theufk");
}
void send(){
  Serial.println(sizeof(uint16_t));
   uint16_t rawlen;
   uint16_t s;
   Serial.println(sizeof(power));
   prog_uint16_t * pfSendBuff =  uSendBuff_Toggle_Cool_Auto_25;
   prog_uint16_t * pf=power;
   
   rawlen = pgm_read_word_near(pfSendBuff);
   
   s=pgm_read_word_near(pf);
   
   Serial.println(rawlen);
   Serial.println(s);
    //memcpy_P(uSendBuff, pfSendBuff+1, rawlen * sizeof(uint16_t));
//memcpy_P(uSend, pf+1, sizeof(power));
    //irsend.sendRaw(uSendBuff, rawlen, 38);
   Serial.println(sizeof(uSendBuff));
    //    Serial.println(sizeof(uSend));

    Serial.println("Success");
}
void loop() {
   
   
    for (int i = 0; i < 3; i++) {
      send();
      delay(4499);
       // Sony TV power code
      delay(40);
    
  }
}
