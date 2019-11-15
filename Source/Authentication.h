/*
  ==============================================================================

    Authentication.h
    Created: 28 Nov 2018 6:37:09pm
    Author:  Guillermo Reyes

  ==============================================================================
*/

#pragma once
/*
 
 Define a routine to connect to server, and authenticate a key
 
 1) Upon purchase, user will recieve an emal with a serial key,
 
 2) this segment of code will cast an alert window to prompt user to regsiter the plugin,
 
 Client Side
 send a request to authenticate, if successful - dsable the alert window. (check this condition at startup everytime)
 if(verified)
  process as normal
 
 else
    attempt to verify
 
 (The verifcation can be a document generated and read at the begiining of startup)
 Server Side,
 
 If key is valid and not used, then authenticate, otherwise prompt user that key is nvalid. 

 
 
 */
