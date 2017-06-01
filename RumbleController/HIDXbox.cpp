#pragma once
#include "HIDXbox.h"
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // Default to 24% of the 

HIDXbox::HIDXbox() :BaseHID(10)
{
	g_bDeadZoneOn = true;
}

bool HIDXbox::readController(){
	XInputGetState(0, &ctrl.state);
	return (ctrl.dwResult == ERROR_SUCCESS) ? true : false;
}

void HIDXbox::mandoAHID()
{

	if (controllerConnected){
		//Comprobamos la zona muelta del mando.

		if (g_bDeadZoneOn){
			if ((ctrl.state.Gamepad.sThumbLX < INPUT_DEADZONE &&
				ctrl.state.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
				(ctrl.state.Gamepad.sThumbLY < INPUT_DEADZONE &&
				ctrl.state.Gamepad.sThumbLY > -INPUT_DEADZONE))
			{
				ctrl.state.Gamepad.sThumbLX = 0;
				ctrl.state.Gamepad.sThumbLY = 0;
			}
			if ((ctrl.state.Gamepad.sThumbRX < INPUT_DEADZONE &&
				ctrl.state.Gamepad.sThumbRX > -INPUT_DEADZONE) &&
				(ctrl.state.Gamepad.sThumbRY < INPUT_DEADZONE &&
				ctrl.state.Gamepad.sThumbRY > -INPUT_DEADZONE))
			{
				ctrl.state.Gamepad.sThumbRX = 0;
				ctrl.state.Gamepad.sThumbRY = 0;
			}
		}
		//pasamos los joysticks a formato [-1.0, 1.0]

		fThumbLX = (float)ctrl.state.Gamepad.sThumbLX / MAXSHORT;
		fThumbLY = (float)ctrl.state.Gamepad.sThumbLY / MAXSHORT;
		fThumbRX = (float)ctrl.state.Gamepad.sThumbRX / MAXSHORT;
		fThumbRY = (float)ctrl.state.Gamepad.sThumbRY / MAXSHORT;

		rTrigger = (float)ctrl.state.Gamepad.bRightTrigger / MAXBYTE;
		lTrigger = (float)ctrl.state.Gamepad.bLeftTrigger / MAXBYTE;


		wButtons = ctrl.state.Gamepad.wButtons;

	}

}
void HIDXbox::writeController(){
	ctrl.vibration.wRightMotorSpeed = (WORD)(rMotor *  MAXUINT16);
	ctrl.vibration.wLeftMotorSpeed = (WORD)(lMotor * MAXUINT16);
	XInputSetState(0, &ctrl.vibration);
}


HIDXbox::~HIDXbox()
{
}
