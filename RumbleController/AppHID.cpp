#include "AppHID.h"
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

//Definicion de calbacs
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//Manejador de ventana
HWND g_hWnd;
WCHAR g_szMessage[4][1024] = { 0 };


void GeneraEventos(HIDXbox * Control);
void GeneraEventos(HIDWii * Control);

VOID CALLBACK  updateControllerState(){
	controller.Actualiza();
	ShitMote.readController();
	GeneraEventos(&ShitMote);

}
int APIENTRY wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int){
	
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


	if (Control->LeftThumb_down())
		mouse_event(MOUSEEVENTF_LEFTDOWN, ptMouse.x, ptMouse.y, 0, NULL);
	if (Control->LeftThumb_up())
		mouse_event(MOUSEEVENTF_LEFTUP, ptMouse.x, ptMouse.y, 0, NULL);

	if (Control->RightThumb_down())
		mouse_event(MOUSEEVENTF_RIGHTDOWN, ptMouse.x, ptMouse.y, 0, NULL);
	if (Control->RightThumb_up())
		mouse_event(MOUSEEVENTF_RIGHTUP, ptMouse.x, ptMouse.y, 0, NULL);


	if (Control->Back_down())
		keybd_event(VK_ESCAPE, 0x18, NULL, NULL);
	if (Control->Back_up())
		keybd_event(VK_ESCAPE, 0x18, KEYEVENTF_KEYUP, NULL);

	if (Control->Start_down())
		keybd_event(VK_RETURN, 0x18, NULL, NULL);
	if (Control->Start_up())
		keybd_event(VK_RETURN, 0x18, KEYEVENTF_KEYUP, NULL);



	//Botones X y B para inicio y fin
	if (Control->X_down()) {
		keybd_event(VK_HOME, 0x18, NULL, NULL);
	}
	if (Control->X_up()) {
		keybd_event(VK_HOME, 0x18, KEYEVENTF_KEYUP, NULL);
	}
	if (Control->B_down()) {
		keybd_event(VK_END, 0x18, NULL, NULL);
	}
	if (Control->B_up()) {
		keybd_event(VK_END, 0x18, KEYEVENTF_KEYUP, NULL);
	}

	//Botones Y y A para Av pag Re pag
	if (Control->A_down()) {
		keybd_event(VK_PRIOR, 0x18, NULL, NULL);
	}
	if (Control->A_up()) {
		keybd_event(VK_PRIOR, 0x18, KEYEVENTF_KEYUP, NULL);
	}

	if (Control->Y_down()) {
		keybd_event(VK_NEXT, 0x18, NULL, NULL);
	}
	if (Control->Y_up()) {
		keybd_event(VK_NEXT, 0x18, KEYEVENTF_KEYUP, NULL);
	}




	//USO DEL PAD
	if (Control->DPadLeft_down()) {
		keybd_event(VK_LEFT, 0x18, NULL, NULL);
	}
	if (Control->DPadLeft_up()) {
		keybd_event(VK_LEFT, 0x18, KEYEVENTF_KEYUP, NULL);
	}
	if (Control->DPadRight_down()) {
		keybd_event(VK_RIGHT, 0x18, NULL, NULL);
	}
	if (Control->DPadRight_up()) {
		keybd_event(VK_RIGHT, 0x18, KEYEVENTF_KEYUP, NULL);
	}
	if (Control->DPadUp_down()) {
		keybd_event(VK_UP, 0x18, NULL, NULL);
	}
	if (Control->DPadUp_up()) {
		keybd_event(VK_UP, 0x18, KEYEVENTF_KEYUP, NULL);
	}
	if (Control->DPadDown_down()) {
		keybd_event(VK_DOWN, 0x18, NULL, NULL);
	}
	if (Control->DPadDown_up()) {
		keybd_event(VK_DOWN, 0x18, KEYEVENTF_KEYUP, NULL);
	}



	//Rueda del ratón:
	if (Control->LeftShoulder_down())
		mouse_event(MOUSEEVENTF_WHEEL, ptMouse.x, ptMouse.y, 10, NULL);
	if (Control->RightShoulder_down())
		mouse_event(MOUSEEVENTF_WHEEL, ptMouse.x, ptMouse.y, -10, NULL);

	if (Control->BD(0xFFFFF)) {
		Control->leftMotor(0.5f);
		Control->rightMotor(0.5f);
	}
	SetCursorPos(ptMouse.x, ptMouse.y);
	Control->writeController();
}

void GeneraEventos(HIDWii * Control)
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	if (Control->LJX() != 0) {
		ptMouse.y += Control->LJX() * 15;
	}
	if (Control->LJY() != 0) {
		ptMouse.x -= -Control->LJY() * 15;
	}

	
	
	if (Control->TWO_down())
		mouse_event(MOUSEEVENTF_LEFTDOWN, ptMouse.x, ptMouse.y, 0, NULL);
	if (Control->TWO_up())
		mouse_event(MOUSEEVENTF_LEFTUP, ptMouse.x, ptMouse.y, 0, NULL);

	if (Control->ONE_down())
		mouse_event(MOUSEEVENTF_RIGHTDOWN, ptMouse.x, ptMouse.y, 0, NULL);
	if (Control->ONE_up())
		mouse_event(MOUSEEVENTF_RIGHTUP, ptMouse.x, ptMouse.y, 0, NULL);

	if (Control->DOWN_up()) {
		keybd_event(VK_LEFT, 0x18, NULL, NULL);

		keybd_event(VK_LEFT, 0x18, KEYEVENTF_KEYUP, NULL);
	}
	if (Control->RIGHT_up()) {
		keybd_event(VK_DOWN, 0x18, NULL, NULL);

		keybd_event(VK_DOWN, 0x18, KEYEVENTF_KEYUP, NULL);
	}

	if (Control->LEFT_up()) {
		keybd_event(VK_UP, 0x18, NULL, NULL);

		keybd_event(VK_UP, 0x18, KEYEVENTF_KEYUP, NULL);
	}
	
	if (Control->UP_up()) {
		keybd_event(VK_RIGHT, 0x18, NULL, NULL);

		keybd_event(VK_RIGHT, 0x18, KEYEVENTF_KEYUP, NULL);
	}

	if (Control->PLUS_down())
		mouse_event(MOUSEEVENTF_WHEEL, ptMouse.x, ptMouse.y, -10, NULL);
	if (Control->MINUS_down())
		mouse_event(MOUSEEVENTF_WHEEL, ptMouse.x, ptMouse.y, 10, NULL);
	
	if (Control->B_down()) {
	}
	if (Control->B_up()) {															
		keybd_event(VK_TAB, 0x18, NULL, NULL);
		keybd_event(VK_TAB, 0x18, KEYEVENTF_KEYUP, NULL);
	}

	if (Control->HOME_down()) {
		keybd_event(VK_LWIN, 0x18, NULL, NULL);

	}
	if (Control->HOME_up()) {
		keybd_event(VK_LWIN, 0x18, KEYEVENTF_KEYUP, NULL);

	}
	if (Control->A_down()) {
		keybd_event(VK_RETURN, 0x18, NULL, NULL);
	}
	if (Control->A_up()) {
		keybd_event(VK_RETURN, 0x18, KEYEVENTF_KEYUP, NULL);
	}


		
	SetCursorPos(ptMouse.x, ptMouse.y);
}
