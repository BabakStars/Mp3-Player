#include <IRremote.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini player;
SoftwareSerial myserial(10,11);
const int RECV_PIN = 7;
IRrecv irrecv (RECV_PIN);
decode_results results;
void setup() {
  Serial.begin(9600);
  myserial.begin(9600);
  player.begin(myserial);
  
  irrecv.enableIRIn();
  irrecv.blink13(true);

  pinMode(2,INPUT_PULLUP);  pinMode(3,INPUT_PULLUP);  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);  pinMode(6,INPUT_PULLUP);
player.start();
}

void loop() {
  
  if(irrecv.decode(&results))
  {
    String ff = String(results.value, HEX);
    irrecv.resume();
    if(ff == "9248D383" || ff == "9248d383")
    {
      player.volumeDown();
    }

    if(ff == "2F2BC3CF" || ff == "2f2bc3cf")
    {
      player.volumeUp();
    }

    if(ff == "600E2DEF" || ff == "600e2def")
    {
      delay(200);
      player.pause();
    }

    if(ff == "A3331023" || ff == "a3331023")
    {
      delay(200);
      player.start();
    }

    if(ff == "64CEEA63" || ff == "64cefa63")
    {
      delay(200);
      player.next();
    }

    if(ff == "A428EC03" || ff == "a428ec03")
    {
      delay(200);
      player.previous();
    }
    Serial.println(ff);
    ff = "";
    
  }
  
  if(digitalRead(2) == LOW)
  {
    delay(200);
    player.next();
  }
  if(digitalRead(3) == LOW)
  {
    delay(200);
    player.previous();
  }
  if(digitalRead(4) == LOW)
  {
    delay(200);
    
    while(1)
    {
      player.pause();
      if(digitalRead(4) == LOW){player.start(); break;}
    }
    
  }
  if(digitalRead(5) == LOW){player.volumeUp();}
  if(digitalRead(6) == LOW){player.volumeDown();}

  
  
  
  delay(100);
}
