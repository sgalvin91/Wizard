#include "EntityEnemy.h"
#include <HAPI_lib.h>


CEntityEnemy::CEntityEnemy(void)
{
}


CEntityEnemy::~CEntityEnemy(void)
{
}

void CEntityEnemy::update()
{
	frame_change++;//always increase

	//if going left
	if(!direction)
	{
		posX-=speed;//reduce x co-ordinate
		frame=(frame_change%10)/3;
	}
	else//if going right
	{
		posX+=speed;//increase x-co-ordinate
		frame=((frame_change%10)/3)+4;
	}

	//if the enemy is too far right change direction
	if (center_x+50 < posX)
	{
		direction = false;
	}

	//if the enemy is too far left change direction 
	if(center_x-50 > posX)
	{
		direction = true;
	}
	//if enemy is at the the center then fire a bullet 
	if (posX == center_x-1)
		fired=true;
}

//them same for each enemy but with different health and speed values based on which type which is dirived from the graphic
void CEntityEnemy::create(int x,int y,int z)
{
	posX=x;
	posY=y;
	center_x=x+1;
	active=true;
	graphic=z;//this is the integer that changes the behavior of the enemy
	frame=0;
	frame_change=0;
	fired=false;
	side=4;//


	switch (z)
	{
		case 5://basic enemy that fires laser's
			health=40;
			speed=3;
			direction = false;
			break;
		case 7://advanced enemy thats fires rockets
			health=50;
			speed=3;
			direction = false;
			break;
		case 11://elite enemies which fire plasma orbs
			health=70;
			speed=2;
			direction = true;
			break;
	}

	//because some enemies so not exist in the file they appear at the value 45,218 if this is the case then make thme inactive
	if (posX==45 && posY ==218)
		active = false;
}
