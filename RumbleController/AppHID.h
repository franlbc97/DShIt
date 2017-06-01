
#include <Windows.h>
#include "HIDXbox.h"
#include <commdlg.h>
#include <basetsd.h>


#define T 10   //ms para actualizar
#define TARGET_XBOX360
#ifdef TARGET_XBOX360
HIDXbox controller(T);
#elif defined(TARGET_PS3)
HIDPs controller(T);
#elif defined(TARGET_WII)
HIDWii controller(T);
#endif
#define XINPUT_GAMEPAD_DPAD_UP 0x0001 // bit 0
#define XINPUT_GAMEPAD_DPAD_DOWN 0x0002 // bit 1
#define XINPUT_GAMEPAD_DPAD_LEFT 0x0004 // bit 2
#define XINPUT_GAMEPAD_DPAD_RIGHT 0x0008 // bit 3
#define XINPUT_GAMEPAD_START 0x0010 // bit 4
#define XINPUT_GAMEPAD_BACK 0x0020 // bit 5
#define XINPUT_GAMEPAD_LEFT_THUMB 0x0040 // bit 6
#define XINPUT_GAMEPAD_RIGHT_THUMB 0x0080 // bit 7
#define XINPUT_GAMEPAD_LEFT_SHOULDER 0x0100 // bit 8
#define XINPUT_GAMEPAD_RIGHT_SHOULDER 0x0200 // bit 9
#define XINPUT_GAMEPAD_A 0x1000 // bit 12
#define XINPUT_GAMEPAD_B 0x2000 // bit 13
#define XINPUT_GAMEPAD_X 0x4000 // bit 14
#define XINPUT_GAMEPAD_Y 0x8000 // bit 15

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define MAX_CONTROLLERS     4
#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )

class AppHID :
	public HIDXbox
{
public:
	AppHID(){};
	~AppHID(){};
	
};

	

	



	