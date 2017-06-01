#define STRICT
#include <windows.h>
#include <commdlg.h>
#include <XInput.h>
#include <basetsd.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include "resource.h"

#include "HIDXbox.h"
//USAMOS MANDO DE EQUISBOS, ASI QUE DEFINIMOS SUS TECLAS
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

//Definicion de calbacs
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
VOID CALLBACK updateControllerState();

//Manejador de ventana
HWND g_hWnd;
HIDXbox controller;
WCHAR g_szMessage[4][1024] = { 0 };
void GeneraEventos(HIDXbox * Control);



int APIENTRY wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int)
{

	//Me daba problemas al convertir a (TIMERPROC), asi que el callback es llamado en case WM_TIMER
	UINT_PTR timerControl = SetTimer(g_hWnd, 1, T, (TIMERPROC)updateControllerState);

	g_szMessage[4][1024] = { 0 };
	// Getting the active window
	g_hWnd = GetActiveWindow();

	// Init state
	//ZeroMemory(controllers, sizeof(HIDXbox) * MAX_CONTROLLERS);

	// Enter the message loop
	MSG msg;
	msg.message = WM_NULL;

	while (GetMessage(&msg, NULL, 0U, 0U))
	{

		// Translate and dispatch the message
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Clean up 
	UnregisterClass(L"XInputSample", NULL);
	KillTimer(g_hWnd, timerControl);

	return 0;
}

//Gestion de mensajes

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATEAPP:
	{
		if (wParam == TRUE)
		{
			// App is now active, so re-enable XInput
			XInputEnable(true);
		}
		else
		{
			// App is now inactive, so disable XInput to prevent
			// user input from effecting application and to 
			// disable rumble. 
			XInputEnable(false);
		}
		break;
	}

	case WM_PAINT:
	{
		// Paint some simple explanation text
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		SetBkColor(hDC, 0xFF0000);
		SetTextColor(hDC, 0xFFFFFF);
		RECT rect;
		GetClientRect(hWnd, &rect);

		rect.top = 20;
		rect.left = 20;
		DrawText(hDC,
			L"Use the controller's left/right trigger to adjust the speed of the left/right rumble motor.\n",
			-1, &rect, 0);
		
		//Cambiar este bucle para solo un controlador
		for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
		{
			rect.top = i * 80 + 90;
			rect.left = 20;
			DrawText(hDC, g_szMessage[i], -1, &rect, 0);
		}

		EndPaint(hWnd, &ps);
		return 0;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		KillTimer(g_hWnd, 1);
		break;
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

VOID CALLBACK updateControllerState(){
		controller.Actualiza();
		if (controller.LT()>0.1)controller.leftMotor(controller.LT());
		else controller.leftMotor(0);
		if (controller.RT()>0.1)controller.rightMotor(controller.RT());
		else controller.rightMotor(0);

		if (controller.BD(XINPUT_GAMEPAD_BACK)){
			PostQuitMessage(0);
		}

		//Movimientos de joystis aqui
		controller.writeController();
		GeneraEventos(&controller);

}
void GeneraEventos(HIDXbox * Control) {


	//Movimientos de joystis aqui
	POINT ptMouse;
	GetCursorPos(&ptMouse);


	RECT rectaux;
	HWND aux = GetDesktopWindow();
	GetWindowRect(aux, &rectaux);


	if (Control->LJX() != 0) {
		ptMouse.x += Control->LJX() * 10;
	}

	if (Control->LJY() != 0) {
		ptMouse.y -= Control->LJY() * 10;
	}


	if (Control->BD(XINPUT_GAMEPAD_LEFT_THUMB))	mouse_event(MOUSEEVENTF_LEFTDOWN, ptMouse.x, ptMouse.y, 0, NULL);
	if (Control->BU(XINPUT_GAMEPAD_LEFT_THUMB))	mouse_event(MOUSEEVENTF_LEFTUP, ptMouse.x, ptMouse.y, 0, NULL);

	if (Control->BD((XINPUT_GAMEPAD_RIGHT_THUMB)))	mouse_event(MOUSEEVENTF_RIGHTDOWN, ptMouse.x, ptMouse.y, 0, NULL);
	if (Control->BU((XINPUT_GAMEPAD_RIGHT_THUMB)))	mouse_event(MOUSEEVENTF_RIGHTUP, ptMouse.x, ptMouse.y, 0, NULL);

	//Start y back
	if (Control->BD(XINPUT_GAMEPAD_BACK))keybd_event(VK_ESCAPE, 0x18, NULL, NULL);
	if (Control->BU(XINPUT_GAMEPAD_BACK))keybd_event(VK_ESCAPE, 0x18, KEYEVENTF_KEYUP, NULL);

	if (Control->BD(XINPUT_GAMEPAD_START))keybd_event(VK_RETURN, 0x18, NULL, NULL);
	if (Control->BU(XINPUT_GAMEPAD_START))keybd_event(VK_RETURN, 0x18, KEYEVENTF_KEYUP, NULL);



	//Botones X y B para inicio y fin
	if (Control->BD(XINPUT_GAMEPAD_X)) {
		keybd_event(VK_HOME, 0x18, NULL, NULL);
	}
	if (Control->BU(XINPUT_GAMEPAD_X)) {
		keybd_event(VK_HOME, 0x18, KEYEVENTF_KEYUP, NULL);
	}
	if (Control->BD(XINPUT_GAMEPAD_B)) {
		keybd_event(VK_END, 0x18, NULL, NULL);
	}
	if (Control->BU(XINPUT_GAMEPAD_B)) {
		keybd_event(VK_END, 0x18, KEYEVENTF_KEYUP, NULL);
	}

	//Botones Y y A para Av pag Re pag
	if (Control->BD(XINPUT_GAMEPAD_Y)) {
		keybd_event(VK_PRIOR, 0x18, NULL, NULL);
	}
	if (Control->BU(XINPUT_GAMEPAD_Y)) {
		keybd_event(VK_PRIOR, 0x18, KEYEVENTF_KEYUP, NULL);
	}

	if (Control->BD(XINPUT_GAMEPAD_A)) {
		keybd_event(VK_NEXT, 0x18, NULL, NULL);
	}
	if (Control->BU(XINPUT_GAMEPAD_A)) {
		keybd_event(VK_NEXT, 0x18, KEYEVENTF_KEYUP, NULL);
	}




	//USO DEL PAD
	if (Control->BD(XINPUT_GAMEPAD_DPAD_LEFT)) {
		keybd_event(VK_LEFT, 0x18, NULL, NULL);
	}
	if (Control->BU(XINPUT_GAMEPAD_DPAD_LEFT)) {
		keybd_event(VK_LEFT, 0x18, KEYEVENTF_KEYUP, NULL);
	}
	if (Control->BD(XINPUT_GAMEPAD_DPAD_RIGHT)) {
		keybd_event(VK_RIGHT, 0x18, NULL, NULL);
	}
	if (Control->BU(XINPUT_GAMEPAD_DPAD_RIGHT)) {
		keybd_event(VK_RIGHT, 0x18, KEYEVENTF_KEYUP, NULL);
	}
	if (Control->BD(XINPUT_GAMEPAD_DPAD_UP)) {
		keybd_event(VK_UP, 0x18, NULL, NULL);
	}
	if (Control->BU(XINPUT_GAMEPAD_DPAD_UP)) {
		keybd_event(VK_UP, 0x18, KEYEVENTF_KEYUP, NULL);
	}
	if (Control->BD(XINPUT_GAMEPAD_DPAD_DOWN)) {
		keybd_event(VK_DOWN, 0x18, NULL, NULL);
	}
	if (Control->BU(XINPUT_GAMEPAD_DPAD_DOWN)) {
		keybd_event(VK_DOWN, 0x18, KEYEVENTF_KEYUP, NULL);
	}



	//Rueda del ratón:
	if (Control->BD(XINPUT_GAMEPAD_LEFT_SHOULDER))  mouse_event(MOUSEEVENTF_WHEEL, ptMouse.x, ptMouse.y, 10, NULL);
	if (Control->BD(XINPUT_GAMEPAD_RIGHT_SHOULDER))  mouse_event(MOUSEEVENTF_WHEEL, ptMouse.x, ptMouse.y, -10, NULL);

	if (Control->BD(0xFFFFF)) {
		Control->leftMotor(0.5f);
		Control->rightMotor(0.5f);
	}
	SetCursorPos(ptMouse.x, ptMouse.y);
	Control->writeController();
}