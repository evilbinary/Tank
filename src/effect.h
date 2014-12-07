/*
 * effect.h
 *
 *  Created on: Sep 8, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#ifndef EFFECT_H_
#define EFFECT_H_
#include <SDL/SDL.h>
#include "warfield.h"
#include <iostream>

using namespace std;
namespace tank {

class Effect {
private:
	int x, y, life,type,step,maxlife;
	int alpha;
	SDL_Rect rect;
	SDL_Surface *surface;
	WarField* field;
public:
	Effect();
	void SetField(WarField * field);
	void SetSurface(SDL_Surface *surface);
	void SetPos(int x, int y);
	void TankBomb();
	void BulletBomb();
	void BulletHit();
	void Draw();
	void SetType(int type);
	int GetLife();
	void SetLife(int life);
	void SetMaxLife(int maxlife);
	int GetMaxLife();
	void BulletBombSound();
	void TankBombSound();
	void ShootSound();

};
}

#endif /* EFFECT_H_ */
