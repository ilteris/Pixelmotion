/*
 *  MyVideo.cpp
 *  getEdgeVideo
 *
 *  Created by ilteris kaplan on 11/9/06.
 *  Copyright 2006 ilteris kaplan. All rights reserved.
 *
 */

#include "MyVideo.h"
#include <Carbon/Carbon.h>
#include <quicktime/quicktimecomponents.h>
#include <iostream>


MyVideo::MyVideo() {
	double Matrix[121]={-1.0,-1.0,-1.0,-1.0,9.0,-1.0,-1.0,-1.0,-1.0};// sharpen
	prevX	= 0;
	prevY	= 0;
	curX	= 0;
	curY	= 0;
	
	// std::cout << "hello" << "\n";
}

void MyVideo::initVideo() {
	OSErr					error;
	ComponentDescription	theDesc;
	ComponentResult			theresult;
	Component				sgCompID;
	Rect					videoRect;
	
	SetRect(&videoRect,0,0,640,480);
	
	error =QTNewGWorld(&videogworld, 32, &videoRect, nil, nil,0 );
	if (error != noErr ) ExitToShell();	
	
	EnterMovies();
	gSeqGrabber		= 0L;
	gVideoChannel	= 0L;
	theDesc.componentType			= SeqGrabComponentType;
	theDesc.componentSubType		= 0L;
	theDesc.componentManufacturer	= 0L;
	theDesc.componentFlags			= 0L;
	theDesc.componentFlagsMask		= 0L;
	sgCompID						= FindNextComponent(nil,&theDesc);
	gSeqGrabber						= OpenComponent(sgCompID);
	SGInitialize(gSeqGrabber);
	SetRect(&videoRect, 0,0,640,480);
	QTNewGWorld(&videogworld, 32, &videoRect, nil, nil, 0);
	SGSetGWorld(gSeqGrabber, videogworld, nil);
	SGNewChannel(gSeqGrabber, 'vide', &gVideoChannel);
	SGSetChannelUsage(gVideoChannel, seqGrabPreview | seqGrabRecord | seqGrabPlayDuringRecord);
	//if (SGSetFrameRate(gVideoChannel,3) != noErr) SysBeep(10);	// these can sometimes help achieve a certain frame rate
	//SGSetChannelPlayFlags(gVideoChannel,channelPlayHighQuality);	// and certain quality.
	SGSetChannelBounds(gVideoChannel, &videoRect);				// tellling the channel about the size we want
	SGStartPreview(gSeqGrabber);								// start the video preview
	
}




void MyVideo::draw(Rect windRect, GWorldPtr drawPort_, MyLine pixels[], const unsigned int numofPixels_) {
	drawToBuffer(windRect, drawPort_,pixels,numofPixels_); 
	
}

int MyVideo::ourRandom(  int min,  int max ){										// method that returns a random number between min and max						
	return( (random()+32768) /((32768*2)/ (max-min)))+ min;
	
}


long MyVideo::clip(long val,long low,long high) {
	if(val<low) {
		val=low; 
	} else if(val>high) {
		val=high;
	}
	return val;
}  



void MyVideo::drawToBuffer(Rect windRect_, GWorldPtr drawPort_, MyLine pixels[],const unsigned int numOfPixels_)   												
{
	long x , y,temp,distance;
	Point mousepoint;
	unsigned short bufferRowBytes,imageRowBytes ;
	Ptr bufferBaseAddress,imageBaseAddress;
	PixMapHandle bufferPixmap, imagePixmap;
	unsigned char R,G,B;
	int MatrixSize;
	GetMouse(&mousepoint);			
	bufferPixmap=GetGWorldPixMap(drawPort_);
	bufferRowBytes  = ((*(bufferPixmap))->rowBytes) & 0x7fff;						
	bufferBaseAddress   = GetPixBaseAddr(bufferPixmap );								

	
	
	imagePixmap=GetGWorldPixMap(videogworld);									
	imageRowBytes  = ((*(imagePixmap))->rowBytes) & 0x7fff;						
	imageBaseAddress   = GetPixBaseAddr(imagePixmap );				
	
	SGIdle(gSeqGrabber);
	
	//CopyBits( GetPortBitMapForCopyBits( videogworld ), GetPortBitMapForCopyBits( drawPort_ ),
	//		  &windRect_, &windRect_, srcCopy, NULL );				
	
	// MatrixSize = 7;
	long difference;
	int i = 0;
	
	for(x=5;x<640; x += 4) {
		for(y=5;y<480;y += 4) {		
			
		//ourGetPixel(x,y,&R,&G,&B,imageRowBytes,imageBaseAddress);	
			//convolve(x,y,&R,&G,&B,MatrixSize,Matrix,imageRowBytes,imageBaseAddress);		// calling the Convolve() method using our matrix	
			//ourSetPixel(x,y,R,G,B,bufferRowBytes,bufferBaseAddress);	 	
		// difference = threshold(x,y,imageRowBytes,imageBaseAddress);	
			difference = GetEdge(x,y,imageRowBytes,imageBaseAddress);			
			// calling the GetEdge() method that calculates the difference in an area
			if (difference > 50)	{	
				
				//ourSetPixel(x,y,0,0,0,bufferRowBytes,bufferBaseAddress);
				
				int count = 0,j,k;
				for (j = -2;j<2;j++){
					for (k = -2;k<2;k++){
						//ourGetPixel(x+j,y+k,&R,&G,&B,videoRowBytes,videoBaseAddress);				
						// geting he color value of a pixel in our video buffer 
						difference = threshold(x+j,y+k,imageRowBytes,imageBaseAddress);			
						
						if (difference > 150) count++;
					
						
					}
				}
				// were counting how many pixels has changed, and if it is greater than 8 we say there is a change in the frame. 
				// looking at 9 neighbors gives us a good result. 
				
				if (count > 10){
					//std::cout << "x: " <<  x << "\n";
					//std::cout << "y: " <<  y << "\n";
					i++;
					 passXY(x,y, pixels, i, numOfPixels_);
					
					
					//ourSetPixel(x,y,0,0,0,bufferRowBytes,bufferBaseAddress);
					// we paint it to red. 
			
				}
				// if the difference is greater than 30 then we set the pixel black
				
			
					

				 
			
					//MyLine 	new Line burada yapilacak			
				// ourSetPixel(x,y,0,255,0,bufferRowBytes,bufferBaseAddress);		 				
			}	else	{
				// ourSetPixel(x,y,255,255,255,bufferRowBytes,bufferBaseAddress);	
			}											
		}																	
	}																																							
}


long MyVideo::sendX(long x) { 
	  return x ;
	
	}
long MyVideo::sendY(long y) {
	return y;
	
}

void MyVideo::seqGrabber() {
	SGIdle(gSeqGrabber);
}



void MyVideo::passXY(long x, long  y, MyLine arr[], int i, unsigned int num_) {
	const unsigned int num = num_-1;
	// std::cout << "i: " << i << "\n";
	
	
	prevX = curX;
	prevY = curY;
	
	curX  = x;
	curY  = y;
	
	
	
	if(i > num) {
	} else {
		arr[i].xCurrent = curX;
		arr[i].yCurrent = curY;
		arr[i].xOld		= prevX;
		arr[i].yOld		= prevY;
				
	}
}


void MyVideo::ourSetPixel(unsigned short horizontal,unsigned short vertical,unsigned char R,unsigned char G,unsigned char B,unsigned short rowbytes,Ptr pixbase){
	Ptr AdressOfRed;
	AdressOfRed = rowbytes * vertical +pixbase+horizontal*4+1;
	*(AdressOfRed)=R;
	*(AdressOfRed+1)=G;
	*(AdressOfRed+2)=B;
}

void MyVideo::ourGetPixel(unsigned short horizontal,unsigned short vertical,unsigned char* R,unsigned char* G,unsigned char* B,unsigned short rowbytes,Ptr pixbase){
	Ptr AdressOfRed;
	AdressOfRed = rowbytes * vertical +pixbase+horizontal*4+1;
	*R=*(AdressOfRed);
	*G=*(AdressOfRed+1);
	*B=*(AdressOfRed+2);
}

void MyVideo::convolve(unsigned short horizontal,unsigned short vertical,unsigned char* R,unsigned char* G,unsigned char* B,int MatrixSize,double* Matrix,unsigned short rowbytes,Ptr pixbase){
	long x,y,halfMatrix ,countMatrix =0,sumMatrix=0;
	double sumR=0,sumG=0,sumB=0;
	double temp;
	Ptr AdressOfRed;
	halfMatrix = MatrixSize/2;
	for (x=-halfMatrix;x<MatrixSize-halfMatrix;x++){
		for (y=-halfMatrix;y<MatrixSize-halfMatrix;y++){	
			
			AdressOfRed = rowbytes * (vertical+y) +pixbase+(horizontal+x)*4+1;					
			temp = (unsigned char)*(AdressOfRed);
			sumR += (temp * Matrix[countMatrix]);												
			
			temp = (unsigned char)*(AdressOfRed+1);
			sumG += (temp * Matrix[countMatrix]);
			
			
			temp = (unsigned char)*(AdressOfRed+2);
			sumB += (temp * Matrix[countMatrix]);
			
			countMatrix++;
		}
	}			
	clip(	sumR,0,255);															//	calles the CLIP macro that makes sure that the value is between  0 and 255
	clip(	sumG,0,255);
	clip(	sumB,0,255);
	
	*R = sumR;
	*G = sumG;
	*B = sumB;
	
}


unsigned char MyVideo::threshold(unsigned short horizontal,unsigned short vertical,unsigned short rowbytes,Ptr pixbase){
	
	long r=0,g=0,b=0 , difference=0;						
	// looking at the center pixel. getting RGB values as brightness.
	r =  (unsigned char) *(rowbytes * (vertical) +pixbase+(horizontal)*4+1);		 
	g =  (unsigned char) *(rowbytes * (vertical) +pixbase+(horizontal)*4+2);		
	b =  (unsigned char) *(rowbytes * (vertical) +pixbase+(horizontal)*4+3);		
	
	difference  = r + g + b;
	
	return (unsigned char)( difference);	
}


unsigned char MyVideo::GetEdge(unsigned short horizontal,unsigned short vertical,unsigned short rowbytes,Ptr pixbase){
	long x,y ,countMatrix =0,sumMatrix=0;
	long sumR=0,sumG=0,sumB=0 , thisgray , centergray ,difference=0;						
	Ptr AdressOfRed;	
	// looking at the center pixel. getting RGB values as brightness.
	centergray =  (unsigned char) *(rowbytes * (vertical) +pixbase+(horizontal)*4+1);		 
	centergray +=  (unsigned char) *(rowbytes * (vertical) +pixbase+(horizontal)*4+2);		
	centergray +=  (unsigned char) *(rowbytes * (vertical) +pixbase+(horizontal)*4+3);		
	
	// looking  at the neighhborhood,
	
	for (x=-2;x<2;x++){
		for (y=-2;y<2;y++){
			// neighborhood
			AdressOfRed = rowbytes * (vertical+y) +pixbase+(horizontal+x)*4+1;
			thisgray  =(unsigned char) *(AdressOfRed);	
			thisgray +=(unsigned char) *(AdressOfRed+1);
			thisgray +=(unsigned char) *(AdressOfRed+2);
			
			difference += abs(thisgray-centergray); // accumulating the difference.
			
		}
	}			
	return (unsigned char)( difference/ 3);	
}

