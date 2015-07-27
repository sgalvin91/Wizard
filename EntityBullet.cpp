#include "EntityBullet.h"
#include <HAPI_lib.h>


CEntityBullet::CEntityBullet(void)
{
}


CEntityBullet::~CEntityBullet(void)
{
}

void CEntityBullet::update()
{
	frame_change++;

		//if the bullet is going left
		if(!direction)
		{
			posX-=speed;
			frame=((frame_change%10)/3);
		}
		else //if the bullet is going right
		{
			posX+=speed;
			frame=(((frame_change%10)/3)+4);
		}

		//if the bullet reaches the edge of the screen
		if (posX < -25 || posX > 1024)
		{
			active=false;
		}
}

void CEntityBullet::shoot(int x,int y,bool dir)
{
	posX=x+(24*dir);
	active=true;
	direction=dir;

	//changes the  y position of  where the bullet is fired from depending on what type of bullet was fired
	switch (graphic)
	{
	case 1:posY=y+16;break;
	case 10:posY=y+13;break;
	case 20:posY=y+10;break;
	case 21:posY=y+30;break;
	}
}
//creates the bullet note that x and y position are set on the shoot function so are not required for create
void CEntityBullet::create(int id)
{
	graphic=id;
	frame=0;
	active=false;
	frame_change=0;
	//if the bullet is a fireball make it be on the players side
	if (graphic == 1)
		side=3;
	else//if not then it belongs on the enemy side
		side=4;
	//chnages the stats of the bullet depending on which graphic is being used
	switch (graphic)
	{
	case 1://stats of the fireball
		speed=10;
		damage=10;
		break;
	case 10://state of the laser
		speed=10;
		damage=5;
		break;
	case 20://stats of the rocket
		speed=15;
		damage=15;
		break;
	case 21://stats of the plasma
		speed=20;
		damage=25;
		break;
	}
}