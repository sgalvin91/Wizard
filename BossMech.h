#pragma once
#include "enitityboss.h"
/*
CBossMech is a child of CEnitityBoss class
*/
class CBossMech :
	public CEnitityBoss
{
public:
	CBossMech(void);//constructor
	~CBossMech(void);//destructor
	void update();
private:
	int movement;//used to work out which way the boss needs to move
};

