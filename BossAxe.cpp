#include "BossAxe.h"
#include "HAPI_lib.h"

//class constructor
CBossAxe::CBossAxe(void)
{
}

//class destructor
CBossAxe::~CBossAxe(void)
{
}


void CBossAxe::update()
{
	frame_change++;//keeps incrementing while the program runs
	// if the boss is going left 
	if(!direction)
	{
		posX-=speed;
		frame=4-((frame_change%10)/3);//change which animation should be drawn
	}
	else//if the boss is going right
	{
		posX+=speed;
		frame=((frame_change%10)/3)+4;
	}//end else

	//if the boss moves to far from it's center position change its direction  so it keeps on screen
	if (center_x+460 < posX)
	{
		direction = false;
	}//end if

	if(center_x-470 > posX)
	{
		direction = true;
	}//end if
}//end update()
