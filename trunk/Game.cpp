#include "Game.h"
#include "GameLogic.h"
#include "main.h"
#include "Music.h"

#include <ctime>

	int keyz[10] = { SDLK_UP,SDLK_UP,SDLK_DOWN,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT,SDLK_LEFT,SDLK_RIGHT,SDLK_b,SDLK_a };
	int keyzl = 10;
	int konamiindex = 0;
	int konami = 0;

int main::game;

// Gain access to keystate array
   Uint8 *keys = SDL_GetKeyState(NULL);

   SDL_Surface *CGame::airhorn;
	SDL_Surface *CGame::airhorn_off;

CGame::CGame(void)
{	
	 while( SDL_PollEvent( &GameEvent ) ) 
	 {
		CGameLogic::Draw( 0, 0, airhorn_off, CGameLogic::screen );
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

		 if( keys[SDLK_UP] )
			CMusic::PlaySong("Title", true, false);

		 if( keys[SDLK_DOWN] )
		 {
			AirHornOn();
			CMusic::PlaySong("Airhorn", false, false);
		 }
			flip();
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

int CGame::LoadAirhorns()
{
	airhorn_off = CGameLogic::load_image("img/airhorn0.png");
	airhorn = CGameLogic::load_image("img/airhorn1.png");

	if ((!airhorn_off) || (!airhorn))
		return 0;

	return 1;
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