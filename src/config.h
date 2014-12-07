/*
 * config.h
 *
 *  Created on: Sep 17, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include <iostream>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include "resource.h"
#include "object.h"
#include <list>
#include <stdio.h>
#include <libxml/xmlreader.h>

using namespace std;

namespace tank{

void print_xml_file(string xmlFileName);

class Config {
private:

public:
	Config();
	void Print();
	void PrintResource();
	void PrintMap();
	void PrintObject();
	void LoadResource(ResourceManager *resourceManger);
	void LoadMap(list<Object> * objects);
};

}

#endif /* CONFIG_H_ */
