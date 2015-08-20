#include "Player.h"
#include "GameLogic.h"
#include "DebugMessage.h"

CPlayer::CPlayer(void)
{
	Spawn();
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::Spawn(void)
{
	playerx = CGameLogic::ScreenWidth/2;
	playery = CGameLogic::ScreenHeight/2;
}

void CPlayer::ProcessInput()
{
		//printf("\nProcessInput\n");

        //Get the keystates
        Uint8 *keystates = SDL_GetKeyState( NULL );

		if(keystates[ SDLK_UP ])
				movingUp = true;
		else
				movingUp = false;

		if(keystates[ SDLK_DOWN ])
				movingDown = true;
		else
				movingDown = false;

		if(keystates[ SDLK_LEFT ])
				movingLeft = true;
		else
				movingLeft = false;

		if(keystates[ SDLK_RIGHT ])
				movingRight = true;
		else
				movingRight = false;


}

void CPlayer::Think()
{
	ProcessInput();
	//CDebugMessage::AddMessage("DEBUG: THINK");
	
	if (movingUp)
		playery -= 1;
	if (movingDown)
		playery += 1;
	if (movingLeft)
		playerx -= 1;
	if (movingRight)
		playerx += 1;
}

void CPlayer::Draw(void)
{
	CGameLogic::Draw( playerx, playery, CPlayer::player_sprite, CGameLogic::screen );
}