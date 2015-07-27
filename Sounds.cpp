#include "Sounds.h"
//sounds is a singleton class
CSounds* CSounds::sound=NULL;


CSounds::CSounds(void)
{
}


CSounds::~CSounds(void)
{
}

//only way to call the constructor
CSounds* CSounds::Inst()
{
	if(sound == NULL)
	{
		sound = new CSounds;
	}
	return sound;
}

//loads each of the sound waves 4 for bullets 1 for the explosions
void CSounds::initalisation()
{
	HAPI->LoadSound("sounds/fireball.wav",&fire);
	HAPI->LoadSound("sounds/explosion.wav",&exe);
	HAPI->LoadSound("sounds/zap1.wav",&laser);
	HAPI->LoadSound("sounds/missile.wav",&rocket);
	HAPI->LoadSound("sounds/plasma.wav",&plasma);
}

// input is the entities graphic id and is then checked in a switch to send the correct sound to the world model
const int CSounds::get_sound(int id)
{
	switch (id)
	{
	case 1:return fire;break;
	case 4:return exe;break;
	case 10:return laser;break;
	case 20:return rocket;break;
	case 21:return plasma;break;
	}
}

//selects the background music to be played based on the level
void CSounds::play_background(int lvl,bool boss)
{
	HAPI->StopStreamedMedia();//stops any background music which might be playing
	switch (lvl)
	{
	case 1:HAPI->PlayStreamedMedia("sounds/level1.wav",false);break;
	case 2:HAPI->PlayStreamedMedia("sounds/level2.wav",false);break;
	case 3:HAPI->PlayStreamedMedia("sounds/level3.wav",false);break;
	case 4:HAPI->PlayStreamedMedia("sounds/level4.wav",false);break;
	}//end switch

	//when the player reaches a boss play a different music track
	if (boss)
	{
		HAPI->StopStreamedMedia();
		HAPI->PlayStreamedMedia("sounds/boss.wav",false);
	}//end if
}//end play_background()