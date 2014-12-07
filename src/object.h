/*
 * object.h
 *
 *  Created on: Sep 15, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#ifndef OBJECT_H_
#define OBJECT_H_
#include <SDL/SDL.h>
#include "warfield.h"
#include "effect.h"
#include <iostream>
using namespace std;

namespace tank {

class Object {
private:
	int id, type, x, y, step, direct, life;
	SDL_Surface *surface;
	SDL_Rect object;
	Uint32 color;
	WarField* field;
	SDL_Rect clip[8];
	int frame;
	int alpha;
	string name;

public:
	Object();
	void SetField(WarField * field);
	void SetSurface(SDL_Surface *surface);
	void Move(int x, int y);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
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
	SDL_Rect GetRect();
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
	void SetRect(int x,int y,int w,int h);
	void SetRect(SDL_Rect rect);
	void SetSize(int w,int h);
	void SetPos(int x,int y);
	string GetName();
};

}

#endif /* OBJECT_H_ */
