#pragma once
#include <Windows.h>
#include <XInput.h>
#include "BaseHID.h"

struct CONTROLER_STATE
{
	XINPUT_STATE lastState;
	XINPUT_STATE state;
	DWORD dwResult;
	bool bLockVibration;
	XINPUT_VIBRATION vibration;
};


class HIDXbox :
	public BaseHID
{
	CONTROLER_STATE ctrl;

public:
	HIDXbox();
	HIDXbox(float t) :BaseHID(t), g_bDeadZoneOn(true){};
	~HIDXbox();
	bool readController();
	void writeController();
	void mandoAHID();
	void updateController();

	bool A_down(){ return BD(XINPUT_GAMEPAD_A); }
	bool A_up(){ return BU(XINPUT_GAMEPAD_A); }

	bool B_down(){ return BD(XINPUT_GAMEPAD_B); }
	bool B_up(){ return BU(XINPUT_GAMEPAD_B); }

	bool X_down(){ return BD(XINPUT_GAMEPAD_X); }
	bool X_up(){ return BU(XINPUT_GAMEPAD_X); }

	bool Y_down(){ return BD(XINPUT_GAMEPAD_Y); }
	bool Y_up(){ return BU(XINPUT_GAMEPAD_Y); }


	bool LeftThumb_down(){ return BD(XINPUT_GAMEPAD_LEFT_THUMB); }
	bool LeftThumb_up(){ return BU(XINPUT_GAMEPAD_LEFT_THUMB); }

	bool RightThumb_down(){ return BD(XINPUT_GAMEPAD_RIGHT_THUMB); }
	bool RightThumb_up(){ return BU(XINPUT_GAMEPAD_RIGHT_THUMB); }

	bool DPadUp_down(){ return BD(XINPUT_GAMEPAD_DPAD_UP); }
	bool DPadUp_up(){ return BU(XINPUT_GAMEPAD_DPAD_UP); }

	bool DPadDown_down(){ return BD(XINPUT_GAMEPAD_DPAD_DOWN); }
	bool DPadDown_up(){ return BU(XINPUT_GAMEPAD_DPAD_DOWN); }

	bool DPadLeft_down(){ return BD(XINPUT_GAMEPAD_DPAD_LEFT); }
	bool DPadLeft_up(){ return BU(XINPUT_GAMEPAD_DPAD_LEFT); }

	bool DPadRight_down(){ return BD(XINPUT_GAMEPAD_DPAD_RIGHT); }
	bool DPadRight_up(){ return BU(XINPUT_GAMEPAD_DPAD_RIGHT); }

	bool LeftShoulder_down(){ return BD(XINPUT_GAMEPAD_LEFT_SHOULDER); }
	bool LeftShoulder_up(){ return BU(XINPUT_GAMEPAD_LEFT_SHOULDER); }

	bool RightShoulder_down(){ return BD(XINPUT_GAMEPAD_RIGHT_SHOULDER); }
	bool RightShoulder_up(){ return BU(XINPUT_GAMEPAD_RIGHT_SHOULDER); }

	bool Back_down(){ return BD(XINPUT_GAMEPAD_BACK); }
	bool Back_up(){ return BU(XINPUT_GAMEPAD_BACK); }

	bool Start_down(){ return BD(XINPUT_GAMEPAD_START); }
	bool Start_up(){ return BU(XINPUT_GAMEPAD_START); }




private:

	bool g_bDeadZoneOn;

};

