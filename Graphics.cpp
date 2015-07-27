#include "Graphics.h"
#include "Sprite.h"
#include <iostream>
#include <sstream>
#include <assert.h>

CGraphics* CGraphics::graphic=NULL;

CGraphics::CGraphics()
{
}


CGraphics::~CGraphics(void)
{
	int d=spriteV.size();
	for (int i=0;i<d;i++)
	{
		delete spriteV[i]->pos;
		delete spriteV[i];
	}
}

CGraphics* CGraphics::Inst()
{
	if(graphic == NULL)
	{
		graphic = new CGraphics;
	}
	return graphic;
}

void CGraphics::initialise(int w,int h)
{
	screenWidth=w;
	screenHeight=h;
	BytesPerPixel=4;

  if (!HAPI->Initialise(&screenWidth,&screenHeight))
          return;
  screen=HAPI->GetScreenPointer();

  //pointers to in the images inside the vector
 BYTE* player=0;
 BYTE* dead=0;
 BYTE* fire=0;
 BYTE* jump=0;
 BYTE* bang=0;
 BYTE* gunner=0; 
 BYTE* rocket=0;
 BYTE* marine=0;
BYTE* magic=0;
BYTE* rock_h=0;
BYTE* rock_v=0;
BYTE* laser=0;
BYTE* missile=0;
BYTE* plasma=0;
BYTE* cloud=0;
BYTE* back_01=0;
BYTE* back_02=0;
BYTE* back_03=0;
BYTE* back_04=0;
BYTE* boss_01=0;
BYTE* boss_02=0;
BYTE* boss_03=0;
BYTE* boss_04=0;



  destination.set(0,screenWidth,0,screenHeight);
 spriteV.push_back(new CSprite("images/wizard_walking.tga",512,64,player,16));
 spriteV.push_back(new CSprite("images/fireball.tga",256,32,fire,8));
 spriteV.push_back(new CSprite("images/wizard_dying.tga",128,32,dead,2));
 spriteV.push_back(new CSprite("images/wizard_jumping.tga",256,64,jump,8));
 spriteV.push_back(new CSprite("images/explosion.tga",512,32,bang,16));
 spriteV.push_back(new CSprite("images/enemy_gun.tga",256,64,gunner,8));
 spriteV.push_back(new CSprite("images/wizard_shooting.tga",64,64,magic,2));
 spriteV.push_back(new CSprite("images/enemy_rocket.tga",256,64,rocket,8));
 spriteV.push_back(new CSprite("images/H_rock.tga",128,8,rock_h,1));
 spriteV.push_back(new CSprite("images/V_rock.tga",8,64,rock_v,1));
 spriteV.push_back(new CSprite("images/laser.tga",128,8,laser,8));
 spriteV.push_back(new CSprite("images/enemy_armour.tga",256,64,marine,8));
 spriteV.push_back(new CSprite("images/level_01.tga",1024,256,back_01,1));
 spriteV.push_back(new CSprite("images/level_02.tga",1024,256,back_02,1));
 spriteV.push_back(new CSprite("images/level_03.tga",1024,256,back_03,1));
 spriteV.push_back(new CSprite("images/level_04.tga",1024,256,back_04,1));
 spriteV.push_back(new CSprite("images/enemy_blood_boss.tga",512,128,boss_01,8));
 spriteV.push_back(new CSprite("images/enemy_beast_boss.tga",512,256,boss_02,4));
 spriteV.push_back(new CSprite("images/enemy_gun_boss.tga",256,64,boss_03,4));
 spriteV.push_back(new CSprite("images/enemy_mech_boss.tga",512,64,boss_04,8));
 spriteV.push_back(new CSprite("images/missile.tga",128,8,missile,8));
 spriteV.push_back(new CSprite("images/plasma.tga",128,16,plasma,8));

  int errors=0;
  for(unsigned int i=0;i<spriteV.size();i++)
  {
 if(!HAPI->LoadTexture(spriteV[i]->name,&spriteV[i]->pos))
	 {
		 std::string error= "failure to load texture " + spriteV[i]->name + " exiting program!"; 
		 HAPI->UserMessage(error,"error message");
		 errors++;
		 return;
	 }
  }
  assert (errors < 1);
	HAPI->SetShowFPS(true);
}

void CGraphics::alphablit(BYTE* dest, BYTE* image,CRectangle &destination, CRectangle &source, int posX, int posY,int frame,int num)
{
	CRectangle changed;
	changed.set(posX,posX+spriteV[num]->frame_size,posY,posY+spriteV[num]->height);//a rectagle with one frame of the image in it
	changed.clipTo(destination);//alters to image if it is off screen


	
	changed.top-=posY;//set top to 0
	changed.bottom-=posY;//keeps the dimensions
	changed.left-=posX;
	changed.right-=posX;

	if (posY < 0)
		{posY=0;}

	if (posX < 0)
		{posX=0;}
	//if left is greater then right then it is totally off the screen and therefore do nothing
	if (posX > destination.right)
	{return;}

	//if top is greater then bottom then it is totally off the screen and therefore do nothing
	if (posY > destination.bottom)
	{return;}

	//if right is less then left then it is totally off the screen and therefore do nothing
	if (posX+(spriteV[num]->frame_size) < destination.left)
	{return;}

	//if bottom is less then top then it is totally off the screen and therefore do nothing
	if (posY+changed.height() < destination.top)
	{return;}
	
	BYTE *destPnter=dest+(posX+(posY*destination.width()))*4;//where on screen to start drawing the image
	BYTE *sourcePnter=image+((changed.left+spriteV[num]->frame_size*frame)+(changed.top*source.width()))*4;//where on the image to start drawing
	//for the height of the image that is on screen
	for (int y=changed.top;y<changed.bottom;y++)
	{
		//for the width of the image which is on screen
		for(int x=changed.left+spriteV[num]->frame_size*frame;x<changed.right+spriteV[num]->frame_size*frame;x++)
		{
				BYTE blue=sourcePnter[0];
				BYTE green=sourcePnter[1];
				BYTE red=sourcePnter[2];
				BYTE alpha=sourcePnter[3];
				

				destPnter[0]=destPnter[0]+((alpha*(blue-destPnter[0])) >> 8);
				destPnter[1]=destPnter[1]+((alpha*(green-destPnter[1])) >> 8);
				destPnter[2]=destPnter[2]+((alpha*(red-destPnter[2])) >> 8);

		//move source and dest pointer to next pixel
		sourcePnter+=4;
		destPnter+=4;
		}

		// Move source pointer to next line 
		sourcePnter+=(source.width()-changed.width())*4;
		destPnter+=(destination.width()-changed.width())*4;

	}
}

void CGraphics::fastblit(CRectangle &back,BYTE* dest,BYTE* source,int posX,int posY)
{
	BYTE *destPnter=dest+(posX+posY*back.width())*4;
	BYTE *sourcePnter=source;
	for (int y=0;y<back.height();y++)
		{
			memcpy(destPnter,sourcePnter,back.width()*4);
			// Move source pointer to next line
			sourcePnter+=back.width()*4;
			// Move destination pointer to next line
			destPnter+=screenWidth*4;
		}
}

void CGraphics::clearscreen(int red, int green, int blue)
{
	for (int pixel=0;pixel < screenHeight * screenWidth *4;pixel+=4)
	{
			screen[pixel]=blue;
			screen[pixel+1]=green;
			screen[pixel+2]=red;
	}
}


void CGraphics::refresh(int x, int y,int id,int animate)
{
	source.set(0,spriteV[id]->width,0,spriteV[id]->height);
	//if trying to blit a background image use fastblit else use alpha blit
	if (id >= 12 && id <=15)
	{
		fastblit(source,screen,spriteV[id]->pos,x,y);
	}
	else
	{
		alphablit(screen,spriteV[id]->pos,destination,source,x,y,animate,id);
	}
}


//get framesize of image to get the width of the rectangle used for collisions
const int CGraphics::get_width(int a)
{
	return spriteV[a]->frame_size;
}

//get height of image to get the width of the rectangle used for collisions
const int CGraphics::get_height(int a)
{
	return spriteV[a]->height;
}

std::string CGraphics::convert(int val)
{
	std::ostringstream stream; // create a stream
	stream << val; // insert value into stream
	return stream.str(); // return as a string
}

//rendered on the game loop 
void CGraphics::display_hud(int a,int b)
{
	HAPI->RenderText(50,0,HAPI_TColour(0,0,255),"HEALTH : ");
	HAPI->RenderText(150,0,HAPI_TColour(0,0,255),convert(a));
	HAPI->RenderText(850,0,HAPI_TColour(0,255,0),"SCORE :");
	HAPI->RenderText(950,0,HAPI_TColour(0,255,0),convert(b));
}

void CGraphics::display_name(std::string a)
{
	HAPI->ChangeFont( "Arial", 36, 1000);
	HAPI->RenderText(100,100,HAPI_TColour(255,255,255),a);
	HAPI->ChangeFont( "Arial", 12, 700);

}

void CGraphics::display_end(std::string a,int b)
{
	HAPI->ChangeFont( "Arial", 72, 1500);
	HAPI->RenderText(350,100,HAPI_TColour(255,0,0),a);
	HAPI->ChangeFont( "Arial", 36, 1000);
	HAPI->RenderText(750,50,HAPI_TColour(0,255,0),"SCORE");
	HAPI->RenderText(125,50,HAPI_TColour(255,255,255),"Input Name");
	HAPI->RenderText(800,100,HAPI_TColour(0,255,0),convert(b));
	HAPI->ChangeFont( "Arial", 12, 700);
}

//display boss health bar when boss is active
void CGraphics::display_boss(int b)
{
	HAPI->RenderText(250,0,HAPI_TColour(255,0,0),"Boss : ");

	for (int y=5; y<30;y++)
	{
		for (int x=325;x<(325+b);x++)
		{
			screen[((x+(y*screenWidth))*4)]=0;//blue
			screen[((x+(y*screenWidth))*4)+1]=0;//green
			screen[((x+(y*screenWidth))*4)+2]=255;//red
		}
	}
}

void CGraphics::display_score(int a,std::string n,int p)
{
	HAPI->RenderText(300,25+(25*a),HAPI_TColour(255,255,255),n);
	HAPI->RenderText(600,25+(25*a),HAPI_TColour(255,255,255),convert(p));
}

void CGraphics::display_title()
{
	HAPI->ChangeFont("Arial",40,800);
	HAPI->RenderText(20,50,HAPI_TColour(255,0,0),"Are you a wizard");
	HAPI->RenderText(700,50,HAPI_TColour(255,0,0),"Are you a wizard");
	HAPI->ChangeFont( "Arial", 12, 700);
	HAPI->RenderText(750,200,HAPI_TColour(255,0,0),"press ENTER to play");
	HAPI->RenderText(100,200,HAPI_TColour(255,0,0),"press ESC to quit");
}

