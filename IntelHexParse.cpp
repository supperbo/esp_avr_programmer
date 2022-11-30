
#include "Arduino.h"
#include "IntelHexParse.h"

IntelHexParse::IntelHexParse() {
  _loadAddress[0] = 0x00;
  _loadAddress[1] = 0x00;
}

void IntelHexParse::ParseLine(byte* hexline) {
  _recordType = GetRecordType(hexline);

  if(_recordType == 0) {
    _address = GetAddress(hexline);
    _length = GetLength(hexline);
    

    GetData(hexline, _length);

    if(_memIdx == 128) {

      if(!_firstRun){
        _loadAddress[1] += 0x40;
        if(_loadAddress[1] == 0){
          _loadAddress[0] += 0x1;
        }
      }
      _firstRun = false;
      _pageReady = true;
      _memIdx = 0;
    }
    
    _nextAddress = _address + _length;
    
  }

  if(_recordType == 1){
    EndOfFile();
    _pageReady=true;
  }

}

bool IntelHexParse::IsPageReady() {
  return _pageReady;
}


byte* IntelHexParse::GetMemoryPage() {
   _pageReady = false;
  return _memoryPage;
}

byte* IntelHexParse::GetLoadAddress() {
  return _loadAddress;
}

void IntelHexParse::GetLoadAddress(byte* hexline) {

  char buff[3];
  buff[2] = '\0';

  buff[0] = hexline[3];
  buff[1] = hexline[4];
  _loadAddress[0] = strtol(buff, 0, 16); 
  buff[0] = hexline[5];
  buff[1] = hexline[6];
  _loadAddress[1] = strtol(buff, 0, 16); 
  
}

void IntelHexParse::GetData(byte* hexline, int len) {

  int start = 9;
  int end = (len * 2) + start;
  char buff[3];
  buff[2] = '\0';
  
  for(int x = start; x < end; x = x+2) {
    buff[0] = hexline[x];
    buff[1] = hexline[x+1];
    _memoryPage[_memIdx] = strtol(buff, 0, 16);
    _memIdx++;
  }
  
}

void IntelHexParse::EndOfFile() {

  _loadAddress[1] += 0x40;
  if(_loadAddress[1] == 0){
    _loadAddress[0] += 0x1;
  }

  while(_memIdx < 128) {
    _memoryPage[_memIdx] = 0xFF;
    _memIdx++;
  }

}

int IntelHexParse::GetAddress(byte* hexline) {

  char buff[5];
  buff[0] = hexline[3];
  buff[1] = hexline[4];
  buff[2] = hexline[5];
  buff[3] = hexline[6];
  buff[4] = '\0';
  
  return strtol(buff, 0, 16); 
}

int IntelHexParse::GetLength(byte* hexline) {

  char buff[3];
  buff[0] = hexline[1];
  buff[1] = hexline[2];
  buff[2] = '\0';
  
  return strtol(buff, 0, 16); 
}

int IntelHexParse::GetRecordType(byte* hexline) {
  
  char buff[3];
  buff[0] = hexline[7];
  buff[1] = hexline[8];
  buff[2] = '\0';
  
  return strtol(buff, 0, 16); 
}


