#include "BossDino.h"


CBossDino::CBossDino(void)
{
}


CBossDino::~CBossDino(void)
{
}
/*
levle 4 boss keeps moving towards the player and doesn't stop even if the player leaves the screen
if the player is hit by the boss his health is reduced by 100 meaning instant game over
*/
void CBossDino::update()
{
	frame_change++;

		posX-=speed;
		set_ani(4-((frame_change%10)/3));
}