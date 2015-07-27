#pragma once
#include "worldentity.h"
//child of world entity
class CEntityExplosion :
	public CWorldEntity
{
public:
	CEntityExplosion(void);
	~CEntityExplosion(void);
	void update();//changes the explosions animation until it no longer exists
	void shoot(int x,int y,bool dir);//fires explosion

private:
	int lastbang;//used for timer to work out the last time the explosion was set off

};

