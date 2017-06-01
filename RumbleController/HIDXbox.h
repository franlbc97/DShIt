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
private:
	bool g_bDeadZoneOn;

};

