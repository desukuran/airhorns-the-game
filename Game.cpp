#include "Game.h"
#include "GameLogic.h"
#include "main.h"
#include "Music.h"
#include "Timer.h"

#include <ctime>

	int keyz[10] = { SDLK_UP,SDLK_UP,SDLK_DOWN,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT,SDLK_LEFT,SDLK_RIGHT,SDLK_b,SDLK_a };
	int keyzl = 10;
	int konamiindex = 0;
	int konami = 0;

int main::game;

//The frames per second 
const int FRAMES_PER_SECOND = 60;

 //Keep track of the current frame 
int frame = 0; 

//Whether or not to cap the frame rate bool 
bool cap = true; 

//The frame rate regulator 
Timer fps;
Timer logos;

// Gain access to keystate array
   Uint8 *keys = SDL_GetKeyState(NULL);

	//Resolve the External Symbols
	map<string, string> CGame::SpriteList;
	SDL_Surface *CGame::airhorn;
	SDL_Surface *CGame::airhorn_off;
	SDL_Surface *CGame::title_logo;
	SDL_Surface *CGame::logo1;
	SDL_Surface *CGame::logo2;
	int CGame::gamestate;
	int CGame::logonumber;
	int CGame::logoframe;

CGame::CGame(void)
{	
	 while( SDL_PollEvent( &GameEvent ) ) 
	 {
		  //If the user has Xed out the window 
		 if( GameEvent.type == SDL_QUIT ) 
		 { 
			 //Quit the program 
			 main::game = false; 
		 } 

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

		if( (keys[SDLK_RETURN]) && (gamestate == STATE_LOGO) )
			CGame::SetGameState(STATE_TITLE);

		 if( keys[SDLK_UP] )
			CMusic::PlaySong("Ayla", true, false);

		 if( keys[SDLK_DOWN] )
		 {
			AirHornOn();
			CMusic::PlaySong("Airhorn", false, false);
		 }
	 }
}

CGame::~CGame(void)
{
}

int CGame::IntRand()
{
	//The Seed is really terrible
	srand(time(NULL));
	return rand()%255;
}

void CGame::SetGameState(int state)
{
	//TODO: Time for some Hardcoded Drama
	if (state == STATE_TITLE)
		CMusic::PlaySong("Title", true, false);

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

	//TODO: SDL_Surfaces that create themselves.
	title_logo = CGameLogic::load_image("Title");
	airhorn_off = CGameLogic::load_image("AirhornOff");
	airhorn = CGameLogic::load_image("Airhorn");
	logo1 = CGameLogic::load_image("Logo1");
	logo2 = CGameLogic::load_image("Logo2");

	if ((!airhorn_off) || (!airhorn) || (!title_logo) || (!logo1) || (!logo2))
		return 0;

	return 1;
}

int CGame::FreeImages()
{
	SDL_FreeSurface(title_logo);
	SDL_FreeSurface(airhorn_off);
	SDL_FreeSurface(airhorn);
	return 1;
}

void CGame::Render()
{
	if (gamestate == STATE_LOGO)
	{
		CGame::DrawLogos();
	}
	if (gamestate == STATE_TITLE)
	{
		//Draw the airhorn
		CGameLogic::Draw( 0, 0, airhorn_off, CGameLogic::screen );

		CGameLogic::Draw(CGameLogic::ScreenWidth/2, CGameLogic::ScreenHeight/2, title_logo, CGameLogic::screen );
	}
	RegulateFrameRate();
}

void CGame::DrawLogos()
{
	//TODO: Fade in between and such
		SDL_FillRect(CGameLogic::screen,NULL, SDL_MapRGB(SDL_GetVideoSurface()->format,0xFF,0xFF,0xFF)); 

		if (logoframe < 240)		
		CGameLogic::Draw( (CGameLogic::ScreenWidth/2)-(logo1->w/2), (CGameLogic::ScreenHeight/2)-(logo1->h/2), logo1, CGameLogic::screen );
		else if (logoframe < 480)
		CGameLogic::Draw( (CGameLogic::ScreenWidth/2)-(logo2->w/2), (CGameLogic::ScreenHeight/2)-(logo2->h/2), logo2, CGameLogic::screen );
		else if (logoframe > 480)
		SetGameState(STATE_TITLE);

		logoframe++;
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