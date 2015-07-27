#pragma once
#include <vector>

class CWorldEntity;
class CWorldModel
{
public:
	//creates the WorldModel using the passed variables as the width and height
	CWorldModel(int x,int y);
	//destroys the WorldModel
	~CWorldModel(void);
	//upadtes the game
	void update_game();
	//updates the game graphics
	void render_game();
	//displays the menu for typing in a name
	void render_menu();
	//displays the high score table
	void render_scores();
	//used to change the level
	void next_level();
	//used by the main to create a name for the score and then end of a game
	void set_name();
	//called once by the main for all values that are required at the start
	void init();

	int screen;// which screen the game is currently on (1-5)
	int level;//the current game level (1-4)
	int game_state;//used by the main to detect which state the game is in

private:
	// run after every entity has been updated
	void check_collisions();
	//used inside the check_collisons() to keep the code manageable
	void player_collisions();
	void bullet_collisions();
	void boss_collisions();
	//creates the entities and puts them in the entity vector
	void create_entity();
	//creates a different boss for each level and stores it inside the Vector
	void create_boss();
	//allows movement throught the level changing which bit of the level can ben seen
	void scroll(int a);
	//removes the level from the Vector including the player and bullets
	void delete_level();

	int screenWidth;//set by the constructor
	int screenHeight;//set by the constructor
	int char_count;//used to type a players name on the menu screen
	char char_input[10];//the array which accepts the characters from the keyboard for the playes name
	int entities[7];//used to traverse the entity vector
	std::vector<CWorldEntity*> entityV;//contains all the information needed to run the game
	std::string players_name;//converted from char_input 
	std::string end_cond;//used to detect weather the player has won or lost
	bool boss_attack;// used for 
	int lastchange;//used to makee sure the background music is allways playing
	int score;//the current score of the game
	int life;//keeps the players health when the player is removed from the vector between levels

	//used as a check in collisions so two from the same side do not collide
	enum Side{
			eSideNetral=1,
			eSideWall=2,
			eSidePlayer=3,
			eSideEnemy=4,
			eSideFloor=5
		};

	//used to check the id of the bullet so the correct graphic, update and sound is used
	enum Bullet{
			eBulletFireball=1,
			eBulletLaser=10,
			eBulletRocket=20,
			eBulletPlasma=21
		};
	//used to check the id of the enemy so the correcr graphic and update
	enum Enemy{
			eEnemyTrooper = 5,
			eEnemySoldier = 7,
			eEnemyMarine = 11
			};

	//used to move inside the entity Vector(entityV) as they are the locations in an array which has the start values of the different ypes of entities
	enum entity{
			eStart=0,
			eEnemy=1,
			eBoss=2,
			ePlayer=3,
			eBullet=4,
			eExplosion=5,
			eEnd=6
	};
};

