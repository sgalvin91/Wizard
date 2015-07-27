#pragma once

#include <string>
#include <HAPI_lib.h>

using namespace std;
class CSprite
{
public:
	CSprite(string w,int x,  int y, BYTE* z, int nf);//constructor
	~CSprite(void);//destructor
	string name;//name of the image file
	int width;// its width in pixels
	int height;//its height in pixels
	BYTE* pos;//where in memeory this Sprite is stored
	int number_of_frames;//how many different frames the image has for animation
	int frame_size;// worked out in the constructor as width / number_of_frames



};

