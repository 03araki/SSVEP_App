#pragma once

#include "ofMain.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment( lib, "WinMM.lib" )
 
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofPoint ptOrig;			// チェッカーボードの原点
		int iUpdateCount;		// 描画回数のカウンタ
		UINT uiTimerID;
		bool bFullscreenStatus;
		bool bHelpMenuStatus;
		int iVisualMode;
		bool bObservingPoint;
};
