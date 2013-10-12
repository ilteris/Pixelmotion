#include <Carbon/Carbon.h>
#include "MyVideo.h"
#include <iostream>
#include "MyLine.h"
void initialize();
void initializeWindow();
void CopyToWindow ();
void draw();
void timeIt();

WindowPtr	ourWindow; 
Rect		windRect;

GWorldPtr	drawPort;
MyVideo my;

long count=0,FPS =0;
long startTicks=-1000;
// video props

const unsigned int numofPixels = 25000;
MyLine pixels[numofPixels];

int main() {
	
	initialize();
	draw();
	
}


void timeIt(){
	long theTicks;
	Str255 theString;
	count ++;
	theTicks=TickCount();
	if (theTicks-startTicks > 60 *5){ 
		// everytime 5 seconds pass we reset it. 
		// use event loop if it is asyncronized. create a timer, like a callback function.
		// smooth animationd doesn't occur when you try to get the most out of the code, so 
		//if you build a timer you can getaway with more smooth animations
		
		startTicks = theTicks;				
		FPS = count/5;
		count = 0;
	}
}


void initialize() {
	int i;
	for(i=0; i<numofPixels; i++) {
		pixels[i] = MyLine::MyLine();
	}
	
	initializeWindow();
}

void initializeWindow() {
	OSErr error;
		
	SetRect(&windRect, 100, 100, 740, 580);
	InitCursor();
	ourWindow = NewCWindow( 0L, &windRect,  "\pMidterm2", true, noGrowDocProc,(WindowPtr)-1L, true, 0L ); 
	if(ourWindow == nil) ExitToShell();
	ShowWindow(ourWindow);
	SetPortWindowPort(ourWindow);
	SetRect(&windRect, 0,0,640,480);
	// this decides sizeof the window.
	error =NewGWorld(&drawPort, 32, &windRect, nil, nil,0 );					// creating our offscreen buffer
	if (error != noErr ) ExitToShell();
		
	 std::cout << "hello" << "\n";
	 my.initVideo();
	

}


void draw() {
	EventRecord anEvent;
	WindowPtr   evtWind;
	short       clickArea;
	Rect        screenRect;
	Point		thePoint;
	for (;;){
		if (WaitNextEvent( everyEvent, &anEvent, 0, nil )){
			if (anEvent.what == mouseDown){
				clickArea = FindWindow( anEvent.where, &evtWind );				
				if (clickArea == inDrag){
					GetRegionBounds( GetGrayRgn(), &screenRect );
					DragWindow( evtWind, anEvent.where, &screenRect );
				}
				else if (clickArea == inContent){
					// I commented this out and it still works.
					//	SGSettingsDialog(gSeqGrabber, gVideoChannel, 0, nil, 0L, nil, nil);
				 	SysBeep(10);
					if (evtWind != FrontWindow())
						SelectWindow( evtWind );
					
					else{
						thePoint = anEvent.where;
						GlobalToLocal( &thePoint );
					}
				}
				else if (clickArea == inGoAway)
					if (TrackGoAway( evtWind, anEvent.where ))
						return;
			}
		}
		SetGWorld(drawPort,nil);
		EraseRect(&windRect);
		my.draw(windRect,drawPort,pixels,numofPixels);
	//	my.seqGrabber();
		int i;
		
		for(i=0; i<numofPixels; i++) {
		
			pixels[i].drawLine();
			
		}
		timeIt();
		 CopyToWindow();
	}	
}

void CopyToWindow (){													//  copy all our buffer to the window, completely replaceing 
																			//  everything that was there
	Rect sourceRect,destRect;
	SetPortWindowPort(ourWindow);
	GetPortBounds( GetWindowPort(ourWindow), &destRect ); 
	GetPortBounds( drawPort, &sourceRect ); 
	CopyBits( GetPortBitMapForCopyBits( drawPort ), GetPortBitMapForCopyBits(GetWindowPort(ourWindow)),
			  &sourceRect, &destRect, srcCopy, NULL );
	
}
