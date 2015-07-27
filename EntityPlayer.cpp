#include "EntityPlayer.h"
#include "UserInterface.h"

CEntityPlayer::CEntityPlayer()
{
}


CEntityPlayer::~CEntityPlayer(void)
{
}
//sets the default values fro the player
void CEntityPlayer::create()
{
	
	posX=50;
	posY=200;
	graphic=0;
	frame=8;//first image facing right
	fired=false;
	direction=true;
	jump=false;//if the player is already jumping
	energy=true;//if the player is on a floor
	frame_change=0;
	mana=true;//used for shooting
	active=true;
	side=3;
	speed=5;
	health=100;

}//end create();

//
void CEntityPlayer::update()
{
	frame_change++;

		posY+=speed;//used to simulate gravity so the player can fall
		
		//if space bar is down and has not been used to shoot before
		if(CUserInterface::Inst()->fire() && mana)
		{
			fired=true;
			mana=false;//the space bar must be released before another fireball can be shot
			graphic=6;//set to the wizard shooting image
			set_ani(get_dir());//make the wizard face the right way 
		}
		//if space bar is not pressed
		else if(!CUserInterface::Inst()->fire())
		{
			//reset animation and allow another fireball to be used
			if (get_dir())
			{set_ani(8);}
			else{set_ani(0);}
			mana=true;

			//if space bar is not pressed and jump is while not in the air
			if (CUserInterface::Inst()->jump()  && !jump && energy )
			{
				jump=true;
				jumpstart=HAPI->GetTime();
				graphic=3;//jumping wizard image
				set_ani(0);
				energy=false;//stops double jump
			}//end if

			//space bar not but left arrow is pressed
			if (CUserInterface::Inst()->left())
			{
				posX-=speed;
				set_dir(false);
				set_ani(7-((frame_change%15)/2)+get_dir()*8);//changes which way the wizard is facing 
			}//end if

			//space bar not but right is
			if (CUserInterface::Inst()->right())
			{
				posX+=speed;
				set_dir(true);
				set_ani(((frame_change%15)/2)+get_dir()*8);
			}//end if

			//while player is jumping
			if (jump)
			{
				posY-=12;//increase the player's height
				DWORD shift=HAPI->GetTime();
					
				//stop the player from enetring the hud
					if (posY < 34)
					{
						posY=34;
					}//end if

					//changes the jump animation with the correct rotation of the wizard
					if (direction)
					{
						frame=((shift-jumpstart)/200)+4;
					}else{
							frame=(3-((shift-jumpstart)/400));
						}//end else

					//jump is based on time after 800 milliseconds return the walking wizard
					if (shift-jumpstart > 800)
					{
						jump=false;
						graphic=0;
						set_ani(((frame_change%15)/2)+get_dir()*8);
					}//end if
			}else{//if not jumping or shooting set the graphic to the wizard walking
					graphic=0;
				}//end else
		}else{//if space bar not down set fired to false
			fired=false;
			}//end else

}//end update()