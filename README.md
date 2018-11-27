# FHEM Arduino
A library for arduino to communicate with a FHEM Server

## What is supported?
This is a simple library to communicate with a FHEM Server. It allows to send and receive data. Basic Auth (Username and Password) is supported and CSRF-Token support is also included.

## What is not supported?
Any other security (SSL/custom certificates) are not supported. I do not have this set up and as such I do not know if it works or not.
## How to use
Initialize first and provide Server, User and Password:
FHEM _fhem("http://192.168.1.1:8083/fhem", "Username", "Password"); //if you use Basic Auth
FHEM _fhem("http://192.168.1.1:8083/fhem"); //if you do not use Basic Auth

Then you can load data from the server:
String result = _fhem.LoadFromServer("{SomeSub()}"); //executes SomeSub() in 99_myUtils and saves the return value in result
_fhem.LoadFromServer("set Licht on"); //executes the fhem command "set Licht on", does not save a return value (no return value is expected)
## License
(c) Copyright 2018 Philipp Pfeiffer