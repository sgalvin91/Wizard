#pragma once
#include "WorldEntity.h"
//child of world entity
class CEntityPlayer : 
	public CWorldEntity
{
public:
	CEntityPlayer(void);
	~CEntityPlayer(void);
	void update();
	void create();

private:
	bool jump;//used to keep the player going upwards once jump has been started
	bool mana;//stops the player from firing multiple fireballs with one press of space
	int jumpstart;//used as timer for when the jump starts to keep track of when to end the jump

};

