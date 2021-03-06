//============================================================================
// Name        : Tank.cpp
// Author      : EvilBinary
// Version     :
// Copyright   : 嘎嘎,小E
// Description : Hello World in C++, Ansi-style
//  Copyright (c) 2014 evilbinary.org. All rights reserved.
//     rootntsd@gmail.com
//
//============================================================================

#include "tank.h"
#include <stdio.h>
#include <iostream>
#include "game.h"

using namespace std;

namespace tank {

Tank::Tank() {
	step = 8;
	this->x = 0;
	this->y = 0;
	this->tank.h = 46;
	this->tank.w = 46;
	//	this->tank.h = 32;
	//	this->tank.w = 32;
	//	this->tank.h = 16;
	//	this->tank.w = 16;
	this->tank.x = 0;
	this->tank.y = 0;
	this->color = 0x0000ff;
	this->field = NULL;
	this->name = "tank01";
	for (int i = 0; i < 8; i++) {
		this->clip[i].h = 63;
		this->clip[i].w = 63;
		this->clip[i].x = i * 64;
		this->clip[i].y = 0;
	}
	bullets = NULL;
	frame = 0;
	direct = 0;//
	life = 100;
}

void Tank::SetSurface(SDL_Surface * surface) {
	this->surface = surface;

}
void Tank::MoveLeft() {
	SDL_Rect t = tank;
	int count = 0;
	int x = tank.x / MAPSIZE;
	int y = tank.y / MAPSIZE;
	if ((tank.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((tank.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	x--;
	int h = tank.h / MAPSIZE + y;

	for (int j = y; j < h; j++) {
		if (field->GetMapType(x, j) > 3)
			count++;
	}

	if (count == 0) {

		tank.x -= step;

	} else {
		//		cout << "left:" << count << endl;
	}
	field->FillCell(t, 0);
	field->FillCell(tank, type);
	direct = 4;
}
void Tank::MoveRight() {
	SDL_Rect t = tank;

	int count = 0;
	int x = tank.x / MAPSIZE;
	int y = tank.y / MAPSIZE;
	if ((tank.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((tank.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	x++;
	int h = tank.h / MAPSIZE + y;
	int w = tank.w / MAPSIZE + x;
	for (int j = y; j < h; j++) {
		if (field->GetMapType(w, j) > 3)
			count++;
	}

	if (count == 0) {
		tank.x += step;

	} else {
		//		cout << "right:" << count << endl;
	}
	field->FillCell(t, 0);
	field->FillCell(tank, type);
	direct = 0;
}
void Tank::MoveUp() {

	SDL_Rect t = tank;

	int count = 0;
	int x = tank.x / MAPSIZE;
	int y = tank.y / MAPSIZE;
	if ((tank.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((tank.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	y--;
	int w = tank.w / MAPSIZE + x;
	for (int i = x; i < w; i++) {
		//cout << "[" << y << "," << i << "]=" << field->GetMapType(i, y) << endl;
		if (field->GetMapType(i, y) > 3)
			count++;
	}

	if (count == 0) {
		tank.y -= step;

	} else {
		//		cout << "up:" << count << endl;
	}
	field->FillCell(t, 0);
	field->FillCell(tank, type);

	direct = 2;
}
void Tank::MoveDown() {
	SDL_Rect t = tank;

	int count = 0;
	int x = tank.x / MAPSIZE;
	int y = tank.y / MAPSIZE;
	if ((tank.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((tank.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	//y++;
	int w = tank.w / MAPSIZE + x;
	int h = tank.h / MAPSIZE + y;

	for (int i = x; i < w; i++) {
		//		cout << "[" << h << "," << i << "]=" << field->GetMapType(i, h) << endl;

		if (field->GetMapType(i, h) > 3)
			count++;
	}

	if (count == 0) {
		tank.y += step;

	} else {
		//		cout << "down:" << count << endl;
	}
	field->FillCell(t, 0);
	field->FillCell(tank, type);
	direct = 6;
}

void Tank::Draw() {
	if (life <= 0 && step == 0) {

		return;
	}

	if (this->field != NULL) {
		ResourceManager * resourceManager = this->field->GetResourceManager();
		if (resourceManager != NULL) {
			SDL_Surface * res = NULL;

			res = resourceManager->GetResourceSurfaceByName(name);

			if (res != NULL) {
				//SDL_FillRect(this->surface,&this->tank,color);
				SDL_SetColorKey(res, SDL_SRCCOLORKEY, 0xffffff);
				SDL_SetAlpha(res, SDL_SRCALPHA, this->alpha);

				apply_surface(tank.x - 7, tank.y - 14, res, surface,
						&clip[direct]);
				Bomb();
			} else {
				cout << "Resource tank is null." << endl;
			}

		}
	} else {
		cout << "Filed is null." << endl;
	}
}
void Tank::DrawRect() {
	if (life <= 0 && step == 0) {

		return;
	}
	Bomb();
	//	for(int k=0;k<100;k++){
	//		put_pixel(this->surface,k, 100, 0x000000ff);
	//	}
	//put_line(surface,10,00,10,200,0xff0000);

	put_line(this->surface, tank.x, tank.y, tank.x + tank.w, tank.y,
			this->color);
	put_line(this->surface, tank.x + tank.w, tank.y, tank.x + tank.w, tank.y
			+ tank.h, this->color);
	put_line(this->surface, tank.x, tank.y, tank.x, tank.y + tank.h,
			this->color);
	put_line(this->surface, tank.x, tank.y + tank.h, tank.x + tank.w, tank.y
			+ tank.h, this->color);
	//	this->field->FillCell(this->tank);

	if (SDL_MUSTLOCK(surface)) {
		SDL_UnlockSurface(surface);
	}

}

//void Tank::SetResourceManager(ResourceManager* resManager) {
//	this->resourceManager = resManager;
//}
void Tank::SetField(WarField *field) {
	this->field = field;
}
void Tank::PrintPos() {
	cout << "[" << x << "," << y << "]" << endl;
}
void Tank::RandPos() {
	this->tank.x = rand() % 800;
	this->tank.y = rand() % 600;
}
void Tank::RandShoot() {
	int r = rand() % 20;
	if (r == 0) {
		this->Shoot();
	}
}
int Tank::GetId() {
	return this->id;
}
void Tank::SetId(int id) {
	this->id = id;

}
int Tank::GetLife() {
	return this->life;
}
int Tank::GetStep() {
	return this->step;
}
void Tank::RandRun() {
	int direct = rand() % 8;
	frame = direct;
	switch (direct) {
	case 0:
		this->MoveRight();
		break;
	case 1:

		break;
	case 2:
		this->MoveUp();
		break;
	case 3:

		break;
	case 4:

		this->MoveLeft();
		break;
	case 5:

		break;
	case 6:
		this->MoveDown();
		break;
	case 7:

		break;

	default:

		break;
	}
}
void Tank::SetFrame(int frame) {
	this->frame = frame;
}
void Tank::Shoot() {
	if (life <= 0 && step == 0)
		return;
	if (bullets != NULL) {
		Bullet bullet;

		switch (direct) {
		case 0:
			//			this->MoveRight();
//			bullet.SetPos(tank.x + tank.w, tank.y + tank.h / 2 - MAPSIZEHALF); stander
			bullet.SetPos(tank.x + tank.w, tank.y + tank.h / 2 - MAPSIZE*2);
			break;
		case 1:

			break;
		case 2:
			//			this->MoveUp();
			bullet.SetPos(tank.x + tank.w / 2 , tank.y - 2
					* MAPSIZE);
			break;
		case 3:

			break;
		case 4:
			//			this->MoveLeft();
//			bullet.SetPos(tank.x - 2 * MAPSIZE, tank.y + tank.w / 2- MAPSIZEHALF); stander center
			bullet.SetPos(tank.x - 2 * MAPSIZE, tank.y + tank.w / 2- MAPSIZEHALF*4);
			break;
		case 5:

			break;
		case 6:
			//			this->MoveDown();
			bullet.SetPos(tank.x + tank.w / 2  , tank.y + tank.w);
			break;
		case 7:

			break;

		default:

			break;
		}
		bullet.SetId(this->id);
		bullet.SetDirect(this->direct);
		bullet.SetField(field);
		bullet.SetSurface(this->surface);
		bullets->push_back(bullet);

		Effect e;
		e.SetSurface(surface);
		e.SetField(field);
		e.SetType(4);
		e.SetMaxLife(1);
		e.ShootSound();

	} else {
		cout << "bullets is null." << endl;
	}
}
void Tank::Damage(int deep) {
	if (life > 0)
		this->life -= deep;
}
void Tank::Bomb() {
	if (life > -5 && life <= 0) {
		step = 0;
		Effect e;
		e.SetSurface(surface);
		e.SetField(field);
		e.SetType(0);
		e.SetMaxLife(20);
		//		cout<<"maxaa:"<<e.GetMaxLife()<<endl;
		e.SetPos(tank.x - 150 + tank.w / 2, tank.y - 150 + tank.h / 2);
		e.TankBombSound();
		Game::effects.push_back(e);
		this->type = 0;
		this->field->FillCell(this->tank, 0);
		life = -10;
	}
}
void Tank::SetAlpha(int alpha) {
	this->alpha = alpha;
}
int Tank::GetAlpha() {
	return this->alpha;
}
void Tank::SetName(string name) {
	this->name = name;
}
SDL_Rect Tank::GetRect() {
	return this->tank;
}

int Tank::GetType() {
	return this->type;
}
void Tank::SetType(int type) {
	this->type = type;
}
void Tank::SetLife(int life) {
	this->life = life;
}
void Tank::SetStep(int step) {
	this->step = step;
}
void Tank::SetBullets(list<Bullet> * bullets) {
	this->bullets = bullets;
}
void Tank::SetColor(Uint32 color) {
	this->color = color;
}

}
