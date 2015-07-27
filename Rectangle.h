#pragma once
class CRectangle
{
public:
	CRectangle();//constructor
	~CRectangle(void);//destructor
	void set(int l, int r, int t,int b);//sets the rectangles dimensions
	int width();//works out the width and returns it
	int height();//works out the high and returns it
	void clipTo(const CRectangle& other);//used to clip an image to the screen
	int left;
	int right;
	int top;
	int bottom;
};

