#include "ofApp.h"

bool bDispStatus;
bool bCheckerStatus;	// チェッカーパターンの入れ替え

int CHECKER_WIDTH = 48;
int RECT_NUM;

ofColor Color1( 255, 255, 255 );
ofColor Color2( 0, 0, 0 );

int iRate = 50; //20

void CALLBACK TimerProc( UINT uID, UINT uMsg, DWORD dUser, DWORD dw1, DWORD dw2 ){
	if( bDispStatus ) bCheckerStatus = !bCheckerStatus;
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground( Color1 );
	ofSetVerticalSync( true );

	bFullscreenStatus = false;
	ofSetFullscreen( bFullscreenStatus );
	// チェッカーボードの原点

	RECT_NUM = ceil( ofGetWidth() / CHECKER_WIDTH ) + 1;
	ptOrig.x = (ofGetWidth() / 2.0) - (CHECKER_WIDTH * RECT_NUM / 2.0);
	ptOrig.y = (ofGetHeight() / 2.0)  - (CHECKER_WIDTH * RECT_NUM / 2.0);
	
	bCheckerStatus = true;
	bDispStatus = false;
	bHelpMenuStatus = true;
	iVisualMode = 0;
	bObservingPoint = true;
}

//--------------------------------------------------------------
void ofApp::update(){
}

void ofApp::exit() {
	timeKillEvent( uiTimerID );
}

//--------------------------------------------------------------
void ofApp::draw(){
	// チェッカーボードの描画
	if( iVisualMode >= 3 ) {
		ofBackground( 0, 0, 0 );
		ofSetColor( 255, 255, 255 );
		ofCircle( ofGetWidth() / 2.0, ofGetHeight() / 2.0, ofGetHeight() / 2.0 );
	} else {
		ofBackground( Color1 );
	}

	// パターンの描画
	ofSetColor( Color2 );
	
	for( int i = 0; i < RECT_NUM; i ++ ) {
		for( int j = (i + (int) bCheckerStatus) % 2; j < RECT_NUM; j += 2 ) {
			ofRect( ptOrig.x + i * CHECKER_WIDTH, ptOrig.y + j * CHECKER_WIDTH, CHECKER_WIDTH, CHECKER_WIDTH );
		}
	}

	if( iVisualMode == 1 || iVisualMode == 4 ) {
		ofSetColor( 0, 0, 0 );
		ofRect( 0, 0, ofGetWidth() / 2.0, ofGetHeight() );
	} else if( iVisualMode == 2 || iVisualMode == 5 ) {
		ofSetColor( 0, 0, 0 );
		ofRect( ofGetWidth() / 2.0, 0, ofGetWidth() / 2.0, ofGetHeight() );
	}

	if( bObservingPoint ) {
		ofSetColor( 255, 0, 0 );
		ofRect( (ofGetWidth() / 2.0) - 10, (ofGetHeight() / 2.0) - 80, 20, 160 );
		ofRect( (ofGetWidth() / 2.0) - 80, (ofGetHeight() / 2.0) - 10, 160, 20 );
	}

	if( bHelpMenuStatus ) {
		string str;
		ofSetColor( 50, 50, 50 );
		ofRect( 30, ofGetHeight() - 220, 400, 200 );
		ofSetColor( 255, 255, 0 );
		ofDrawBitmapString( "h: on/off this menu", 50, ofGetHeight() - 200 );
		ofDrawBitmapString( "s: start/stop visual stimulation", 50, ofGetHeight() - 180 );
		ofDrawBitmapString( "f: full screen mode", 50, ofGetHeight() - 160 );
		ofDrawBitmapString( "o: show observing point", 50, ofGetHeight() - 140 );
		ofDrawBitmapString( "m: visual stimulation mode (full, left, right)", 50, ofGetHeight() - 120 );
		ofDrawBitmapString( "up/down: change pattern refresh frequency", 50, ofGetHeight() - 100 );
		ofDrawBitmapString( "left/right: change pattern size", 50, ofGetHeight() - 80 );
		str = "pattern refresh freqency: " + ofToString( 1000 / (float) iRate ) + " Hz (" + ofToString( iRate ) + " ms)";
		ofDrawBitmapString( str, 50, ofGetHeight() - 50 );
		str = "pattern size: " + ofToString( CHECKER_WIDTH ) + " pixel";
		ofDrawBitmapString( str, 50, ofGetHeight() - 30 );
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch( key ) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
		iVisualMode = key - '0';
		break;
	case 's':
		bDispStatus = !bDispStatus;
		if( bDispStatus ) {
			timeBeginPeriod( 1 );
			uiTimerID = timeSetEvent( iRate, 1, TimerProc, NULL, TIME_PERIODIC );
		} else {
			timeKillEvent( uiTimerID );
			timeEndPeriod( 1 );
		}
		break;
	case 'f':
		bFullscreenStatus = !bFullscreenStatus;
		ofSetFullscreen( bFullscreenStatus );
		// チェッカーボードの原点
		ptOrig.x = (ofGetWidth() / 2.0) - (CHECKER_WIDTH * RECT_NUM / 2.0);
		ptOrig.y = (ofGetHeight() / 2.0)  - (CHECKER_WIDTH * RECT_NUM / 2.0);
		break;
	case 'h':
		bHelpMenuStatus = !bHelpMenuStatus;
		break;
	case 'm':
		iVisualMode = (iVisualMode + 1) % 6;
		break;
	case 'o':
		bObservingPoint = !bObservingPoint;
		break;
	case OF_KEY_UP:
		iRate --;
		if( iRate == 0 ) iRate = 1;
		break;
	case OF_KEY_DOWN:
		iRate ++;
		break;
	case OF_KEY_LEFT:
		CHECKER_WIDTH --;
		if( CHECKER_WIDTH == 1 ) CHECKER_WIDTH = 2;
		RECT_NUM = ceil( ofGetWidth() / CHECKER_WIDTH ) + 1;
		break;
	case OF_KEY_RIGHT:
		CHECKER_WIDTH ++;
		RECT_NUM = ceil( ofGetWidth() / CHECKER_WIDTH ) + 1;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	RECT_NUM = ceil( ofGetWidth() / CHECKER_WIDTH ) + 1;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
