/*
 * Object.cpp
 *
 *  Created on: Sep 15, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#include "object.h"
#include "game.h"

namespace tank {
Object::Object() {
	step = 8;
	this->x = 0;
	this->y = 0;
	this->object.h = 46;
	this->object.w = 46;
	//	this->tank.h = 32;
	//	this->tank.w = 32;
	//	this->tank.h = 16;
	//	this->tank.w = 16;
	this->object.x = 0;
	this->object.y = 0;
	this->color = 0x0000ff;
	this->field = NULL;
	this->name = "b";
	for (int i = 0; i < 8; i++) {
		this->clip[i].h = 63;
		this->clip[i].w = 63;
		this->clip[i].x = i * 64;
		this->clip[i].y = 0;
	}
	frame = 0;
	direct = 0;//
	life = 100;
	name="";

}

void Object::SetSurface(SDL_Surface * surface) {
	this->surface = surface;

}
void Object::SetPos(int x,int y){
	this->object.x=x;
	this->object.y=y;
}
string Object::GetName(){
	return this->name;
}
void Object::MoveLeft() {
	SDL_Rect t = object;
	int count = 0;
	int x = object.x / MAPSIZE;
	int y = object.y / MAPSIZE;
	if ((object.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((object.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	x--;
	int h = object.h / MAPSIZE + y;

	for (int j = y; j < h; j++) {
		if (field->GetMapType(x, j) > 3)
			count++;
	}

	if (count == 0) {

		object.x -= step;

	} else {
		//		cout << "left:" << count << endl;
	}
	field->FillCell(t, 0);
	field->FillCell(object, type);
	direct = 4;
}
void Object::MoveRight() {
	SDL_Rect t = object;

	int count = 0;
	int x = object.x / MAPSIZE;
	int y = object.y / MAPSIZE;
	if ((object.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((object.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	x++;
	int h = object.h / MAPSIZE + y;
	int w = object.w / MAPSIZE + x;
	for (int j = y; j < h; j++) {
		if (field->GetMapType(w, j) > 3)
			count++;
	}

	if (count == 0) {
		object.x += step;

	} else {
		//		cout << "right:" << count << endl;
	}
	field->FillCell(t, 0);
	field->FillCell(object, type);
	direct = 0;
}
void Object::MoveUp() {

	SDL_Rect t = object;

	int count = 0;
	int x = object.x / MAPSIZE;
	int y = object.y / MAPSIZE;
	if ((object.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((object.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	y--;
	int w = object.w / MAPSIZE + x;
	for (int i = x; i < w; i++) {
		//cout << "[" << y << "," << i << "]=" << field->GetMapType(i, y) << endl;
		if (field->GetMapType(i, y) > 3)
			count++;
	}

	if (count == 0) {
		object.y -= step;

	} else {
		//		cout << "up:" << count << endl;
	}
	field->FillCell(t, 0);
	field->FillCell(object, type);

	direct = 2;
}
void Object::MoveDown() {
	SDL_Rect t = object;

	int count = 0;
	int x = object.x / MAPSIZE;
	int y = object.y / MAPSIZE;
	if ((object.x - x * MAPSIZE) >= MAPSIZEHALF) {
		x++;
	}
	if ((object.y - y * MAPSIZE) >= MAPSIZEHALF) {
		y++;
	}
	//y++;
	int w = object.w / MAPSIZE + x;
	int h = object.h / MAPSIZE + y;

	for (int i = x; i < w; i++) {
		//		cout << "[" << h << "," << i << "]=" << field->GetMapType(i, h) << endl;

		if (field->GetMapType(i, h) > 3)
			count++;
	}

	if (count == 0) {
		object.y += step;

	} else {
		//		cout << "down:" << count << endl;
	}
	field->FillCell(t, 0);
	field->FillCell(object, type);
	direct = 6;
}

void Object::Draw() {
	if (life <= 0 && step == 0) {

		return;
	}

	if (this->field != NULL) {
		ResourceManager * resourceManager = this->field->GetResourceManager();
		if (resourceManager != NULL) {
			SDL_Surface * res = NULL;
//			cout<<"Object "<<name<<endl;
			res = resourceManager->GetResourceSurfaceByName(name);
			if (res != NULL) {
				//SDL_FillRect(this->surface,&this->object,color);
				SDL_SetColorKey(res, SDL_SRCCOLORKEY, 0xffffff);
				SDL_SetAlpha(res, SDL_SRCALPHA, this->alpha);

				apply_surface(object.x  , object.y , res, surface,
						&clip[direct]);
				field->FillCell(object, type);
				Bomb();
			} else {
				cout << "Resource is null." << endl;
			}

		}
	} else {
		cout << "Filed is null." << endl;
	}

}
void Object::DrawRect() {
	if (life <= 0 && step == 0) {

		return;
	}
	Bomb();
	//	for(int k=0;k<100;k++){
	//		put_pixel(this->surface,k, 100, 0x000000ff);
	//	}
	//put_line(surface,10,00,10,200,0xff0000);

	put_line(this->surface, object.x, object.y, object.x + object.w, object.y,
			this->color);
	put_line(this->surface, object.x + object.w, object.y, object.x + object.w,
			object.y + object.h, this->color);
	put_line(this->surface, object.x, object.y, object.x, object.y + object.h,
			this->color);
	put_line(this->surface, object.x, object.y + object.h, object.x + object.w,
			object.y + object.h, this->color);
	//	this->field->FillCell(this->object);

	if (SDL_MUSTLOCK(surface)) {
		SDL_UnlockSurface(surface);
	}

}

//void Object::SetResourceManager(ResourceManager* resManager) {
//	this->resourceManager = resManager;
//}
void Object::SetField(WarField *field) {
	this->field = field;
}
void Object::PrintPos() {
	cout << "[" << object.x << "," << object.y << "]" << endl;
}
void Object::RandPos() {
	this->object.x = rand() % 800;
	this->object.y = rand() % 600;
}
void Object::SetRect(int x,int y,int w,int h){
	this->object.x=x;
	object.y=y;
	object.w=w;
	object.h=h;
}void Object::SetRect(SDL_Rect rect){
	object=rect;
}

int Object::GetId() {
	return this->id;
}
void Object::SetId(int id) {
	this->id = id;

}
int Object::GetLife() {
	return this->life;
}
int Object::GetStep() {
	return this->step;
}
void Object::SetSize(int w,int h){
	this->object.h=h;
	this->object.w=w;
}
void Object::RandRun() {
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
void Object::SetFrame(int frame) {
	this->frame = frame;
}

void Object::Damage(int deep) {
	if (life > 0)
		this->life -= deep;
}
void Object::Bomb() {
	if (life > -5 && life <= 0) {
		step = 0;
		Effect e;
		e.SetSurface(surface);
		e.SetField(field);
		e.SetType(0);
		e.SetMaxLife(20);
		//		cout<<"maxaa:"<<e.GetMaxLife()<<endl;
		e.SetPos(object.x - 150 + object.w / 2, object.y - 150 + object.h / 2);
		e.TankBombSound();
		Game::effects.push_back(e);
		this->type = 0;
		this->field->FillCell(this->object, 0);
		life = -10;
	}
}
void Object::SetAlpha(int alpha) {
	this->alpha = alpha;
}
int Object::GetAlpha() {
	return this->alpha;
}
void Object::SetName(string name) {
	this->name = name;
}
SDL_Rect Object::GetRect() {
	return this->object;
}

int Object::GetType() {
	return this->type;
}
void Object::SetType(int type) {
	if (field != NULL) {
		field->FillCell(object, type);
	}
	this->type = type;
}
void Object::SetLife(int life) {
	this->life = life;
}
void Object::SetStep(int step) {
	this->step = step;
}

void Object::SetColor(Uint32 color) {
	this->color = color;
}

}
