/*
 *  ParticleSystem.h
 *  getEdgeVideo4
 *
 *  Created by ilteris kaplan on 11/14/06.
 *  Copyright 2006 ilteris kaplan. All rights reserved.
 *
 */

#include <Carbon/Carbon.h>
#include <list>
#include "MyLine.h"


class ParticleSystem {
public:
	//std::list<MyLine> particles;
	//std::list<MyLine>::iterator p;
	// long x, y; // x and y coordinate of the origin of the particle.
	int num;
	ParticleSystem(long x, long y, int num);
	//void addParticle(long x, long y);
	//void run();
	//bool dead();
private:
	
	
	
};