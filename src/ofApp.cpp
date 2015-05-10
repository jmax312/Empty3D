#include "ofApp.h"

//-----------------------------------------------------------------------------------------
//
void ofApp::setup()
{
	fontSmall.loadFont("Fonts/DIN.otf", 8 );
	circ = ofVec3f (0, 0, 0); //used for animation
	radius = 2; //used for animation //change this to zero if you want to have movement that gains momentum over time
		
	// Give us a starting point for the camera
	camera.setNearClip(0.01f);
	camera.setPosition( 0, 4, 10 );
	camera.setMovementMaxSpeed( 0.1f );

	H = 30; //height for mesh
	W = 30; //width for mesh
	color = ofColor(100, 50, 200); //starting color
	
    //sets up the mesh's vertices and color
	for (int y = 0; y < H; y++){ //as long as y is less than 30
		for (int x = 0; x < W; x++){ //and x is less than 30
			mesh.addVertex(ofVec3f((x - W/2), (y - H/2), 0)); //add a vertex along each of these x and y points
			mesh.addColor(color); //puts the color in
		}
	}

	//sets up the triangle indices
    for (int y=0; y<H-1; y++) { //as long as y is less than the height-1
        for (int x=0; x<W-1; x++) { //and x is less than the width-1
            int i1 = x + W * y; //0 is the first index
            int i2 = x+1 + W * y; //1 is the second
            int i3 = x + W * (y+1); //30 is the third
            int i4 = x+1 + W * (y+1); //31 is the fourth
            mesh.addTriangle( i1, i2, i3 ); //0, 1, 30
            mesh.addTriangle( i2, i4, i3 ); //1, 31, 30
        }
    }

	setNormals(mesh); //sets the normals to the mesh (function down below)
	
}

//-----------------------------------------------------------------------------------------
//
void ofApp::update()
{
	float time = ofGetElapsedTimef(); //our time variable for animation

	//radius += 0.001; //uncomment this if you want to have movement that gains momentum
	
	for (int y=0; y<H; y++) { //for as long as y is less than the height
        for (int x=0; x<W; x++) { //and x is less than the width
            int i = x + W * y;	//our vertex index will equal x plus the width times y
            ofPoint v = mesh.getVertex( i ); //gets the vertices along all the points 
			circ.x = x + radius * cos(time);
			circ.y = y + radius * sin(time);
			circ.z = circ.x * circ.y;

            float move = ofNoise( circ.x * 0.05, circ.y * 0.05, circ.z * 0.05 ); //noise value for animation
			v.z = move; //changes the z values of the mesh points using the noise value
			
            mesh.setVertex( i, v ); //updates the mesh vertices
            mesh.setColor( i, ofColor( move*180, move * 50, 220 ) ); //changes the color based on z movement
        }
    }
    setNormals( mesh );	//updates the normals
	
}

//-----------------------------------------------------------------------------------------
//
void ofApp::draw()
{
	ofBackgroundGradient( ofColor(40,40,40), ofColor(0,0,0), OF_GRADIENT_CIRCULAR);	
	
	ofEnableDepthTest();
	
	camera.begin();
	
		// draw a grid on the floor
		ofSetColor( ofColor(60) );
		ofPushMatrix();
			ofRotate(90, 0, 0, -1);
			ofDrawGridPlane( 12 );
		ofPopMatrix();

		ofPushMatrix(); //rotate and translate the mesh
		ofRotate(90, 1, 0, 0);
		ofTranslate(0, 0, -3);
			mesh.draw();
		ofPopMatrix();
	
	camera.end();

	ofSetColor( ofColor::white );
	ofDisableDepthTest();


	fontSmall.drawStringShadowed(ofToString(ofGetFrameRate(),2), ofGetWidth()-35, ofGetHeight() - 6, ofColor::whiteSmoke, ofColor::black );
}

//-----------------------------------------------------------------------------------------//
//Universal function which sets normals for the triangle mesh
void ofApp::setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}





void ofApp::keyPressed(int key)
{
	if( key == 'f' )
	{
		ofToggleFullscreen();
	}
}
