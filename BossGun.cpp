#include "BossGun.h"


CBossGun::CBossGun(void)
{
	lastshot=0;
}


CBossGun::~CBossGun(void)
{
}

/*
level 1 boss does not move or change direction but fires a constant stream of missiles at the player
*/
void CBossGun::update()
{
	frame_change++;
	set_ani((frame_change%10)/3);

	currenttime=HAPI->GetTime();

	// every 3 seconds fire a missile
	if(currenttime - lastshot > 3000)
	{
		fired=true;
		lastshot=currenttime;
	}
}