#include "EntityExplosion.h"
#include "HAPI_lib.h"


CEntityExplosion::CEntityExplosion(void)
{
	lastbang=0;
}


CEntityExplosion::~CEntityExplosion(void)
{
}

void CEntityExplosion::update()
{
	int current=HAPI->GetTime();
	if (current-lastbang > 100)
	{
		lastbang=current;
		set_ani(get_ani()+1);
	}

	if (get_ani() > 15)
	{
		active=false;
	}


}

void CEntityExplosion::shoot(int x,int y,bool dir)
{
	posX=x;
	posY=y;
	set_ani(0);
	active=true;
}
