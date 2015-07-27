#include "Rectangle.h"


CRectangle::CRectangle()
{
}


CRectangle::~CRectangle(void)
{
}

int CRectangle::width()
{
	return right-left;
}

int CRectangle::height()
{
	return bottom- top;
}

/*
changes the dimension of the rectangle so it fits onto the other
this means the image is only partially drawn
*/
void CRectangle::clipTo(const CRectangle& other)
{
	if (left<other.left)
left=other.left;
if (right>other.right)
right=other.right;
if (top<other.top)
top=other.top;
if (bottom>other.bottom)
	bottom=other.bottom;

}


//sets to rectangle's dimensions to the exect values past in
void CRectangle::set(int l, int r, int t,int b)
{
	left=l;
	right=r;
	top=t;
	bottom=b;

}