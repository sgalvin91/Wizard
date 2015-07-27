#include "Sprite.h"


CSprite::CSprite(string w,int x,  int y, BYTE* z, int nf)//constructor
{
	name=w;
	width=x;
	height=y;
	pos=z;
	number_of_frames=nf;
	frame_size=x/nf;//frame size worked out using other values so not needed to be passed
}


CSprite::~CSprite(void)
{
}
