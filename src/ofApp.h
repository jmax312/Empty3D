#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "Math/MathUtils.h"

#include "Utils/ofTrueTypeFontExt.h"
#include "Utils/Cameras/ofxWalkingFirstPersonCamera.h"

class ofApp : public ofBaseApp
{
	public:
		
		void setup();
		void update();
		void draw();
		void setNormals(ofMesh &mesh);

		void keyPressed(int key);
	
		ofxFirstPersonCamera	camera;
	
		ofTrueTypeFontExt		fontSmall;
    
    ofMesh mesh;

	ofVec3f pos, circ; 
	float radius;
	ofColor color;
	int H, W;
};
