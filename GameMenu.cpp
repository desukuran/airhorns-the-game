#include "GameMenu.h"
#include "SDL.h"

int CGameMenu::cursorIndex;
SDL_Surface *CGameMenu::curTex;
SDL_Surface *CGameMenu::menuTex;
std::string CGameMenu::choice[MENU_MAX];
int CGameMenu::currentMax;

CGameMenu::CGameMenu(std::string choices [], int choiceCount)
{
	curTex = CGameLogic::load_image("Cursor");
	menuTex = CGameLogic::load_image("Menu");
	int max;

	if (choiceCount-1 < MENU_MAX)
	{
		currentMax = choiceCount-1;
		max = choiceCount-1;
	}
	else
	{
		currentMax = MENU_MAX;
		max = MENU_MAX;
	}
	for (int i=0;i<max;i++)
		choice[i].swap(choices[i]);
}

CGameMenu::~CGameMenu(void)
{
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

		 if(keystate[SDLK_UP])
			 CGameMenu::CursorMove(CUR_UP);
		 else if (keystate[SDLK_DOWN])
			 CGameMenu::CursorMove(CUR_DOWN);
}

void CGameMenu::CursorMove(int direction)
{
	CSound::PlaySound("Cursor", false);
	if (direction == CUR_UP)
		cursorIndex -= 1;
	else if (direction == CUR_DOWN)
		cursorIndex += 1;

	if (cursorIndex < 0)
		cursorIndex = currentMax;
	else if (cursorIndex > currentMax)
		cursorIndex = 0;
}

int CGameMenu::menuDecision()
{
	return cursorIndex;
}