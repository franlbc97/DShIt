#ifndef HIDWII_H
#define HIDWII_H
#include "WiiUse\wiiusecpp.h"
#include "BaseHID.h"


class HIDWii : public BaseHID
{
public:
	HIDWii(float t) ;
	~HIDWii() {};
	virtual void mandoAHID() {};
	virtual bool readController();
	virtual void writeController() { };

	float getPitch()const { return Pitch_; }

	float getRoll()const { return Roll_; }

	float getYaw()const { return Yaw_; }

	virtual bool A_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_A); }
	virtual bool A_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_A); }

	virtual bool B_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_B); }
	virtual bool B_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_B); }

	virtual bool ONE_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_ONE); }
	virtual bool ONE_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_ONE); }

	virtual bool TWO_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_TWO); }
	virtual bool TWO_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_TWO); }

	virtual bool DOWN_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_DOWN); }
	virtual bool DOWN_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_DOWN); }

	virtual bool UP_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_UP); }
	virtual bool UP_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_UP); }

	virtual bool LEFT_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_LEFT); }
	virtual bool LEFT_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_LEFT); }

	virtual bool RIGHT_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_RIGHT); }
	virtual bool RIGHT_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_RIGHT); }

	virtual bool MINUS_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_MINUS); }
	virtual bool MINUS_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_MINUS); }

	virtual bool PLUS_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_PLUS); }
	virtual bool PLUS_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_PLUS); }

	virtual bool HOME_down() { return Wiimote->Buttons.isPressed(CButtons::BUTTON_HOME); }
	virtual bool HOME_up() { return Wiimote->Buttons.isReleased(CButtons::BUTTON_HOME); }
	
	

private:
	CWii* Wii;
	CWiimote* Wiimote;
	float Pitch_, Roll_, Yaw_;

};
#endif // !HIDWII_H
