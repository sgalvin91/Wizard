#include "UserInterface.h"

//user interface defined as a singleton
CUserInterface* CUserInterface::UI=NULL;

CUserInterface::CUserInterface(void)
{
}


CUserInterface::~CUserInterface(void)
{
}

//constructor can only be called once byt this function
CUserInterface* CUserInterface::Inst()
{
	if(UI == NULL)
	{
		UI = new CUserInterface;
	}
	return UI;
}

//every loop reset the keyboard data to false
bool CUserInterface::update()
{
	if(HAPI->GetKeyboardData(&data))
		return true;
	if(!HAPI->GetKeyboardData(&data))
		return false;
}

//if the back button is pressed
bool CUserInterface::back()
{
	if(data.scanCode[HK_BACK])
	return true;
	else return false;
}

//if the enter key is pressed
bool CUserInterface::enter()
{
	if(data.scanCode[HK_RETURN])
	return true;
	else return false;
}

//if the escape key is pressed
bool CUserInterface::escape()
{
	if(data.scanCode[HK_ESCAPE])
	return true;
	else return false;
}

//if space bar is pressed
bool CUserInterface::fire()
{
	if(data.scanCode[HK_SPACE])
	return true;
	else return false;
}

//if the up arrow button is pressed
bool CUserInterface::jump()
{
	if(data.scanCode[HK_UP])
	return true;
	else return false;;
}

//if the left arrow button
bool CUserInterface::left()
{
	if(data.scanCode[HK_LEFT])
	return true;
	else return false;;
}

//if the right arrow button is pressed
bool CUserInterface::right()
{
	if(data.scanCode[HK_RIGHT])
	return true;
	else return false;
}

//used to collect the letters from the keyboard so they can be written to the screen
int CUserInterface::letter(int i)
{
	if (data.scanCode[i])
			return true;
	else return false;
}