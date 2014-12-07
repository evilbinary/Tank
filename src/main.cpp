/*
 * main.cpp
 *
 *  Created on: Aug 27, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#include <iostream>
#include "game.h"

using namespace tank;

int main(int argc, char* argv[]) {
	Game game;
	game.Init();
	game.Start();
	game.Loop();
	game.Exit();

	return 0;
}
