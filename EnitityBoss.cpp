#include "EnitityBoss.h"


CEnitityBoss::CEnitityBoss(void)
{
}


CEnitityBoss::~CEnitityBoss(void)
{
}

//called by the create_boss() is the world model at the start of each level
void CEnitityBoss::create(int x,int y,int z,int a,int b,int c)
{
	posX=x;
	posY=y;
	center_x=x+32;//only boss for level 2 and 3 use this stat
	graphic=z;//each boss has a different graphic
	frame=0;//set the animation to 0
	frame_change=0; //
	health=a;//different health values
	damage=b;// boss do different amounts of damage
	active=true;//always active
	direction=false;//they always start by going left
	fired=false;//
	speed=c;// boss's travel at different speeds
	side=4;//make them an enemy
}

//used only as a bridge
void CEnitityBoss::update()
{
}