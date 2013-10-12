/*
 *  MyVideo.h
 *  getEdgeVideo
 *
 *  Created by ilteris kaplan on 11/9/06.
 *  Copyright 2006 ilteris kaplan. All rights reserved.
 *
 */

#include <quicktime/quicktimecomponents.h>
#include "MyLine.h"

class MyVideo {
public:
	GWorldPtr			videogworld;
	SeqGrabComponent	gSeqGrabber;
	SGChannel			gVideoChannel;
	
	
	
				
	MyVideo();
	void initVideo();
	void  seqGrabber();
	void draw(Rect, GWorldPtr, MyLine arr[],unsigned num_);
		
	int  ourRandom(  int min,  int max );
	void ourSetPixel(unsigned short horizontal,unsigned short vertical,unsigned char R,unsigned char G,unsigned char B,unsigned short rowbytes,Ptr pixbase);
	void ourGetPixel(unsigned short horizontal,unsigned short vertical,unsigned char* R,unsigned char* G,unsigned char* B,unsigned short rowbytes,Ptr pixbase);
	unsigned char GetEdge(unsigned short horizontal,unsigned short vertical,unsigned short rowbytes,Ptr pixbase);
	long clip(long,long,long);
	void drawToBuffer(Rect windRect_, GWorldPtr drawPort_, MyLine pixels[],const unsigned int numOfPixels_);
	void passXY(long x, long y, MyLine arr[],int i, unsigned int num_);
	void convolve(unsigned short horizontal,unsigned short vertical,unsigned char* R,unsigned char* G,unsigned char* B,int MatrixSize,double* Matrix,unsigned short rowbytes,Ptr pixbase);
	unsigned char threshold(unsigned short horizontal,unsigned short vertical,unsigned short rowbytes,Ptr pixbase);
		
	long sendX(long);
	long sendY(long);
private:
		double Matrix[121];
		long	prevX;
		long	prevY;
	
		long	curX;
		long	curY;
	
};