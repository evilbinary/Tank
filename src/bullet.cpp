/*
 * bullet.cpp
 *
 *  Created on: Aug 27, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#include "bullet.h"
#include "tank.h"
#include "game.h"

namespace tank {

Bullet::Bullet() {
	type = 7;
	bullet.h = 10;
	bullet.w = 10;
	bullet.x = 0;
	bullet.y = 0;
	step = 12;
	life = 2;
	name = "bullet01";

	for (int i = 0; i < 8; i++) {
		this->clip[i].h = 63;
		this->clip[i].w = 63;
		this->clip[i].x = i * 64;
		this->clip[i].y = 0;
	}

}

void Bullet::Draw() {

	if (life <= 0 && step == 0) {

		return;
	}


	//		field->FillCell(bullet);
	//	cout<<direct<<endl;
	if (life <= 0 && step == 0)
		return;
	switch (direct) {
	case 0:
		this->MoveRight();
		x= bullet.x-60;
		y=bullet.y-20;
		break;
	case 1:

		break;
	case 2:
		this->MoveUp();
		x= bullet.x-30;
				y=bullet.y+10;
		break;
	case 3:

		break;
	case 4:

		this->MoveLeft();
		x= bullet.x+10;
				y=bullet.y-20;
		break;
	case 5:

		break;
	case 6:
		this->MoveDown();
		x= bullet.x-30;
		y=bullet.y-60;
		break;
	case 7:

		break;

	default:

		break;
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

				apply_surface(x, y, res, surface,
						&clip[direct]);
				Bomb();
			} else {
				cout << "Resource bullet is null." << endl;
			}

		}
	} else {
		cout << "Filed is null." << endl;
	}

	if (bullet.x < -10 || bullet.y < -10 || bullet.x > MAPCOL * MAPSIZE
			|| bullet.y > MAPROW * MAPSIZE) {
		life = 0;
		Bomb();
	}

}
int Bullet::GetStep() {
	return this->step;
}
void Bullet::Damage(int deep) {
	if (life > 0)
		life -= deep;
}
void Bullet::Bomb() {
	if (life <= 0) {
		this->step = 0;
		this->type = 0;

		Effect e;
		e.SetSurface(surface);
		e.SetField(field);
		e.SetType(1);
		e.SetMaxLife(6);
		e.SetPos(bullet.x - 32 + this->bullet.w / 2, bullet.y - 32 + bullet.h
				/ 2);
		e.BulletBombSound();
		Game::effects.push_back(e);

		this->field->FillCell(bullet, 0);
		life = -10;

	}
}
void Bullet::SetRect(SDL_Rect rect) {
	this->bullet = rect;
}
void Bullet::SetField(WarField *field) {
	this->field = field;
}
void Bullet::SetSurface(SDL_Surface * surface) {
	this->surface = surface;
}
void Bullet::SetDirect(int direct) {
	this->direct = direct;
}
int Bullet::GetLife() {
	return this->life;
}

void Bullet::MoveLeft() {
	field->FillCell(bullet, 0);
	int count = 0;
	int x = bullet.x / MAPSIZE;
	int y = bullet.y / MAPSIZE;
	if ((bullet.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((bullet.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	x--;
	int h = bullet.h / MAPSIZE + y;
	int left = -1;
	for (int j = y; j < h; j++) {
		left = field->GetMapType(x, j);
		if (left > 3)
			count++;
	}

	if (count == 0) {
		bullet.x -= step;

	} else {
		//		cout << "left:" << count << endl;
		//cout<<left<<endl;
		Damage(2);
		this->Bomb();
		this->ReduceLife(left, 10);

	}
	field->FillCell(bullet, type);
	direct = 4;
}
void Bullet::ReduceLife(int id, int num) {
	//	cout<<"id:"<<id<<" num:"<<num<<endl;
	list<Tank>::iterator tank;
	for (tank = Game::tanks.begin(); tank != Game::tanks.end(); tank++) {
		if (tank->GetId() == id) {
			tank->Damage(num);
			//cout<<"tank"<<id<<" life:"<<tank->GetLife()<<endl;
		}
	}
}

void Bullet::MoveRight() {
	field->FillCell(bullet, 0);
	int count = 0;
	int x = bullet.x / MAPSIZE;
	int y = bullet.y / MAPSIZE;
	if ((bullet.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((bullet.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	x++;
	int h = bullet.h / MAPSIZE + y;
	int w = bullet.w / MAPSIZE + x;
	int right = -1;
	for (int j = y; j < h; j++) {
		right = field->GetMapType(w, j);
		if (right > 3)
			count++;
	}

	if (count == 0) {
		bullet.x += step;

	} else {
		//		cout << "right:" << count << endl;
		Damage(2);
		this->Bomb();
		this->ReduceLife(right, 10);
	}
	field->FillCell(bullet, type);
	direct = 0;
}
void Bullet::MoveUp() {
	field->FillCell(bullet, 0);
	int count = 0;
	int x = bullet.x / MAPSIZE;
	int y = bullet.y / MAPSIZE;
	if ((bullet.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((bullet.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	y--;
	int w = bullet.w / MAPSIZE + x;
	int up = -1;
	for (int i = x; i < w; i++) {
		//cout << "[" << y << "," << i << "]=" << field->GetMapType(i, y) << endl;
		up = field->GetMapType(i, y);
		if (up > 3)
			count++;
	}

	if (count == 0) {
		bullet.y -= step;

	} else {
		//		cout << "up:" << count << endl;
		Damage(2);
		this->Bomb();
		this->ReduceLife(up, 10);
	}
	field->FillCell(bullet, type);
	direct = 2;
}
void Bullet::MoveDown() {
	field->FillCell(bullet, 0);
	int count = 0;
	int x = bullet.x / MAPSIZE;
	int y = bullet.y / MAPSIZE;
	if ((bullet.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((bullet.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	//y++;
	int w = bullet.w / MAPSIZE + x;
	int h = bullet.h / MAPSIZE + y;
	int down = -1;
	for (int i = x; i < w; i++) {
		//		cout << "[" << h << "," << i << "]=" << field->GetMapType(i, h) << endl;
		down = field->GetMapType(i, h);
		if (down > 3)
			count++;
	}

	if (count == 0) {
		bullet.y += step;

	} else {
		//		cout << "down:" << count << endl;
		Damage(2);
		this->Bomb();
		this->ReduceLife(down, 10);
	}

	field->FillCell(bullet, type);
	direct = 6;
}
void Bullet::SetPos(int x, int y) {
	bullet.x = x;
	bullet.y = y;
}
void Bullet::SetId(int id) {
	this->id = id;
}
void Bullet::SetSpeed(int speed) {
	this->step = speed;
}
int Bullet::GetId() {
	return this->id;
}
void Bullet::SetColor(Uint32 color) {
	this->color = color;
}
}
