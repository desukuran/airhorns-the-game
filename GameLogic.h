#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Music.h"

enum { WIDTH, HEIGHT, BPP };

class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);
	static int DrawTitle(void);
	static int InitGame(void);
	static void CleanUp(void);

	static SDL_Surface *load_image(string filename);
	static void Draw(int x, int y, SDL_Surface* source, SDL_Surface* destination);
	static void DrawText(SDL_Surface* screen, string text, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center);
	static void DrawProgressiveText(SDL_Surface* screen, string text, Sint16 x, Sint16 y, Uint8 red, Uint8 green, Uint8 blue, bool center);
	static void DrawBackground(SDL_Surface* screen, Uint8 red, Uint8 Green, Uint8 blue);

	static void MessageBox(SDL_Surface* screen, string name, string msg);
	static void DrawMenu(int choices, string c1, string c2, string c3, string c4);

	static SDL_Surface* screen;
	static TTF_Font *font;

	static SDL_Surface* menu;
	static SDL_Surface* messagebox;

	//Variables
	int playing;
	static int ScreenHeight, ScreenWidth;
	static string message;
	
};
