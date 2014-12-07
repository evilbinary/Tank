/*
 * map.h
 *
 *  Created on: Oct 3, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#ifndef MAP_H_
#define MAP_H_
#include "resource.h"
#include "warfield.h"
#include "object.h"
#include <SDL/SDL.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <list>

namespace tank {

class Map {
private:
	ResourceManager *resourceManger;
	list<Object> * objects;
	WarField *field;
	SDL_Surface *screen;
	xmlDocPtr doc;
	xmlNodePtr curNode;
	xmlChar * temp;

public:
	Map();
	Map(ResourceManager *resourceManger,WarField * field, list<Object> *objects,SDL_Surface *screen);
	void SetResourceManager(ResourceManager *resourceManger);
	void ParseMap(string name);
	void ParseResource(string name);
	void AddNode(string fileName,xmlNodePtr node);
	void DeleteNode(string fileName,xmlNodePtr node);
	void AddNodeList(string fileName,list<xmlNodePtr> *nodes);
	void SaveObject(string fileName);
};
}
#endif /* MAP_H_ */
