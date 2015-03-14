/*
 * agent.cpp
 *
 *  Created on: Oct 9, 2011
 *      Author: cty
 *  Copyright (c) 2014 evilbinary.org. All rights reserved.
 *     rootntsd@gmail.com
 */

#include "agent.h"
#include "tank.h"
#include "game.h"
#include "warfield.h"
#include "map.h"
#include "resource.h"

using namespace tank;



Map * create_map(WarField *wf){
    Map *m=new Map(&Game::resourceManager, wf, &Game::objects,&Game::screen );
    return m;
}

WarField * create_warfiled(){
    WarField *w=new WarField();
    return w;
}

Tank* create_tank(){
    Tank* t=new Tank();
    return t; 
}

Tank *get_tank(){

}

