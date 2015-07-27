#include "WorldModel.h"
#include "Graphics.h"
#include "Sounds.h"
#include "WorldEntity.h"
#include "EntityPlayer.h"
#include "BossAxe.h"
#include "BossDino.h"
#include "BossGun.h"
#include "BossMech.h"
#include "EntityEnemy.h"
#include "UserInterface.h"
#include "EntityBullet.h"
#include "EntityExplosion.h"
#include "Files.h"
#include <iostream>

CWorldModel::CWorldModel(int x, int y) 
{
	screenWidth=x;
	screenHeight=y;
}

CWorldModel::~CWorldModel(void)
{ //removes every memory location stored by the entity removing memory leaks
	for (unsigned int i=0;i<entityV.size();i++)
	{
		delete entityV[i];
	}
	
}

void CWorldModel::init()
{
	CGraphics::Inst()->initialise(screenWidth,screenHeight);// loads the sprites need to run the game
	CSounds::Inst()->initalisation();//loads all the sound effect files that are needed
	game_state=2;//starts on the high score table
}

void CWorldModel::delete_level()
{
	//deletes the memory loacations used by the Vector 
	for (unsigned int i=0;i<entityV.size();i++)
	{
		delete entityV[i];
	}
	//clears the Vector so it can be used for the next level
	entityV.clear();
}

void CWorldModel::next_level()
{
	//if at the start of the game do not try and destroy the level as none exists and crashes the game
	if (level !=0)
	{
	delete_level();
	}


	level++;
	//loads the required level from file
	CFiles::Inst()->load_level(level);
	//creates all the entities for the level
	create_entity();
	//sets the players health using life
	entityV[entities[ePlayer]]->set_health(100-life);
	screen=1;//sets the screen count to 1
	boss_attack=false;//stops the boss from moving until the players reaches screen 5
	end_cond="GAME OVER";//defult setting
	CSounds::Inst()->play_background(level,boss_attack);// starts plying the background music
}

//used while game_state = game
void CWorldModel::update_game()
{
	/*
	while traversing the vector different letters are used to move through different parts
	k is ued for the bullets
	j is used for the enemies
	i is used for the entities e.g. the walls and floors
	e is used for the explosions
	the player and boss because there is only one of each are called explicitly using ePlayer and eBoss
	*/

	//go through the vector starting at the bullets and stopping when you reach the explosions since they are the next type of entity
	for(int k=entities[eBullet];k<entities[eExplosion];k++)
	{
		//is the bullets side = the playes side e.g a fireball
		if(entityV[k]->get_side() == eSidePlayer)
		{
			//if the player has fired and there is a fireball not being used
			if (entityV[entities[ePlayer]]->get_fired() && !entityV[k]->get_active())
			{
				//shoot the fireball using x,y and direction from the player
				entityV[k]->shoot(entityV[entities[ePlayer]]->get_x(),entityV[entities[ePlayer]]->get_y(),entityV[entities[ePlayer]]->get_dir());
				HAPI->StopSound(CSounds::Inst()->get_sound(entityV[k]->get_id()));
				//stops the player firing two fireballs at the same time
				entityV[entities[ePlayer]]->set_fired(false);
				HAPI->PlayASound(CSounds::Inst()->get_sound(entityV[k]->get_id()));

			}//end if
		}else//if not a player bullet
		{
			//go through the vector with the for loop [k] to find enemies
			for(int j=entities[eEnemy];j<entities[eBoss]; j++)
			{
				/*
				if the enemy is trooper(basic) and the bullet is a laser(least powerful)
				if the enemy is a solider(advanced and the bullet is a rocket(medieum power)
				if the enemy is a marine Elite and the bullet is a plasma orb(most powerful)
				*/
				if ((entityV[j]->get_id() == eEnemyTrooper && entityV[k]->get_id() == eBulletLaser) || (entityV[j]->get_id() == eEnemySoldier && entityV[k]->get_id() == eBulletRocket) || (entityV[j]->get_id() == eEnemyMarine  && entityV[k]->get_id() == eBulletPlasma))
				{
					//if the enemy has fired and there is an inactive bullet
					if (entityV[j]->get_fired() && !entityV[k]->get_active())
					{
						//shoot the fireball using x,y and direction from the selected enemy
						entityV[k]->shoot(entityV[j]->get_x(),entityV[j]->get_y(),entityV[j]->get_dir());
						HAPI->StopSound(CSounds::Inst()->get_sound(entityV[k]->get_id()));
						entityV[j]->set_fired(false);
						HAPI->PlayASound(CSounds::Inst()->get_sound(entityV[k]->get_id()));
					}//end if
				}//end if
			}//end for [j]


			//if the boss has fired and there is a spare rocket
			if (entityV[entities[eBoss]]->get_fired() && !entityV[k]->get_active() && entityV[k]->get_id() == eBulletRocket)
			{
				//shoot the fireball using x,y and direction from the boss
				entityV[k]->shoot(entityV[entities[eBoss]]->get_x(),entityV[entities[eBoss]]->get_y()+20,entityV[entities[eBoss]]->get_dir());
				entityV[entities[eBoss]]->set_fired(false);
				HAPI->StopSound(CSounds::Inst()->get_sound(entityV[k]->get_id()));
				HAPI->PlayASound(CSounds::Inst()->get_sound(entityV[k]->get_id()),true);
			}//end if
		}//end if

	}//end for [k]

		//move through the entire Vector calling the entities update function
		for(unsigned int i=0;i<entityV.size();i++)
		{
			if (entityV[i]->get_active() && i != entities[eBoss])
			entityV[i]->update(); 
		}//end for
		/* 
		if the game has been running for 1 minute then reset the backgound music to the start
		this makes sure then there is always some music playing during the game
		*/
		int gamertime=HAPI->GetTime();
		if(gamertime-lastchange > 60*1000)
		{
			CSounds::Inst()->play_background(level,boss_attack);
			lastchange=gamertime;
		}//end if
	//checks for collisions more on this function later							
	check_collisions();

		//if the player is on screen 5 or the boss is active
		//players can't stop the boss from moving if they leave the screen
		if (screen == 5 || boss_attack)
		{
			entityV[entities[eBoss]]->update();
			boss_attack=true;
		}//end if

		//if the player goes off the right edge of the screen
		if (entityV[entities[ePlayer]]->get_x() > 1024)
		{
			scroll(-1);
			screen++;
			if(screen ==5)//change background music if the player reaches screen 5
				CSounds::Inst()->play_background(level,boss_attack);
		}//end if
			
		//if the player goes off the left side of the screen
		if (entityV[entities[ePlayer]]->get_x() < -32)
		{
			scroll(1);
			screen--;
		}//end if

		//if the boss has no health left
		if (entityV[entities[eBoss]]->get_health() <= 0)
		{	
			score+=100;
			//if the player has killed the level 4 boss
			if (level==4)
			{
				game_state=3;//go to the menu
				HAPI->StopStreamedMedia();
				score+=entityV[entities[ePlayer]]->get_health();//add the remaining players health to the score
				end_cond="YOU WIN";//congratulate the player
			}else//if it is not the level 4 boss which has been killed
				{
					//keep the players health in a sperate variable as the player is abou to go out of scope
					life=entityV[entities[ePlayer]]->get_health();
					//load the next level
					next_level();
				}//end else end if
		}//end if

		//if the players health is reduced to 0
		if (entityV[entities[ePlayer]]->get_health() <=0 )
		{	
			game_state=3;
			HAPI->StopStreamedMedia();//go tot the menu
		}//end if
}//end update_game()

void CWorldModel::check_collisions()
{
	//runs 3 seperate collision functions to keep the code mamagable
	player_collisions();
	bullet_collisions();
	boss_collisions();
}

//all collisions relating to the player
void CWorldModel::player_collisions()
{
	//for all the bullets in the Vector
	for(int k=entities[eBullet];k<entities[eExplosion];k++)
	{
		//if the bullet is active and not on the players side
		if (entityV[k]->get_active() && entityV[k]->get_side() != eSidePlayer)
		{
			//if the players IS NOT colliding with the bullet
			if((entityV[k]->get_x()+CGraphics::Inst()->get_width(entityV[k]->get_id()) < entityV[entities[ePlayer]]->get_x() || entityV[k]->get_x() > entityV[entities[ePlayer]]->get_x()+CGraphics::Inst()->get_width(entityV[entities[ePlayer]]->get_id()))||
				(entityV[k]->get_y()+CGraphics::Inst()->get_height(entityV[k]->get_id()) < entityV[entities[ePlayer]]->get_y() || entityV[k]->get_y()> entityV[entities[ePlayer]]->get_y()+CGraphics::Inst()->get_height(entityV[entities[ePlayer]]->get_id())))
			{}//do nothing
			else
				{
					entityV[entities[ePlayer]]->set_health(entityV[k]->get_damage());//chnage the players health by the damage of the bullet
					entityV[k]->set_active(false);//make the bullet inactive
					HAPI->StopSound(CSounds::Inst()->get_sound(entityV[k]->get_id()));//stop the bullet from making a sound
				}//end else collision
		}//end if
	}//end for

	//for all the entities in the Vector so all the walls and floors
	for(int i=entities[eStart];i<entities[eEnemy];i++)
	{
		//if they are active and not Netral so the background is not tested against or it would be constant collisions
		if(entityV[i]->get_active() && entityV[i]->get_side() != eSideNetral)
		{
			//if the player IS NOT colliding
			if((entityV[i]->get_x()+CGraphics::Inst()->get_width(entityV[i]->get_id()) < entityV[entities[ePlayer]]->get_x() || entityV[i]->get_x() > entityV[entities[ePlayer]]->get_x()+CGraphics::Inst()->get_width(entityV[entities[ePlayer]]->get_id()))||
				(entityV[i]->get_y()+CGraphics::Inst()->get_height(entityV[i]->get_id()) < entityV[entities[ePlayer]]->get_y() || entityV[i]->get_y()> entityV[entities[ePlayer]]->get_y()+CGraphics::Inst()->get_height(entityV[entities[ePlayer]]->get_id())))
			{}//do nothing
			else
				{//if the entity the player has hit is a wall
					if(entityV[i]->get_side() == eSideWall)
					{
						//if the player is going right
						if (entityV[entities[ePlayer]]->get_dir())
						{
							//stop the player from going further right
							entityV[entities[ePlayer]]->set_x(entityV[i]->get_x()-CGraphics::Inst()->get_width(entityV[entities[ePlayer]]->get_id()));

						}else if(!entityV[entities[ePlayer]]->get_dir())//if the player is going left
						{
							//stop the player from going left
							entityV[entities[ePlayer]]->set_x(entityV[i]->get_x()+CGraphics::Inst()->get_width(entityV[i]->get_id()));
						}//end else if
					}//end if

					//if the player has hit a floor with the lowest 8 pixels of its rectangle
					if(entityV[i]->get_side() == eSideFloor && entityV[i]->get_y()-entityV[entities[ePlayer]]->get_y() > 56)
					{
						entityV[entities[ePlayer]]->set_y(entityV[i]->get_y()-63);//move the player so it is sitting onto of the floor
						entityV[entities[ePlayer]]->set_energy(true);//allow the player to jump
					}else if(entityV[i]->get_side() == eSideFloor && entityV[i]->get_y()-entityV[entities[ePlayer]]->get_y() < 24)// if the player hits a floor with the top thrid of its rectangle
					{
						entityV[entities[ePlayer]]->set_y(entityV[i]->get_y()+8);//move the player below the floor stopping the player from jumping through floors
					}//end else if
			}//end else collisions
		}//if active and netral
	}//end for [i]

	//if the players height is below the bottom of the screen
	if (entityV[entities[ePlayer]]->get_y() > 300)
		//reduce the players life to 0
	{entityV[entities[ePlayer]]->set_health(100);}
}

//all bullet collisions not exept player<->bullet collions as they were done earlier
void CWorldModel::bullet_collisions()
{
	//loop through the bullets is the vector
	for(int k=entities[eBullet]; k<entities[eExplosion];k++)
	{
		//if the bullet is active 
		if (entityV[k]->get_active())
		{
			//loop throught the enemies in the vector
			for(int j=entities[eEnemy];j<entities[eBoss];j++)
			{
				//if the enemy is active and the bullet is a fireball so on the players side
				if(entityV[j]->get_active() && entityV[k]->get_side() == eSidePlayer)
				{
					//if the enemy IS NOT colliding with the bullet
					if((entityV[k]->get_x()+CGraphics::Inst()->get_width(entityV[k]->get_id()) < entityV[j]->get_x() || entityV[k]->get_x() > entityV[j]->get_x()+CGraphics::Inst()->get_width(entityV[j]->get_id()))||
						(entityV[k]->get_y()+CGraphics::Inst()->get_height(entityV[k]->get_id()) < entityV[j]->get_y() || entityV[k]->get_y()> entityV[j]->get_y()+CGraphics::Inst()->get_height(entityV[j]->get_id())))
					{} // do nothing
					else
						{
							entityV[k]->set_active(false);//set the bullet to inactive
							HAPI->StopSound(CSounds::Inst()->get_sound(entityV[k]->get_id()));
							entityV[j]->set_health(entityV[k]->get_damage());//reduce the enemyies health by the damage of the fireball
							//if the enemies health is 0 or less
							if (entityV[j]->get_health() <= 0)
							{	
								entityV[j]->set_active(false);//remove the enemy
								score+=10;//increase score by 10
								//loop through the explosions in the Vector
								for (int e=entities[eExplosion];e<entities[eEnd];e++)
								{
									//if the explosion is inactive
									if (!entityV[e]->get_active())
									{
										//create an explosion 
										entityV[e]->shoot(entityV[j]->get_x(),entityV[j]->get_y(),true);
										HAPI->StopSound(CSounds::Inst()->get_sound(entityV[e]->get_id()));
										HAPI->PlayASound(CSounds::Inst()->get_sound(entityV[e]->get_id()));
										break;//only do this for the first inactive explosion found
									}//end if
								}//end for [e]
						}//end if
					}//end else collision
				}//end if
			}//end for [j]
												
						
				// loops through all the entities in the vector
				for(int i=0;i<entities[1];i++)
				{
					//if active and not the background
					if(entityV[i]->get_active() && entityV[i]->get_side() != eSideNetral)
					{
						//if the bullets and entities ARE NOT colliding
						if((entityV[k]->get_x()+CGraphics::Inst()->get_width(entityV[k]->get_id()) < entityV[i]->get_x() || entityV[k]->get_x() > entityV[i]->get_x()+CGraphics::Inst()->get_width(entityV[i]->get_id()))||
							(entityV[k]->get_y()+CGraphics::Inst()->get_height(entityV[k]->get_id()) < entityV[i]->get_y() || entityV[k]->get_y()> entityV[i]->get_y()+CGraphics::Inst()->get_height(entityV[i]->get_id())))
						{}//do nothing
						else
							{
								entityV[k]->set_active(false);//make the bullet inactive
								HAPI->StopSound(CSounds::Inst()->get_sound(entityV[k]->get_id()));
								//loop through all the explosions in the Vector
								for ( int e=entities[eExplosion];e<entities[eEnd];e++)
								{
									//if the explosion is inactive
									if (!entityV[e]->get_active())
									{
										//create an explosion
										entityV[e]->shoot(entityV[k]->get_x(),entityV[k]->get_y(),true);
										HAPI->StopSound(CSounds::Inst()->get_sound(entityV[e]->get_id()));
										HAPI->PlayASound(CSounds::Inst()->get_sound(entityV[e]->get_id()));
										break;//only create explosion once
									}//end if
								}//end for [e]
						}// end else collisions
				}//end if
			}//end for [i]
		}//if bullet is active
	}//end for [k]
}//end bullet_collision()


//check collisons for everything to do with the boss
void CWorldModel::boss_collisions()
{
	//check each bullet in the Vector
	for(int k=entities[eBullet]; k<entities[eExplosion];k++)
	{
		//if bullet is active and nelongs to the player
		if (entityV[k]->get_active() && entityV[k]->get_side() == eSidePlayer)
		{
			//if the bullet IS NOT colliding with the boss
			if((entityV[k]->get_x()+CGraphics::Inst()->get_width(entityV[k]->get_id()) < entityV[entities[2]]->get_x() || entityV[k]->get_x() > entityV[entities[2]]->get_x()+CGraphics::Inst()->get_width(entityV[entities[2]]->get_id()))||
				(entityV[k]->get_y()+CGraphics::Inst()->get_height(entityV[k]->get_id()) < entityV[entities[2]]->get_y() || entityV[k]->get_y()> entityV[entities[2]]->get_y()+CGraphics::Inst()->get_height(entityV[entities[2]]->get_id())))
			{} // do nothing
			else
				{
					entityV[k]->set_active(false);//bullet is removed
					HAPI->StopSound(CSounds::Inst()->get_sound(entityV[k]->get_id()));
					entityV[entities[eBoss]]->set_health(entityV[k]->get_damage());//boss's health reduced by the damage of the bullet
					//for each explosion in the Vector
					for (int e=entities[eExplosion];e<entities[eEnd];e++)
					{
						//if the explosion is not active
						if (!entityV[e]->get_active())
						{
							//create explosion
							entityV[e]->shoot(entityV[k]->get_x(),entityV[k]->get_y(),true);
							HAPI->StopSound(CSounds::Inst()->get_sound(entityV[e]->get_id()));
							HAPI->PlayASound(CSounds::Inst()->get_sound(entityV[e]->get_id()));
							break;//only created once per collision
						}//end if
					}//end for [e] 		
					
				}//end else collision
		}//end if
	}//end for [k]

	//if the player and the boss ARE NOT colliding
	if((entityV[entities[ePlayer]]->get_x()+CGraphics::Inst()->get_width(entityV[entities[ePlayer]]->get_id()) < entityV[entities[eBoss]]->get_x() || entityV[entities[ePlayer]]->get_x() > entityV[entities[eBoss]]->get_x()+CGraphics::Inst()->get_width(entityV[entities[eBoss]]->get_id()))||
				(entityV[entities[ePlayer]]->get_y()+CGraphics::Inst()->get_height(entityV[entities[ePlayer]]->get_id()) < entityV[entities[eBoss]]->get_y() || entityV[entities[ePlayer]]->get_y()> entityV[entities[eBoss]]->get_y()+CGraphics::Inst()->get_height(entityV[entities[eBoss]]->get_id())))
			{}//do nothing
			else
				{
					entityV[entities[ePlayer]]->set_health(entityV[entities[eBoss]]->get_damage());//reduce the players health by the boss damage

					//turns the boss around stopping multiple collisions and killing the player instantly
					if(entityV[entities[eBoss]]->get_dir() && level ==2)
					{
						entityV[entities[eBoss]]->set_dir(false);
						entityV[entities[ePlayer]]->set_x(entityV[entities[ePlayer]]->get_x()+20);//moves the player away from the boss
					}else if(!entityV[entities[eBoss]]->get_dir() && level == 2)
						{
							entityV[entities[eBoss]]->set_dir(true);
							entityV[entities[ePlayer]]->set_x(entityV[entities[ePlayer]]->get_x()-20);//moves the player away from the boss
						}//end else if
							
				}//end else collison
}//end boss_collisions()


void CWorldModel::create_entity()
{
	int tracker=0;//used to set the arry entities to the changes in objects in the vector
	entities[tracker]=0;//0
	tracker++;
	//create the background first so it is drawn first
	CWorldEntity *back_01 = new CWorldEntity;
	back_01->create(0,34,11+level,true,eSideNetral);
	entityV.push_back(back_01);
	//create the floors
	for(int i=0;i<59;i++)
	{
	CWorldEntity *floor0=new CWorldEntity;
	floor0->create(CFiles::Inst()->get_hor_x(i),CFiles::Inst()->get_hor_y(i),8,true,eSideFloor);
	entityV.push_back(floor0);
	}
	//create the walls
	for(int i=0;i<30;i++)
	{
	CWorldEntity *wall0=new CWorldEntity;
	wall0->create(CFiles::Inst()->get_vert_x(i),CFiles::Inst()->get_vert_y(i),9,true,eSideWall);
	entityV.push_back(wall0);
	}
	entities[tracker]=entityV.size();// 1 in the array used to check in the vector
	tracker++;
	//create the enemies
	for(int i=0; i<14; i++)
	{
	CEntityEnemy *gunner0=new CEntityEnemy;
	gunner0->create(CFiles::Inst()->get_ene_x(i),CFiles::Inst()->get_ene_y(i),CFiles::Inst()->get_ene_id(i));
	entityV.push_back(gunner0);
	}
	entities[tracker]=entityV.size();//2 in the array used to check in the vector
	tracker++;
	//more detail on the actual function
	create_boss();
	entities[tracker]=entityV.size();//3 in the array used to check in the vector
	tracker++;
	//create player
	CEntityPlayer *player = new CEntityPlayer;
	player->create();
	entityV.push_back(player);
	entities[tracker]=entityV.size();//4 in the array used to check in the vector
	tracker++;
	//create fireballs
	for (int i=0;i<3;i++)
	{
	CEntityBullet *fire1 = new CEntityBullet;
	fire1->create(1);
	entityV.push_back(fire1);
	}
	//create lasers
	for (int i=0; i<9;i++)
	{
	CEntityBullet *laser1=new CEntityBullet;
	laser1->create(10);
	entityV.push_back(laser1);
	}
	//create rockets
	for(int i=0;i<9;i++)
	{
	CEntityBullet *rocket1=new CEntityBullet;
	rocket1->create(20);
	entityV.push_back(rocket1);
	}
	//create plasma
	for(int i=0;i<9;i++)
	{
	CEntityBullet *plasma1=new CEntityBullet;
	plasma1->create(21);
	entityV.push_back(plasma1);
	}
	entities[tracker]=entityV.size();//5 in the array used to check in the vector
	tracker++;
	//create explosions
	for (int i=0;i<10; i++)
	{
	CEntityExplosion *bang1 = new CEntityExplosion;
	bang1->create(0,0,4,false,eSideNetral);
	entityV.push_back(bang1);
	}
	entities[tracker]=entityV.size();//6 in the array used to check in the vector
}//end create_entity()

//creates the boss which is different for each level
void CWorldModel::create_boss()
{
	switch (level)
	{
	case 1://level 1
		{
			CBossGun *gun = new CBossGun;
			gun->create(5000,215,18,200,0,0);//no speed and no damage so can't hurt the player fires rockets
			entityV.push_back(gun);
			break;
		}
	case 2:
		{ 
			CBossAxe *axe = new CBossAxe;
			axe->create(4576,160,16,300,20,20);// very fast and quite a bit of damage does not shoot
			entityV.push_back(axe);
			break;
		}
	case 3:
		{
			CBossMech *mech = new CBossMech;
			mech->create(4896,208,19,400,0,4);//very slow but no damage fires rockets
			entityV.push_back(mech);
			break;
		}
	case 4:
		{
			CBossDino *dino = new CBossDino;
			dino->create(5000,34,17,500,100,10);// slow but if he hits the player its instant game over
			entityV.push_back(dino);
			break;
		}
	}//end switch
}//end create_boss()

//draws the game to screen using the graphics class
void CWorldModel::render_game()
{
	CGraphics::Inst()->clearscreen(0,0,0);//clears the screen so there is a black workspace
	HAPI->ChangeFont( "Arial", 24, 800);//change the font size very hard on the frame rate
		CGraphics::Inst()->display_hud(entityV[entities[ePlayer]]->get_health(),score);//gives the graphics players health and score

		//starting with the background send all the entities to the graphics class
		for(unsigned int i=0;i<entityV.size();i++)
		{
			//only send them im the entity is active
			if (entityV[i]->get_active())
				CGraphics::Inst()->refresh(entityV[i]->get_x(),entityV[i]->get_y(),entityV[i]->get_id(),entityV[i]->get_ani()); 
		}//end for [i]

		//if the boss is updating display the boss health bar
		if(boss_attack)
		{CGraphics::Inst()->display_boss(entityV[entities[eBoss]]->get_health());}

		HAPI->ChangeFont( "Arial", 12, 700);//reset font back

		if (CUserInterface::Inst()->escape())
		{
			game_state=0;//exits the program cleanly
		}//end if

}
//draws the menu using the graphics class
void CWorldModel::render_menu()
{
	CGraphics::Inst()->clearscreen(0,0,0);//sets the screen to default
	CGraphics::Inst()->display_end(end_cond,score);//send the end condition (WIN or GAME OVER) with the score to the graphics class

		//if the player has input a name send that name to the graphics {not doing this caused runtime errors as HAPI was trying render text that didn't exist
		if (players_name != "")
			CGraphics::Inst()->display_name(players_name);

}//end render_menu()


//used when the player goes of the edge of the screen to move the entities
void CWorldModel::scroll(int a)
{
	//for all entities in the Vector
	for(int i=0;i<entityV.size();i++)
	{
		//if the entity is not the player
		if(i != entities[ePlayer])
		/*
		a = 1 when the player goes of the left of the screen shifting everything to the right
		a = -1  when the player goes of the right of the screen shifting everything to the left
		*/
		entityV[i]->set_x(entityV[i]->get_x()+(1024*a));//add + or - 1024 dpending on weather the player went left or right off the screen a 


		//if the entity is an enemy or the boss
		if(i >= entities[eEnemy] && i < entities[ePlayer])
		{
			entityV[i]->set_center(1024*a);//change the center to the with the same value as x so the enemies can still move
		}
	}
	//if te player went off the left
	if(a == 1)
	{entityV[entities[ePlayer]]->set_x(990);}//set the players position to right hand side of the screen
	
	//if the player went of the right
	if(a == -1)
	{entityV[entities[ePlayer]]->set_x(2);}//set the players position to the left hand side of the screen
}//end scroll()


//used to allow the player to input a name to used in the high score table
void CWorldModel::set_name()
{
	HAPI_TKeyboardData data;
	HAPI->GetKeyboardData(&data);

	for(int a=0; a<255; a++)
	{
			//if backpsace or return not pressed
			if (CUserInterface::Inst()->letter(a) && (!CUserInterface::Inst()->back() || !CUserInterface::Inst()->enter()))
			{
				char_input[char_count] = char(a); //cast the int of the number pressed to the relivant char code.
				 if(char_count < 10)
				 char_count++; //move along the array
			}//end if

			//if backspace is pressed
			if (CUserInterface::Inst()->back())
			{
				if (char_count > 0)
				{
					char_count--; //move back one space
					char_input[char_count] = ' '; //replace what was in that place
				}//end if
			}//end if

			//if enter is pressed 
			if(CUserInterface::Inst()->enter())
			{
				game_state=2;//change to to the high score table
			}//end if

			if (CUserInterface::Inst()->escape())
			{
				game_state=0;//exits the program cleanly
			}//end if

	}//end for[a]

if (char_count == 0)
{
	players_name="";
}else{
		players_name = char_input; // convert the char[] to string
	}//end else
}//end set_name()

//sends the high score table to the grapics*/
void CWorldModel::render_scores()
{
	CFiles::Inst()->load_scores();//loads the most recent high score table

	//if the player has a new score
	if(score  > 0)
	{
		CFiles::Inst()->set_high_score(players_name,score);//send to the file class to check if it goes on the high score table
	}//end if
	HAPI->ChangeFont( "Arial", 24, 1000);
	//for all of the scores in the table
	for(int a=0; a<10; a++)
	{
		CGraphics::Inst()->display_score(a,CFiles::Inst()->get_name(a),CFiles::Inst()->get_points(a));//send the name and score to the graphics for rendering
	}//end for [a]
	CGraphics::Inst()->display_title();//asks the graphics to display the name of the game
	CFiles::Inst()->save_scores();//saves the high scores to file via the file class

	level=0;//set level at 0 this screen is seen before the game starts which is why the level is set here

	//if the return key is pressed
	if(CUserInterface::Inst()->enter())
	{
		life=100;
		players_name="";
		lastchange=0;
		score=0;
		char_count=0;//used as players health
		game_state=1;//play game
		next_level();//load the next level
	}//end if

	//if Esc is pressed
	if (CUserInterface::Inst()->escape())
	{
		game_state=0;//exits the program cleanly
	}//end if
}//end render_scores()