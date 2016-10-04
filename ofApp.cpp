#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetVerticalSync(true);
	ofSetFrameRate( 60 );
	
	/********************
	********************/
	gui.setup("Parameters", "settings.xml");
	
	gui.add( shift_x.setup( "shift_x", 0, -200, 200 ) );
	gui.add( shift_y.setup( "shift_y", 0, -200, 200 ) );
	gui.add( shift_z.setup( "shift_z", 0, -200, 200 ) );
	
	gui.add( rotate_angle.setup( "rotate_angle", 0, -180, 180 ) );
	gui.add( rotate_x_axis.setup( "rotate_x_axis", 0, 0, 1 ) );
	gui.add( rotate_y_axis.setup( "rotate_y_axis", 0, 0, 1 ) );
	gui.add( rotate_z_axis.setup( "rotate_z_axis", 1, 0, 1 ) );
	
	gui.add( scale_x.setup( "scale_x", 1, 0.5, 4 ) );
	gui.add( scale_y.setup( "scale_y", 1, 0.5, 4 ) );
	gui.add( scale_z.setup( "scale_z", 1, 0.5, 4 ) );
	
	gui.add( b_vbo.setup( "b_vbo", false ) );
	
	gui.add( color.setup("color", ofColor(0, 0, 255, 255), ofColor(0, 0, 0, 0), ofColor(255, 255, 255, 255)) );
	gui.add( b_filled.setup( "b_filled", true ) );
	gui.add( LineWidth.setup( "LineWidth", 2, 1, 5 ) );
	
	/********************
	********************/
	for(int i = 0; i < NUM_VERTS; i++){
		ofColor temp = color;
		vbo_Color[i].set(float(temp.r)/255, float(temp.g)/255, float(temp.b)/255, (temp.a)/255);
	}
	vbo_Verts[0] = ofVec3f(-50,  50, 0);
	vbo_Verts[1] = ofVec3f( 50,  50, 0);
	vbo_Verts[2] = ofVec3f( 50, -50, 0);
	vbo_Verts[3] = ofVec3f(-50, -50, 0);
	
	Vbo.setVertexData(vbo_Verts, NUM_VERTS, GL_DYNAMIC_DRAW);
	Vbo.setColorData(vbo_Color, NUM_VERTS, GL_DYNAMIC_DRAW);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()	{
	/********************
	********************/
	if ( b_filled ) ofFill(); else ofNoFill();
	
	ofBackground(0);
	
	ofDisableAlphaBlending();
	ofEnableDepthTest();
	ofEnableSmoothing();
	ofSetLineWidth( LineWidth );
	
	/********************
	********************/
	cam.begin();
	if(!b_vbo){
		ofColor temp = color;
		ofSetColor(temp.r, temp.g, temp.b, temp.a);
		
		ofPushMatrix();
		
		ofTranslate(shift_x, shift_y, shift_z);
		ofRotate(rotate_angle, rotate_x_axis, rotate_y_axis, rotate_z_axis);
		ofScale(scale_x, scale_y, scale_z);
		ofRect( -50, -50, 100, 100 );
		
		ofPopMatrix();
		
	}else{
		/********************
		********************/
		AXIS axis;
		
		axis.translate(shift_x, shift_y, shift_z);
		axis.rotate(rotate_angle, ofVec3f(rotate_x_axis, rotate_y_axis, rotate_z_axis));
		axis.scale(scale_x, scale_y, scale_z);

		/********************
		********************/
		/* */
		ofVec3f target;
		axis.get(ofVec3f(-50, 50, 0), target);
		vbo_Verts[0].set(target);

		axis.get(ofVec3f(50, 50, 0), target);
		vbo_Verts[1].set(target);

		axis.get(ofVec3f(50, -50, 0), target);
		vbo_Verts[2].set(target);
		
		axis.get(ofVec3f(-50, -50, 0), target);
		vbo_Verts[3].set(target);
	
		Vbo.updateVertexData(vbo_Verts, NUM_VERTS);
		
		/* */
		for(int i = 0; i < NUM_VERTS; i++){
			ofColor temp = color;
			vbo_Color[i].set(float(temp.r)/255, float(temp.g)/255, float(temp.b)/255, (temp.a)/255);
		}
		Vbo.updateColorData(vbo_Color, NUM_VERTS);
		
		/********************
		********************/
		Vbo.draw(GL_QUADS, 0, NUM_VERTS);
	}
	cam.end();
	
	ofDisableDepthTest();		// for gui.draw()
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case ' ':
			ofSaveScreen("image.png");
			printf("save image\n");
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
