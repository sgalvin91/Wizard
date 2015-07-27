#pragma once
#include <HAPI_lib.h>
class CSounds
{
public:
	static CSounds* Inst();
	~CSounds(void);
	void initalisation();//loads the sounds from file into the class
	//turns the graphic id into which sound to be played
	const int get_sound(int id);
	//used to play a different background music
	void play_background(int lvl,bool boss);

private:
	CSounds(void);//constructor private
	static CSounds* sound;
	//holds the sound bites in place to be played when needed
	int fire;
	int laser;
	int plasma;
	int rocket;
	int exe;
};

