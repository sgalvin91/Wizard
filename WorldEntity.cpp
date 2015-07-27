#include "WorldEntity.h"


CWorldEntity::CWorldEntity()
{
}


CWorldEntity::~CWorldEntity(void)
{
}

void CWorldEntity::update()
{
}

void CWorldEntity::create(int x,int y,int id,bool flag,int col)
{
	posX=x;
	posY=y;
	graphic=id;
	frame=0;
	active=flag;
	side=col;
}

const int CWorldEntity::get_x()
{
	return posX;
}

const int CWorldEntity::get_y()
{
	return posY;
}

const int CWorldEntity::get_id()
{
	return graphic;
}

const int CWorldEntity::get_ani()
{
	return frame;
}

const bool CWorldEntity::get_dir()
{
	return direction;
}

const bool CWorldEntity::get_active()
{
	return active;
}

void CWorldEntity::set_x(int x)
{
	posX=x;
}

void CWorldEntity::set_y(int x)
{
	posY=x;
}

void CWorldEntity::set_id(int x)
{
	graphic=x;
}

void CWorldEntity::set_ani(int x)
{
	frame=x;
}

void CWorldEntity::set_dir(bool y)
{
	direction=y;
}

void CWorldEntity::shoot(int x, int y,bool dir)
{
}


void CWorldEntity::set_active(bool y)
{
	active=y;
}


const int CWorldEntity::get_side()
{
	return side;
}

const int CWorldEntity::get_health()
{
	return health;
}

const int CWorldEntity::get_damage()
{
	return damage;
}

void CWorldEntity::set_health(int x)
{
	health-=x;
}

const bool CWorldEntity::get_fired()
{
	return fired;
}

void CWorldEntity::set_fired(bool y)
{
	fired=y;
}

void CWorldEntity::set_center(int x)
{
	center_x+=x;
}

void CWorldEntity::set_energy(bool y)
{
	energy=y;
}