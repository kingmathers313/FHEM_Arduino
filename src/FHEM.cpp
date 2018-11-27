// This allows you to communicate with a FHEM Server. 
// (c) Copyright 2018 Philipp Pfeiffer
// 

#include "Arduino.h"
#include "FHEM.h"
#include <base64.h>
#include <ESPHTTPClient.h>

FHEM::FHEM(String Server, String User, String Password)
{
	FHEM_Server = Server;
	FHEM_User = User;
	FHEM_Password = Password;
}

FHEM::FHEM(String Server)
{
	FHEM_Server = Server;
}

String FHEM::LoadFromServer(String command)
{
	if (!CSRFTokenloaded)
	{
		LoadCSRFToken();
	}

	PrepareClient(FHEM_Server, command);

	int httpCode = client.GET();

	String result = "";

	if (httpCode > 0) //Check the returning code
	{
		result = client.getString(); //Get the request response payload
	}

	client.end();   //Close connection

	return result;
}

void FHEM::PrepareClient(String URL, String command)
{
	command.replace(" ", "%20");  //remove blank spaces. Other special characters are not regarded, these must be replaced before
	URL = URL + "?XHR=1&cmd=" + command;
	if (CSRFToken != "")
	{
		URL = URL + "&fwcsrf=" + CSRFToken;
	}
	PrepareClient(URL);
}

void FHEM::PrepareClient(String URL)
{
	if (FHEM_User != "")
	{
		String auth = FHEM_User + ":" + FHEM_Password;
		auth = base64::encode(auth);
		client.setAuthorization(auth.c_str());
	}

	client.begin(URL);
}


void FHEM::LoadCSRFToken()
{
	PrepareClient(FHEM_Server);

	const char* headerNames[] = { "X-FHEM-csrfToken" };
	client.collectHeaders(headerNames, sizeof(headerNames) / sizeof(headerNames[0]));

	int httpCode = client.GET();
	if (httpCode > 0)
	{
		if (client.hasHeader("X-FHEM-csrfToken"))
		{
			CSRFToken = client.header("X-FHEM-csrfToken");
		}
	}
	client.end();

	CSRFTokenloaded = true;
}
