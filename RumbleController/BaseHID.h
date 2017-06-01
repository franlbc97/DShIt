#pragma once
#define T 0.01



typedef unsigned short WORD;
class BaseHID
{
public:
	BaseHID(float t) :tUpdate(t){};
	~BaseHID(){};
	
	void Actualiza();
	inline float LT() { return lTrigger; };
	inline float RT(){ return rTrigger; };
	inline float RJXf(){ return fThumbRXf; };
	inline float RJYf(){ return fThumbRYf; };
	inline float LJX(){ return fThumbLX; };
	inline float LJY(){ return fThumbLY; };
	void leftMotor(float aux){ lMotor = aux; };
	void rightMotor(float aux){ rMotor = aux; };
	bool BD(WORD button){ return (button & wButtonsDown); };
	bool BU(WORD button){ return (button & wButtonsUp); };




protected:
	bool controllerConnected;
	WORD wButtons;
	WORD wLastButtons;
	WORD wButtonsDown, wButtonsUp;
	//Definición de ejes de joysticks. Los usaremos en el intervalo [-1.0,1.0]
	float fThumbRX, fThumbRY, fThumbLX, fThumbLY;
	float fThumbRXf, fThumbRYf, fThumbLXf, fThumbLYf;

	//Definición de floats para los triggers. Intervalo [0.0, 1.0]	
	float rTrigger, lTrigger;
	const float aTR = T / (0.1) + T;
	float lMotor, rMotor;


	virtual void mandoAHID() = 0;
	virtual bool readController() = 0;
	virtual void writeController() = 0;

	float tUpdate;

};

