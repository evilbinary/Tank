/*
 * game.h
 *
 *  Created on: Aug 27, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#ifndef GAME_H_
#define GAME_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include <list>
#include "warfield.h"
#include "tank.h"
#include "bullet.h"
#include "phys.h"
#include "resource.h"
#include <time.h>
#include "effect.h"
#include "object.h"
#include "config.h"
#include "map.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700
#define SCREEN_BPP 32

using namespace std;

namespace tank {

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination,
		SDL_Rect* clip);
SDL_Surface *load_image(string filename);
void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void put_line(SDL_Surface *surface, int x, int y,int ex,int ey, Uint32 pixel);
Uint32 get_pixel(SDL_Surface *surface, int x, int y);
double calFrequency();

list<Tank> * GetTanks();

class Game {
private:
	static SDL_Thread *thread;
	static SDL_Surface *background;
	static SDL_Surface *front;
	static SDL_Surface *screen;
	static SDL_Event event;
	TTF_Font * font;
	static bool quit;
	int alpha;
	SDL_Color textColor ;
	Mix_Music *music;
	Mix_Chunk *chunk;
	int tankdeadnum;
	int bulletdeadnum;
	int bombnum;
	int direct;
	int shoot;
	double fps;
	int keycount;
	int candraw;
	int lpress;
	Map *map;
	int objnum;
	int screenwidth;
	int screenheight;
public:
	static list<WarField> warfields;
	static list<Tank> tanks;
	static list<Bullet> bullets;
	static Phys phys;
	static ResourceManager resourceManager;
	static list<Effect> effects;
	static list<Object> objects;

	Game();
	void Init();
	void Start();
	void Loop();
	void Exit();
	void HandleInput();
	void Render();
	void Logic();
	void ShowState();
	void Test(SDL_Rect & r);
};

}

#endif /* GAME_H_ */
