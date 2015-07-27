#pragma once
#include <fstream>
#include <iostream>
#include <string>

class CFiles
{
public:
	//singleton class
	static CFiles* Inst();
	//destructor
	~CFiles(void);
	//loads from file the values of each level when called
	 void load_level(int a);
	 //loads the high score table from scores.sfg
	 void load_scores();
	 //used by the world model to get the x position of a specified floor
	const int get_hor_x(int x);
	 //used by the world model to get the y position of a specified floor
    const int get_hor_y(int y);
	 //used by the world model to get the x position of a specified wall
	const int get_vert_x(int x);
	 //used by the world model to get the y position of a specified wall
	const int get_vert_y(int y);
	 //used by the world model to get the x position of a specified enemy
	const int get_ene_x(int x);
	 //used by the world model to get the y position of a specified enemy
	const int get_ene_y(int y);
	 //used by the world model to get the id  of a specified enemy
	const int get_ene_id(int z);
	 //used by the world model to get a name from the high score table
	const std::string get_name(int a);
	 //used by the world model to get a points total from the high score table
	const int get_points(int a);
	/*
	takes the players score to see if it can be included in the high score table and if it can
	puts the socre and the players name in the correct position
	*/
	void set_high_score(std::string n,int p);
	//the current values stored in name[] and points[] and saves them to files scores.sfg
	void save_scores();

private:
	int hor_x[60];
	int hor_y[60];
	int vert_x[30];
	int vert_y[30];
	int enemy_x[15];
	int enemy_y[15];
	int enemy_id[15];
	std::string name[10];
	int points[10];
	void load_horis(int a);
	void load_verts(int a);
	void load_enemy(int a);
	CFiles();
	static CFiles* file;

};

