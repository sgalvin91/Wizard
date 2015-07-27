#pragma once
#include "enitityboss.h"
class CBossAxe :
	public CEnitityBoss
{
public:
	CBossAxe(void);//called when loading the boss for level 2
	~CBossAxe(void);
	void update();//only called when the player reaches screen 5
};

