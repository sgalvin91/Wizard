#pragma once
#include "worldentity.h"
//child of world entity
class CEntityBullet :
	public CWorldEntity
{
public:
	CEntityBullet(void);//constructor
	~CEntityBullet(void);//destructor
	void create(int id);//takes the graphic id
	void update();
	void shoot(int x,int y,bool dir);//takes an x and y position along with a direction
	};

