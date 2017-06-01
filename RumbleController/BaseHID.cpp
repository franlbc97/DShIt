#include "BaseHID.h"
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )
void BaseHID::Actualiza(){
	controllerConnected = readController();
	if (controllerConnected){
		
		mandoAHID();
		//Detectamos gestos

		wButtonsDown = wButtons & ~wLastButtons;
		wButtonsUp = ~wButtons & wLastButtons;

		//aquí hariamos el filtrado de joysticks.
		fThumbLXf = (1 - aTR)*fThumbLXf + aTR*fThumbLX;
		fThumbLYf = (1 - aTR)*fThumbLYf + aTR*fThumbLY;



		fThumbRXf = (1 - aTR)*fThumbRXf + aTR*fThumbRX;
		fThumbRYf = (1 - aTR)*fThumbRYf + aTR*fThumbRY;

		
		wLastButtons = wButtons;
	}

}

