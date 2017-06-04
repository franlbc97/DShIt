#include "HIDWii.h"
int LED_MAP[4] = { CWiimote::LED_1, CWiimote::LED_2, CWiimote::LED_3, CWiimote::LED_4 };
HIDWii::HIDWii(float t) :BaseHID(t)
{
	Wii = new CWii(4);
	Wii->Find(50);
	Wiimote = &Wii->Connect()[0];
	Wiimote->SetLEDs(LED_MAP[0]);
	Wiimote->SetMotionSensingMode(CWiimote::ON);
	Wiimote->Accelerometer.SetGravityCalVector(100, 100, 100);
	
}

bool HIDWii::readController()
{
	Wii->Poll(); 
	if (Wiimote->isUsingACC()) {
		Wiimote->Accelerometer.GetOrientation(Pitch_,Roll_, Yaw_);
		fThumbLX = Roll_/180, fThumbLY = Pitch_/ 180;
	}	
	return true;
}
