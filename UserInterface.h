#include <HAPI_lib.h>

#pragma once
class CUserInterface
{
public:
	static CUserInterface* Inst();
	~CUserInterface(void);//destructor
	bool update();
	// returns if the key is pressed down or not
	bool jump();
	bool fire();
	bool left();
	bool right();
	bool enter();
	bool escape();
	bool back();
	//
	int letter(int i);
private:
	CUserInterface();//constructor
	static CUserInterface* UI;
	HAPI_TKeyboardData data;// used to read input from the keyboard


};



