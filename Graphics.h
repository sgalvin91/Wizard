#pragma once
#include <HAPI_lib.h>
#include "Rectangle.h"
#include <string>
#include <vector>

class CSprite;


class CGraphics
{
public:
	static CGraphics* Inst();//singleton class
	~CGraphics(void);
	void initialise(int w, int h);//gives the window its height and width
	void clearscreen(int red, int green, int blue);//run at the start of every loop to set the screen colour
	void refresh(int x,int y,int id,int animate);//draws the specified sprite
	const int get_width(int a);//used in collisons to give a rectangle
	const int get_height(int a);//used in collisons to give a rectangle
	void display_hud(int a,int b);//set the hud of the game to the top of the screen
	void display_name(std::string a);//writes what the player types on screen
	void display_end(std::string a,int b);//displays end condition and score
	void display_boss(int b);//in game displays boss's health bar so players can see how close they are to killing him
	void display_score(int a,std::string n,int p);//displays the high score table from file with changes if nessacary
	void display_title();//gives instructions to the player on the high-score screen

private:
	void fastblit(CRectangle &back,BYTE* dest,BYTE* source,int posX,int posY); //background blit
	void alphablit(BYTE* dest, BYTE* image,CRectangle &destination, CRectangle &source, int posX, int posY,int frame,int num);//transparent blit
	std::string convert(int val);//converts and integer into a string
	CGraphics();//constructor
	static CGraphics* graphic;//used for singeton

		int screenWidth;//
		int screenHeight;
		int BytesPerPixel;//set as 4
		BYTE* screen;
		BYTE* back;//pointer to the background
		std::string background;//
		CRectangle destination;//a rectangle to size of the window that is drawn to
		CRectangle source;
		std::vector<CSprite*> spriteV;//vecotr with pointer to all the images required by the game
};