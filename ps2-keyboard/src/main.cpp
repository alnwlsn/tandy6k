#include <Arduino.h>
#include <PS2KeyAdvanced.h>

// pins to keyboard
#define kbDataPin 4
#define kbIRQPin 3  // needs to be interrupt pin

//pins to computer
#define tandykbDataPin 7
#define tandykbClkPin 8
#define tandykbBusyPin 9

uint16_t c;

PS2KeyAdvanced keyboard;

void setup() {
  keyboard.begin(kbDataPin, kbIRQPin);
  Serial.begin(9600);
  pinMode(tandykbBusyPin, INPUT_PULLUP);
  pinMode(tandykbClkPin, OUTPUT);
  pinMode(tandykbDataPin, OUTPUT);
  keyboard.setLock(PS2_LOCK_NUM | PS2_LOCK_CAPS);
}

int keymap(uint16_t c) {
  int ret = -1;
  //takes in raw key scan from the library, and returns
  //or -1 if no key is pressed 
  if (c & 0x8000) return -1;  // do not return any key_up events
  //modifiers
  bool shift = (c & 0x4000);
  bool control = (c & 0x2000);
  bool caps = (c & 0x1000);
  bool alt = (c & 0x400);
  //keys that ignore modifiers
  uint16_t n=c&0x1ff;
  // Serial.print('<');
  // Serial.print(n, HEX);
  // Serial.print('>');
  if(shift && ret == -1){ //shift key modifier
    switch(n){
      case 0x31:ret=0x21;break; //!
      case 0x32:ret=0x40;break; //@
      case 0x33:ret=0x23;break; //#
      case 0x34:ret=0x24;break; //$
      case 0x35:ret=0x25;break; //%
      case 0x36:ret=0x5e;break; //^
      case 0x37:ret=0x26;break; //&
      case 0x38:ret=0x2a;break; //*
      case 0x39:ret=0x28;break; //(
      case 0x30:ret=0x29;break; //)
      case 0x3c:ret=0x5f;break; //_
      case 0x5f:ret=0x2b;break; //+
      case 0x51:ret=0x51;break; //Q
      case 0x57:ret=0x57;break; //W
      case 0x45:ret=0x45;break; //E
      case 0x52:ret=0x52;break; //R
      case 0x54:ret=0x54;break; //T
      case 0x59:ret=0x59;break; //Y
      case 0x55:ret=0x55;break; //U
      case 0x49:ret=0x49;break; //I
      case 0x4f:ret=0x4f;break; //O
      case 0x50:ret=0x50;break; //P
      case 0x5d:ret=0x7b;break; //{
      case 0x5e:ret=0x7d;break; //}
      case 0x41:ret=0x41;break; //A
      case 0x53:ret=0x53;break; //S
      case 0x44:ret=0x44;break; //D
      case 0x46:ret=0x46;break; //F
      case 0x47:ret=0x47;break; //G
      case 0x48:ret=0x48;break; //H
      case 0x4a:ret=0x4a;break; //J
      case 0x4b:ret=0x4b;break; //K
      case 0x4c:ret=0x4c;break; //L
      case 0x5b:ret=0x3a;break; //:
      case 0x3a:ret=0x22;break; //"
      case 0x5a:ret=0x5a;break; //Z
      case 0x58:ret=0x58;break; //X
      case 0x43:ret=0x43;break; //C
      case 0x56:ret=0x56;break; //V
      case 0x42:ret=0x42;break; //B
      case 0x4e:ret=0x4e;break; //N
      case 0x4d:ret=0x4d;break; //M
      case 0x3b:ret=0x3c;break; //<
      case 0x3d:ret=0x3e;break; //>
      case 0x3e:ret=0x3f;break; //?
      case 0x40:ret=0x7e;break; //~
      case 0x5c:ret=0x7c;break; //|
    }
  }
  if(control && ret == -1){ //control key modifier
    switch(n){
      case 0x32:ret=0x00;break; //2
      case 0x34:ret=0xa4;break; //4
      case 0x36:ret=0x7e;break; //6
      case 0x39:ret=0x5c;break; //9
      case 0x30:ret=0x7c;break; //0
      case 0x3c:ret=0x7f;break; //-
      case 0x5f:ret=0x2b;break; //=
      case 0x51:ret=0x11;break; //q
      case 0x57:ret=0x17;break; //w
      case 0x45:ret=0x05;break; //e
      case 0x52:ret=0x12;break; //r
      case 0x54:ret=0x14;break; //t
      case 0x59:ret=0x19;break; //y
      case 0x55:ret=0x15;break; //u
      case 0x49:ret=0x09;break; //i
      case 0x4f:ret=0x0f;break; //o
      case 0x50:ret=0x10;break; //p
      case 0x41:ret=0x01;break; //a
      case 0x53:ret=0x13;break; //s
      case 0x44:ret=0x04;break; //d
      case 0x46:ret=0x06;break; //f
      case 0x47:ret=0x07;break; //g
      case 0x48:ret=0x08;break; //h
      case 0x4a:ret=0x0a;break; //j
      case 0x4b:ret=0x0b;break; //k
      case 0x4c:ret=0x0c;break; //l
      case 0x5a:ret=0x1a;break; //z
      case 0x58:ret=0x18;break; //x
      case 0x43:ret=0x03;break; //c
      case 0x56:ret=0x16;break; //v
      case 0x42:ret=0x02;break; //b
      case 0x4e:ret=0x0e;break; //n
      case 0x4d:ret=0x0d;break; //m
    }
  }
  if(caps && ret == -1){ //caps lock on
    switch(n){
      case 0x51:ret=0x51;break; //q
      case 0x57:ret=0x57;break; //w
      case 0x45:ret=0x45;break; //e
      case 0x52:ret=0x52;break; //r
      case 0x54:ret=0x54;break; //t
      case 0x59:ret=0x59;break; //y
      case 0x55:ret=0x55;break; //u
      case 0x49:ret=0x49;break; //i
      case 0x4f:ret=0x4f;break; //o
      case 0x50:ret=0x50;break; //p
      case 0x41:ret=0x41;break; //a
      case 0x53:ret=0x53;break; //s
      case 0x44:ret=0x44;break; //d
      case 0x46:ret=0x46;break; //f
      case 0x47:ret=0x47;break; //g
      case 0x48:ret=0x48;break; //h
      case 0x4a:ret=0x4a;break; //j
      case 0x4b:ret=0x4b;break; //k
      case 0x4c:ret=0x4c;break; //l
      case 0x5a:ret=0x5a;break; //z
      case 0x58:ret=0x58;break; //x
      case 0x43:ret=0x43;break; //c
      case 0x56:ret=0x56;break; //v
      case 0x42:ret=0x42;break; //b
      case 0x4e:ret=0x4e;break; //n
      case 0x4d:ret=0x4d;break; //m
    }
  }
  if(ret == -1){ //more unmodified keys
    switch(n){  
      case 0x31:ret=0x31;break; //1
      case 0x32:ret=0x32;break; //2
      case 0x33:ret=0x33;break; //3
      case 0x34:ret=0x34;break; //4
      case 0x35:ret=0x35;break; //5
      case 0x36:ret=0x36;break; //6
      case 0x37:ret=0x37;break; //7
      case 0x38:ret=0x38;break; //8
      case 0x39:ret=0x39;break; //9
      case 0x30:ret=0x30;break; //0
      case 0x3c:ret=0x2d;break; //-
      case 0x5f:ret=0x3d;break; //=
      case 0x51:ret=0x71;break; //q
      case 0x57:ret=0x77;break; //w
      case 0x45:ret=0x65;break; //e
      case 0x52:ret=0x72;break; //r
      case 0x54:ret=0x74;break; //t
      case 0x59:ret=0x79;break; //y
      case 0x55:ret=0x75;break; //u
      case 0x49:ret=0x69;break; //i
      case 0x4f:ret=0x6f;break; //o
      case 0x50:ret=0x70;break; //p
      case 0x5d:ret=0x5b;break; //[
      case 0x5e:ret=0x5d;break; //]
      case 0x41:ret=0x61;break; //a
      case 0x53:ret=0x73;break; //s
      case 0x44:ret=0x64;break; //d
      case 0x46:ret=0x66;break; //f
      case 0x47:ret=0x67;break; //g
      case 0x48:ret=0x68;break; //h
      case 0x4a:ret=0x6a;break; //j
      case 0x4b:ret=0x6b;break; //k
      case 0x4c:ret=0x6c;break; //l
      case 0x5b:ret=0x3b;break; //;
      case 0x3a:ret=0x27;break; //'
      case 0x5a:ret=0x7a;break; //z
      case 0x58:ret=0x78;break; //x
      case 0x43:ret=0x63;break; //c
      case 0x56:ret=0x76;break; //v
      case 0x42:ret=0x62;break; //b
      case 0x4e:ret=0x6e;break; //n
      case 0x4d:ret=0x6d;break; //m
      case 0x3b:ret=0x2c;break; //,
      case 0x3d:ret=0x2e;break; //.
      case 0x3e:ret=0x2f;break; ///
      case 0x40:ret=0x60;break; //'
      case 0x5c:ret=0x5c;break; //backslash
      case 0x11a:ret=0x7f;break; //del
      case 0x2f:ret=0x2f;break; //numberpad /
      case 0x2e:ret=0x2a;break; //numberpad *
      case 0x2d:ret=0x2d;break; //numberpad -
      case 0x2c:ret=0x2b;break; //numberpad +
      case 0x11f:ret=0x20;break; //space
      case 0x11d:ret=0x09;break; //tab
      case 0x11b:ret=0x1b;break; //escape
      case 0x11c:ret=0x08;break; //backspace
      case 0x06: ret=0x03;break; //break (mapped as pause/break)
      case 0x104:ret=0x00;break; //hold (mapped as printScreen)
      case 0x11e:ret=0x0d;break; //enter
      case 0x115:ret=0x1c;break; //left
      case 0x116:ret=0x1d;break; //right
      case 0x117:ret=0x1e;break; //up
      case 0x118:ret=0x1f;break; //down
      case 0x161:ret=0x01;break; //f1 (model ii mapping, don't know what 6000 uses yet)
      case 0x162:ret=0x02;break; //f2
      case 0x163:ret=0x03;break; //f3
      case 0x164:ret=0x04;break; //f4
      case 0x165:ret=0x05;break; //f5
      case 0x166:ret=0x06;break; //f6
      case 0x167:ret=0x07;break; //f7
      case 0x168:ret=0x08;break; //f8
      case 0x169:ret=0x09;break; //f9
      case 0x16a:ret=0x0a;break; //f10
      case 0x16b:ret=0x0b;break; //f11
      case 0x16c:ret=0x0c;break; //f12
      //number pad (number lock on)
      case 0x20:ret=0x30;break; //0
      case 0x2a:ret=0x2e;break; //.
      case 0x21:ret=0x31;break; //1
      case 0x22:ret=0x32;break; //2
      case 0x23:ret=0x33;break; //3
      case 0x24:ret=0x34;break; //4
      case 0x25:ret=0x35;break; //5
      case 0x26:ret=0x36;break; //6
      case 0x27:ret=0x37;break; //7
      case 0x28:ret=0x38;break; //8
      case 0x29:ret=0x39;break; //9
      case 0x2b:ret=0x0d;break; //enter
    }
  }
  if(alt && ret != -1) ret += 128;
  return ret;
}

void tandySend(uint8_t b){
  digitalWrite(tandykbClkPin, LOW);
  digitalWrite(tandykbDataPin, HIGH);
  //wait for Busy to go high
  for(;;){
    if(digitalRead(tandykbBusyPin)==1) break;
    delayMicroseconds(10);
  }
  //now, send it
  //the order is important
  for(int i=0;i<=7;i++){
    bool d = (b>>i)&1;
    digitalWrite(tandykbDataPin, d);
    delayMicroseconds(20);
    digitalWrite(tandykbClkPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(tandykbDataPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(tandykbClkPin, LOW);
    delayMicroseconds(20);
  }
  // delayMicroseconds(20);
  digitalWrite(tandykbDataPin, LOW);
  delayMicroseconds(10);
  digitalWrite(tandykbDataPin, HIGH);
  delayMicroseconds(100);
}

void loop() {
  if (keyboard.available()) {
    c = keyboard.read();           // read the next key
    if (c > 0 && !(c & 0x8000)) {  // some key was pressed
      int g = keymap(c);
      if(g!=-1){
        tandySend(g);
        Serial.write(g);
        // Serial.println(g, HEX);
      }
    }
  }
  if (Serial.available()){ //also send raw serial data
    uint8_t g = Serial.read();
    if(g==127)g=8; //backspace to 0x08
    tandySend(g);
    Serial.write(g);
  }
}