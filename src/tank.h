/*
 * tank.h
 *
 *  Created on: Aug 27, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#ifndef TANK_H_
#define TANK_H_


#include <SDL/SDL.h>
#include <list>
#include "resource.h"
#include "warfield.h"
#include "bullet.h"
#include "effect.h"

namespace tank {

extern void apply_surface(int x,int y,SDL_Surface* source,SDL_Surface* destination,SDL_Rect* clip);
extern void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
extern void put_line(SDL_Surface *surface, int x, int y,int ex,int ey, Uint32 pixel);

class Tank {
private:
	int id,type,x, y,step,direct,life;
	SDL_Surface *surface;
	SDL_Rect tank;
	Uint32 color;
//	ResourceManager * resourceManager;
	WarField* field;
	SDL_Rect clip[8];
	int frame;
	int alpha;
	string name;
	list<Bullet > * bullets;

public:
	Tank();
//	void SetResourceManager(ResourceManager* resourceManager);
	void SetField(WarField * field);
	void SetSurface(SDL_Surface *surface);
	void Move(int x, int y);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void Shoot();
	void PrintPos();
	void Draw();
	void DrawRect();
	void RandPos();
	void RandRun();
	void SetAlpha(int alpha);
	int GetAlpha();
	void SetName(string name);

	int GetType();
	void SetType(int type);
	void SetBullets(list<Bullet > * bullets);
	SDL_Rect  GetRect();
	void RandShoot();
	void Damage(int deep);
	void Bomb();
	int GetId();
	void SetId(int id);
	int GetLife();
	void SetLife(int life);
	void SetStep(int step);
	void SetColor(Uint32 color);
	int GetStep();
	void SetFrame(int frame);
};

}

#endif /* TANK_H_ */
