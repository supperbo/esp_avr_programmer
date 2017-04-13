#ifndef WebServ_h
#define WebServ_h

#include "Arduino.h"
#include "WebServ.h"
#include <ESP8266WiFi.h>
#include "FS.h"
#include "IntelHexParse.h"
#include "Stk500.h"


class WebServ {

	public:

    const int httpCmdIndex = 0;
    const int httpCmdFlash = 1;
    const int httpCmdUpload = 2;
    const int httpCmdDelete = 3;
    const int httpCmdList = 4;
 
		WebServ(int i);
    int GetCommand(String s);
    String GetUrlParam(String s);
    String HttpSimplePage(String s);
    String HttpRawText(String s);
    void WSCmdIndex(WiFiClient* c);
    void WSCmdList(WiFiClient* c);
    void WSCmdDelete(WiFiClient* c, String s);
    void WSCmdFlash(WiFiClient* c, String s);
    void WSCmdUpload(WiFiClient* c, String s);
    
	private:
    String DefaultHeader(bool b);
    String DefaultFooter();
    void PrintPage(WiFiClient* c, String s);
    String GetDirList();

    int _resetPin = 0;
};

#endif
