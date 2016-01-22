#include "GameMenu.h"
#include "SDL/SDL.h"
#include "Timer.h"

Timer globalTime;

CGameMenu::~CGameMenu(void)
{
}

void CGameMenu::Create(std::string choices[], int choiceCount)
{
	curTex = CGameLogic::load_image("Cursor");
	menuTex = CGameLogic::load_image("Menu");
	int max;

	if (choiceCount < MENU_MAX)
	{
		currentMax = choiceCount;
		max = choiceCount;
	}
	else
	{
		currentMax = MENU_MAX;
		max = MENU_MAX;
	}
	for (int i=0;i<max;i++)
		choice[i].swap(choices[i]);
}

void CGameMenu::Draw()
{
	//Draw Menu Background
	CGameLogic::Draw((CGameLogic::ScreenWidth/2)-(menuTex->w/2), (CGameLogic::ScreenHeight)-(menuTex->h)-(menuTex->h/8), menuTex, CGameLogic::screen);

	//Draw Text
	for (int i=0;i<MENU_MAX;i++)
		CGameLogic::DrawText(CGameLogic::screen, choice[i], (CGameLogic::ScreenWidth/2)-(menuTex->w/2)+(menuTex->w/16), (CGameLogic::ScreenHeight)-(menuTex->h)-(menuTex->h/8)+(menuTex->h/16)+(i*32), 255,255,255, false);

	//Draw Cursor
	CGameLogic::Draw((CGameLogic::ScreenWidth/2)-(menuTex->w/2), (CGameLogic::ScreenHeight)-(menuTex->h)-(menuTex->h/8)+(menuTex->h/16)+(cursorIndex*32), curTex, CGameLogic::screen);
}

void CGameMenu::Think()
{
	Uint8 *keystate = SDL_GetKeyState(NULL);

	if (CGameMenu::nextMoveTime < globalTime.get_ticks())
	{
		 if(keystate[SDLK_UP])
			 CGameMenu::CursorMove(CUR_UP);
		 else if (keystate[SDLK_DOWN])
			 CGameMenu::CursorMove(CUR_DOWN);

		 CGameMenu::nextMoveTime = globalTime.get_ticks() + 1000;
	}
}

void CGameMenu::CursorMove(int direction)
{
	CSound::PlaySound("Cursor", false);
	if (direction == CUR_UP)
		cursorIndex -= 1;
	else if (direction == CUR_DOWN)
		cursorIndex += 1;

	if (cursorIndex < 0)
		cursorIndex = currentMax-1;
	else if (cursorIndex > currentMax-1)
		cursorIndex = 0;
}

int CGameMenu::menuDecision()
{
	return cursorIndex;
}
