/*
 * bullet.h
 *
 *  Created on: Aug 27, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#ifndef BULLET_H_
#define BULLET_H_
#include <SDL/SDL.h>
#include "warfield.h"
#include <list>
#include <iostream>

using namespace std;

namespace tank {



class Bullet {
private:
	int id,x, y, direct, step, type, life;
	Uint32 color;
	SDL_Rect bullet;
	SDL_Surface *surface;
	WarField* field;
	SDL_Rect clip[8];
	string name;
	int alpha;

public:
	Bullet();
	void SetField(WarField * field);
	void SetSurface(SDL_Surface *surface);
	void SetRect(SDL_Rect rect);
	void SetDirect(int direct);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void Draw();
	void Bomb();
	void Damage(int deep);
	void SetPos(int x, int y);
	void ReduceLife(int id, int num);
	void SetId(int id);
	int GetId();
	void SetSpeed(int speed);
	int GetLife();
	void SetColor(Uint32 color);
	int GetStep();
};
}

#endif /* BULLET_H_ */
