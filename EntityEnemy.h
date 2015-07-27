#pragma once
#include "WorldEntity.h"
//child of world entity
class CEntityEnemy :
	public CWorldEntity
{
public:
	CEntityEnemy(void);//constructor
	~CEntityEnemy(void);//destructor
	void update();
	void create(int x,int y,int z);//x and y positions with a graphic id
};

