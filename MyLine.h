/*
 *  Line.h
 *  getEdgeVideo2
 *
 *  Created by ilteris kaplan on 11/11/06.
 *  Copyright 2006 ilteris kaplan. All rights reserved.
 *
 */

#ifndef _MyLine
#define _MyLine
class MyLine {
public:
	MyLine();
	void drawLine();
	double ourRandom(float,float);
	void ourRect(int,int,int,int);
	void run();
	void update();
	void render();
	bool dead();
	
	float xDest, yDest;
	float xCurrent, yCurrent;
	float xOld, yOld;
	float damper;
	float timer;
	
	
private:
		
		
	float xvel;
	float yvel;
	
	
};


#endif