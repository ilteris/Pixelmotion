/*
 *  Line.cpp
 *  getEdgeVideo2
 *
 *  Created by ilteris kaplan on 11/11/06.
 *  Copyright 2006 ilteris kaplan. All rights reserved.
 *
 */

#include "MyLine.h"
#include <iostream>

MyLine::MyLine() {
	xCurrent = 500; // need to figure out a way to get width value from GWorld
	yCurrent = 500;
	
	xOld	 = xCurrent;
	yOld	 = yCurrent;
	
}


void MyLine::run() {
	update();
	render();
}

void MyLine::render() {
	
}


bool MyLine::dead() {
	if(timer < 0.0 ) {
		return true;
	} else {
		return false;
	}
	
}
	

void MyLine::update() {
	
}
void MyLine::drawLine() {

	double x  =  ourRandom(0,10);
	double y  =  ourRandom(0,10);
	 ourRect(xCurrent-x,yCurrent-x, xCurrent+x,yCurrent+x);
	}


double MyLine::ourRandom(  float min,  float max ){
	return( (Random()+32768) /((32768*2)/ (max-min)))+ min;
}


void MyLine::ourRect(int left,int top,int right ,int bottom){						
	Rect theRect;												
	long temp;
	if (left > right) {temp = left; left = right ; right = temp;}		
	if (top > bottom) {temp = top; top = bottom ; bottom = temp;}		
	SetRect(&theRect,left,top,right,bottom);							
	FrameRect(&theRect);
	//FrameOval(&theRect);												
}