#pragma once
#include "worldentity.h"/*a child of the WorldEntityClass*/
class CEnitityBoss :/*a miss type when adding class */
	public CWorldEntity
{
public:
	CEnitityBoss(void);//never called used as a bridge to consruct its children
	~CEnitityBoss(void);
	void create(int x,int y,int z,int a,int b,int c);//used by all the boss's so there values can be changed in the world model
	virtual void update();//used to call the update functions of the children
};

