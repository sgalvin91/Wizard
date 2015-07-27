#pragma once


class CWorldEntity
{
public:
	CWorldEntity();
	~CWorldEntity(void);
	//although virtual this function is used by the background, the wall and the floors
	virtual void create(int x,int y,int id,bool flag,int col);
	//used only so the world model can access the childrens update()
	virtual void update();
	//never used but required for both the explosions and bullets
	virtual void shoot(int x, int y,bool dir);

	//gets the x position of the entity
	const int get_x();
	//gets the y position of the entity
	const int get_y();
	//gets the graphic id used by Graphics.cpp
	const int get_id();
	//gets which frame in the image should be used by Graphics
	const int get_ani();
	//direction of the entity not used by base entities or explosions
	const bool get_dir();
	//not used by player and base entities
	const bool get_active();
	/*
	1 is netral
	3 is player
	4 is enemy
	2 is wall
	5 is floor 
	is was going to some weird maths using % to work out what to do when each entity collided
	this was unnessary as only the objects that can collide are now tested
	*/
	const int get_side();
	//not used for base entities, bullets and explosions
	const int get_health();
	//not used by base entities, explosions,player and enemies
	const int get_damage();
	//only used by player, enemies and the boss
	const bool get_fired();

	void set_x(int x);
	void set_y(int x);
	void set_id(int x);
	void set_ani(int x);
	void set_dir(bool y);
	void set_active(bool y);
	void set_health(int x);
	void set_fired(bool y);
	//used for enemies and one boss
	void set_center(int x);
	//used by the player only as a jump check
	void set_energy(bool y);

	//all children classes can access these data memebers
protected:
	int posX;
	int posY;
	int graphic;
	int frame;
	int center_x;
	bool active;
	bool direction;
	int frame_change;
	int side;
	bool energy;
	int health;
	int damage;
	int speed;
	bool fired;
};

