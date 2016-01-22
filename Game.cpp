#include "Game.h"
#include "GameLogic.h"
#include "main.h"
#include "Music.h"
#include "Timer.h"
#include "config.h"
#include "DebugMessage.h"
#include "GameMenu.h"
#include "Player.h"

#include <ctime>

	int keyz[10] = { SDLK_UP,SDLK_UP,SDLK_DOWN,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT,SDLK_LEFT,SDLK_RIGHT,SDLK_b,SDLK_a };
	int keyzl = 10;
	int konamiindex = 0;
	int konami = 0;

//Define Menu
	std::string menu[] = { "New Game", "Continue", "Option", "Exit" };
	/*menu[0] = "New Game";
	menu[1] = "Continue";
	menu[2] = "Option";
	menu[3] = "Exit";*/

//The frames per second
const int FRAMES_PER_SECOND = 60;

 //Keep track of the current frame
int frame = 0;

//Whether or not to cap the frame rate bool
bool cap = true;

//The frame rate regulator
Timer fps;
Timer logos;

CPlayer playerEnt;
CMainLogic mainLogic;
CGameMenu gameMenu;

// Gain access to keystate array
   Uint8 *keys = SDL_GetKeyState(NULL);

CGame::CGame(void)
{
	//Ugly
	gameMenu.Create(menu, MENU_MAX);
}

CGame::~CGame(void)
{
}

int CGame::IntRand()
{
	//TODO: The Seed is really terrible
	srand(time(NULL));
	return rand()%255;
}

void CGame::Think()
{
	while( SDL_PollEvent( &GameEvent ) )
	 {
		  //If the user has Xed out the window
		 if( GameEvent.type == SDL_QUIT )
		 {
			 //Quit the program
			 mainLogic.game = false;
		 }

		if(gamestate == STATE_LOGO)
		{
			if(keys[SDLK_RETURN])
				CGame::SetGameState(STATE_TITLE);
		}
		else if (gamestate == STATE_TITLE)
		{
			if(GameEvent.type == SDL_KEYDOWN)
			{
				if (!konami)
				{
					if(GameEvent.key.keysym.sym == keyz[konamiindex])
					{
						konamiindex++;
						if (konamiindex == keyzl)
						{
							CMusic::PlaySong("Konami", false, false);
							konami = 1;
						}
					}
					else
						konamiindex = 0;
				}
			}
				if (keys[SDLK_RETURN])
				{
					switch (gameMenu.menuDecision())
					{
						case 0: CGame::SetGameState(STATE_GAME);break;
						case 1: CGame::SetGameState(STATE_GAME);break;
						case 2: CGame::SetGameState(STATE_GAME);break;
						case 3: mainLogic.game = 0;break;
					}
				}
			}
		else if (gamestate == STATE_GAME)
		{
			playerEnt.Think();
		}
	}
}

void CGame::SetGameState(int state)
{
	//TODO: Time for some Hardcoded Drama
	if (state == STATE_TITLE)
	{
		if (CConfig::debugFlag)
			CDebugMessage::AddMessage("DEBUG: Loaded Title");
		CMusic::PlaySong("Title", true, false);

		//CGameMenu(menu, 4);
	}
	else if (state == STATE_GAME)
	{
		CDebugMessage::AddMessage("DEBUG: Loaded Game.");
		//CMusic::PlaySong("Game", true, false);
		//playerEnt.Think();
	}

	gamestate = state;
}

int CGame::LoadImages()
{
	ifstream file;
	file.open("cfg/images.cfg");

	if (!file)
		return 0; //Error loading the images.cfg

	string imagename = "";
	string filename = "";

	getline(file, imagename);

	while(!file.eof())
	{
		file >> imagename;
		file >> filename;

		SpriteList[imagename] = filename;
	}

	file.close();

	//TODO: SDL_Surfaces that create themselves. UPDATE: May not even need this.
	title_logo = CGameLogic::load_image("Title");
	airhorn_off = CGameLogic::load_image("AirhornOff");
	airhorn = CGameLogic::load_image("Airhorn");
	logo1 = CGameLogic::load_image("Logo1");
	logo2 = CGameLogic::load_image("Logo2");
	CGameLogic::messagebox = CGameLogic::load_image("MessageBox");
	CPlayer::player_sprite = CGameLogic::load_image("player");

	if ((!airhorn_off) || (!airhorn) || (!title_logo) || (!logo1) || (!logo2))
		return 0;

	return 1;
}

int CGame::FreeImages()
{
	SDL_FreeSurface(title_logo);
	SDL_FreeSurface(airhorn_off);
	SDL_FreeSurface(airhorn);
	SDL_FreeSurface(logo1);
	SDL_FreeSurface(logo2);
	return 1;
}

void CGame::Render()
{
	if (gamestate == STATE_LOGO)
	{
		CGame::DrawLogos();
	}
	else if (gamestate == STATE_TITLE)
	{
		DrawTitle();
		gameMenu.Draw();
		gameMenu.Think();
	}
	else if (gamestate == STATE_GAME)
	{
		CGameLogic::DrawBackground(CGameLogic::screen, 0, 25, 0);
		playerEnt.Draw();
	}

	if (CConfig::preRelease)
	CGameLogic::DrawText(CGameLogic::screen, "Demo Version",(CGameLogic::ScreenWidth-120), 10, 156, 8, 8, false);

	RegulateFrameRate();
}

void CGame::RegulateFrameRate()
{
	 //Increment the frame counter
	frame++;
	 //Keep track of the current frame
	int frame = 0;
	//Whether or not to cap the frame rate
	bool cap = true;
	//The frame rate regulator
	Timer fps;

	 //If we want to cap the frame rate
	if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) ) {
		//Sleep the remaining frame time
		SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() ); }
}

void CGame::AirHornOn()
{
	CGameLogic::Draw( 0, 0, airhorn, CGameLogic::screen );
}

void CGame::flip()
{
	//Update Screen
	SDL_Flip( CGameLogic::screen );
}

void CGame::DrawLogos()
{
	//TODO: Fade in between and such
		CGameLogic::DrawBackground(CGameLogic::screen, 255, 255, 255);

		if (logoframe < 240)
			CGameLogic::Draw( (CGameLogic::ScreenWidth/2)-(logo1->w/2), (CGameLogic::ScreenHeight/2)-(logo1->h/2), logo1, CGameLogic::screen );
		else if (logoframe < 480)
			CGameLogic::Draw( (CGameLogic::ScreenWidth/2)-(logo2->w/2), (CGameLogic::ScreenHeight/2)-(logo2->h/2), logo2, CGameLogic::screen );
		else if (logoframe > 480)
			SetGameState(STATE_TITLE);

		logoframe++;
}

void CGame::DrawTitle()
{
	CGameLogic::DrawBackground(CGameLogic::screen, 0, 0, 0);
	CGameLogic::Draw( (CGameLogic::ScreenWidth/2)-(title_logo->w/2), (title_logo->h/1.5), title_logo, CGameLogic::screen );
	CGameLogic::DrawProgressiveText(CGameLogic::screen, "You've met with a terrible fate, haven't you?", 0, (CGameLogic::ScreenHeight/2), 255, 255, 255, true);
	CGameLogic::DrawText(CGameLogic::screen, "The Legend of", 0, 32, 255, 255, 255, true);
	CGameLogic::DrawText(CGameLogic::screen, "(C) 2013 - Buff Drinklots. There is no copyright.", 0, (CGameLogic::ScreenHeight-25), 255, 255, 255, true);

	/*CGameLogic::message = "You're a petite little thing";

	if (CGameLogic::message != "")
		CGameLogic::MessageBox(CGameLogic::screen, "NAM", CGameLogic::message);*/
}
