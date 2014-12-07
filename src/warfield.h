/*
 * warfield.h
 *
 *  Created on: Aug 27, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#ifndef WARFIELD_H_
#define WARFIELD_H_

#include "resource.h"

#define MAPCOL 56*2
#define MAPROW 43*2
#define MAPSIZE 8
#define MAPSIZEHALF 4

namespace tank {

extern void apply_surface(int x, int y, SDL_Surface* source,
		SDL_Surface* destination, SDL_Rect* clip);
extern void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
extern void put_line(SDL_Surface *surface, int x, int y, int ex, int ey,
		Uint32 pixel);

class WarField {
private:
	ResourceManager * resourceManager;
	SDL_Surface *surface;
	int map[MAPROW][MAPCOL];

public:
	WarField();
	void Init();
	void LoadMap();
	void LoadTank();
	void Draw();
	void DrawRect();
	void DrawGrid();
	void ClearMap();
	void SetMap(int x,int y,int type);
	int GetMapType(int x,int y);
	void SetResourceManager(ResourceManager* resourceManager);
	ResourceManager* GetResourceManager();
	void SetSurface(SDL_Surface * surface);
	void FillCell(SDL_Rect rect);
	void FillCell(SDL_Rect rect,int type);
	void PrintMap();
};
}

#endif /* WARFIELD_H_ */
