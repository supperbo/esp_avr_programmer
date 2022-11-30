#ifndef IntelHexParse_h
#define IntelHexParse_h

#include "Arduino.h"

class IntelHexParse {

	public:
		IntelHexParse();
    void ParseLine(byte* data);
    byte* GetMemoryPage();
    byte* GetLoadAddress();
    bool IsPageReady();
    
	private:
    int _address = 0;
    int _length = 0;
    int _nextAddress = 0;
    int _memIdx = 0;
    int _recordType = 0;
    byte _memoryPage[128];
    byte _loadAddress[2];
    bool _pageReady = false;
    bool _firstRun = true;
    
    int GetAddress(byte* hexline);
    int GetLength(byte* hexline);
    int GetRecordType(byte* hexline);
    void GetData(byte* hexline, int len);
    void GetLoadAddress(byte* hexline);
    void EndOfFile();
    
    
};

#endif
