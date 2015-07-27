#include <HAPI_lib.h>
#include "WorldModel.h"
#include "UserInterface.h"
#include "Graphics.h"
#include "Sounds.h"
#include "Files.h"

//creates an instance of my world model with width 1024 height 290
CWorldModel world(1024,290);
//different states to be displayed on screen
enum eStateType {
	eStateMenu=3,
	eStateGame=1,
	eStateScore=2,
	eStateExit=0
};
void HAPI_Main()
{
	world.init();
	//number of ticks = 1000/ticker
	int ticker = 50;//20 ticks a second
	int lasttick=0;

		while(HAPI->Update() && world.game_state != eStateExit)
		{			
			int totaltime=HAPI->GetTime();

			CUserInterface::Inst()->update();

			if (world.game_state == eStateGame)
			{
				if(totaltime-lasttick > ticker)
				{
					//upadates the game positions every tick
					world.update_game();
					lasttick=totaltime;
				}
				//draws the game on screen while the game is being played
				world.render_game();
			}

			if (world.game_state == eStateMenu)
			{
				if(totaltime-lasttick > ticker)
				{
					//allows the user to input a name for the high score table
					world.set_name();
					lasttick=totaltime;
				}
				//display menu
				world.render_menu();
			}

			if (world.game_state == eStateScore)
			{
				//shows the high score table
				world.render_scores();
			}
		}

		delete CUserInterface::Inst();
		delete CGraphics::Inst();
		delete CSounds::Inst();
		delete CFiles::Inst();
}