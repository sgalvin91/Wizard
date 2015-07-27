#include "BossMech.h"


CBossMech::CBossMech(void)
{
}


CBossMech::~CBossMech(void)
{
}

/*
this boss travels in a square around the screen firing missiles towards the center where the player is
*/
void CBossMech::update()
{
	//the bottom right of the square
	if(posX == 800 && posY == 208)
	{
		movement=1;//set the boss the travel left
		fired=true;
	}//end if

	// the top right of the square 
	if(posX == 800 && posY == 40)
	{
		movement=4;//set the boss to travel down
		direction=false;//sets the boss to look left so the missiles it fires go towards the player
		fired=true;
	}//end if

	//the bottom left of the square
	if(posX == 288 && posY == 208)
	{
		movement=2;//sets the boss to travel up
		direction=true;//sets the boss to look right to fire its missiles
		fired=true;
	}//end if

	//the top left of the square
	if (posX == 288 && posY == 40)
	{
		movement=3;//sets the boss to travel right
		fired=true;
	}//end if

	//when the boss reaches the middle of the sides fire a missile towards the dead center of the screen
	if(( posX == 288 || posX==800) && (posY == 124))
	{
		fired=true;
	}//end if


	//if the player leaves screen 5 set the boss back to its start position at the bottom right of the screen
	if (posX > 1024)
	{
		movement=0;
		posX=800+1024;
		posY=208;
	}//end if
				
	//takes the movement value and translates it into the required change in position
	switch (movement)
	{
	case 1: posX-=speed;break;
	case 2: posY-=speed;break;
	case 3: posX+=speed;break;
	case 4: posY+=speed;break;
	}

	frame_change++;//keeps incrementing

	//changes the animation depending on if the boss is going left or right
	if(!direction)
	{
		frame=4-((frame_change%10)/3);
	}
	else
	{
		frame=((frame_change%10)/3)+4;
	}//end else
}//end update()
