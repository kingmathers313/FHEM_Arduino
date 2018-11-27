// FHEM.h

#ifndef FHEM_h
#define FHEM_h

#include "Arduino.h"
#include <ESPHTTPClient.h>

class FHEM
{
public:
	FHEM(String Server);
	FHEM(String Server, String User, String Password);
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

