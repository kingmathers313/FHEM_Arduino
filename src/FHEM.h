// FHEM.h

#ifndef FHEM_h
#define FHEM_h

#include "Arduino.h"
#include <ESPHTTPClient.h>

class FHEM
{
public:
	FHEM(String Server); //Server is required with port like this: http://192.168.1.1:8083/fhem
	FHEM(String Server, String User, String Password); //Server is required with port like this: http://192.168.1.1:8083/fhem
	String LoadFromServer(String command);
private:
	void PrepareClient(String URL);
	void PrepareClient(String URL, String command);
	void LoadCSRFToken();
	HTTPClient client;
	bool CSRFTokenloaded = false;
	String CSRFToken = "";
	String FHEM_Server = "";
	String FHEM_User = "";
	String FHEM_Password = "";
};

#endif

