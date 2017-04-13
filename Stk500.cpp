#include "Arduino.h"
#include "Stk500.h"

Stk500::Stk500(int resetPin){

  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  
  pinMode(resetPin, OUTPUT);
  //pinMode(9, OUTPUT);
  //pinMode(0, INPUT);
  //pinMode(1, OUTPUT);
  _resetPin = resetPin;
  
}


void Stk500::setupDevice() {
  resetMCU();
  getSync();
  setProgParams();
  setExtProgParams();
  enterProgMode();
 
}

void Stk500::flashPage(byte* address, byte* data) {

  byte header[] = { 0x64, 0x00, 0x80, 0x46 };
  loadAddress(address[1], address[0]);
  
  Serial.write(header, 4);
  for (int i = 0; i < 128; i++) {
    Serial.write(data[i]);
  }
  Serial.write(0x20);
  
  waitForSerialData(2, 1000);
  Serial.read();
  Serial.read();
}

void Stk500::resetMCU() {
  
  digitalWrite(_resetPin, LOW);
  delay(1);
  digitalWrite(_resetPin, HIGH);
  delay(100);
  digitalWrite(_resetPin, LOW);
  delay(1);
  digitalWrite(_resetPin, HIGH);
  delay(100);

}

int Stk500::getSync() {

  return execCmd(0x30);

}

int Stk500::enterProgMode() {

  return execCmd(0x50);

}

int Stk500::exitProgMode() {

  return execCmd(0x51);

}

int Stk500::setExtProgParams() {
  
  byte params[] = { 0x05, 0x04, 0xd7, 0xc2, 0x00 };
  return execParam(0x45, params, sizeof(params));
  
}

int Stk500::setProgParams() {
  
  byte params[] = { 0x86, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0xff, 0xff, 0xff, 0xff, 0x00, 0x80, 0x04, 0x00, 0x00, 0x00, 0x80, 0x00 };
  return execParam(0x42, params, sizeof(params));
  
}

int Stk500::loadAddress(byte adrHi, byte adrLo) {

  byte params[] = { adrHi, adrLo };
  return execParam(0x55, params, sizeof(params));

}

byte Stk500::execCmd(byte cmd) {

  byte bytes[] = { cmd, 0x20 };
  return sendBytes(bytes, 2);
}

byte Stk500::execParam(byte cmd, byte* params, int count) {

  byte bytes[32];
  bytes[0] = cmd;

  int i = 0;
  while (i < count) {
    bytes[i + 1] = params[i];
    i++;
  }

  bytes[i + 1] = 0x20;

  return sendBytes(bytes, i + 2);
}

byte Stk500::sendBytes(byte* bytes, int count) {

  Serial.write(bytes, count);
  waitForSerialData(2, 1000);

  byte sync = Serial.read();
  byte ok = Serial.read();
  if (sync == 0x14 && ok == 0x10) {
    return 1;
  }
  
  return 0;

}

int Stk500::waitForSerialData(int dataCount, int timeout) {

  int timer = 0;

  while (timer < timeout) {
    if (Serial.available() >= dataCount) {
      return 1;
    }
    delay(1);
    timer++;
  }

  return 0;
}

