/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxGui.h"

/************************************************************
************************************************************/

/**************************************************
description
	基底ベクトルを定義し、これに対し、
	translate, rotate, scale
	のmethodを準備。
	
	さらに、変換後の空間上での(x, y, z)が、正規直交空間ではどの座標になるか、を取得するmethod(get())も準備した


	translate, rotate, scale, の順に対して結果は独立.
	ofxxx() は独立でない.
	本classと結果が同じになる並びは、以下の通り.
		ofTranslate(shift_x, shift_y, shift_z);
		ofRotate(rotate_angle, rotate_x_axis, rotate_y_axis, rotate_z_axis);
		ofScale(scale_x, scale_y, scale_z);
**************************************************/
class AXIS{
private:
	/****************************************
	****************************************/
	/********************
	基底ベクトル
		(1, 0, 0), (0, 1, 0), (0, 0, 1)
	を、original空間上で表現した値を格納.
	********************/
	ofVec3f e_x;
	ofVec3f e_y;
	ofVec3f e_z;
	
	ofVec3f center;
	
public:
	/****************************************
	****************************************/
	AXIS() : e_x(1, 0, 0), e_y(0, 1, 0), e_z(0, 0, 1), center(0, 0, 0){
	}
	
	void Reset()
	{
		e_x = ofVec3f(1, 0, 0);
		e_y = ofVec3f(0, 1, 0);
		e_z = ofVec3f(0, 0, 1);
		
		center = ofVec3f(0, 0, 0);
	}
	
	
	void translate(float x, float y, float z)
	{
		center += x * e_x;
		center += y * e_y;
		center += z * e_z;
	}
	
	/******************************
	URL
		Rotate quad made in geometry shader
			http://stackoverflow.com/questions/28124548/rotate-quad-made-in-geometry-shader
			
			shader上での実装も記述してあり、大変参考になる.
	
		http://physmath.main.jp/src/rodrigues-rotation.html
			ロドリゲスの回転公式.
			軸 N は、単位ベクトル.
	
	description
		original ベクトル空間の値に変換後、回転.
		...e_xyzも、currentの基底ベクトルをoriginal空間で表現した値.
	******************************/
	void rotate(float angle_deg, ofVec3f _n)
	{
		/********************
		ofRotateと方向合わせる.
		********************/
		float angle_rad = -angle_deg * 3.1415 / 180.0;
		
		/********************
		_nをoriginalのベクトル空間上での値に変換し、
		original空間上で回転させる.
		********************/
		ofVec3f n(0, 0, 0);
		n += e_x * _n.x;
		n += e_y * _n.y;
		n += e_z * _n.z;
		n.normalize(); // 軸 N は、単位ベクトル.
		
		
		/********************
		********************/
		ofVec3f q;
		q.x =	  e_x.x * (n.x * n.x * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_x.y * (n.x * n.y * (1.0 - cos(angle_rad)) + n.z * sin(angle_rad))
				+ e_x.z * (n.x * n.z * (1.0 - cos(angle_rad)) - n.y * sin(angle_rad));
		
		q.y =     e_x.x * (n.y * n.x * (1.0 - cos(angle_rad)) - n.z * sin(angle_rad))
				+ e_x.y * (n.y * n.y * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_x.z * (n.y * n.z * (1.0 - cos(angle_rad)) + n.x * sin(angle_rad));
		
		q.z =     e_x.x * (n.z * n.x * (1.0 - cos(angle_rad)) + n.y * sin(angle_rad))
				+ e_x.y * (n.z * n.y * (1.0 - cos(angle_rad)) - n.x * sin(angle_rad))
				+ e_x.z * (n.z * n.z * (1.0 - cos(angle_rad)) + cos(angle_rad));
				
		e_x = q;
				
		/********************
		********************/
		q.x =	  e_y.x * (n.x * n.x * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_y.y * (n.x * n.y * (1.0 - cos(angle_rad)) + n.z * sin(angle_rad))
				+ e_y.z * (n.x * n.z * (1.0 - cos(angle_rad)) - n.y * sin(angle_rad));
		
		q.y =     e_y.x * (n.y * n.x * (1.0 - cos(angle_rad)) - n.z * sin(angle_rad))
				+ e_y.y * (n.y * n.y * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_y.z * (n.y * n.z * (1.0 - cos(angle_rad)) + n.x * sin(angle_rad));
		
		q.z =     e_y.x * (n.z * n.x * (1.0 - cos(angle_rad)) + n.y * sin(angle_rad))
				+ e_y.y * (n.z * n.y * (1.0 - cos(angle_rad)) - n.x * sin(angle_rad))
				+ e_y.z * (n.z * n.z * (1.0 - cos(angle_rad)) + cos(angle_rad));
				
		e_y = q;

		/********************
		********************/
		q.x =	  e_z.x * (n.x * n.x * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_z.y * (n.x * n.y * (1.0 - cos(angle_rad)) + n.z * sin(angle_rad))
				+ e_z.z * (n.x * n.z * (1.0 - cos(angle_rad)) - n.y * sin(angle_rad));
		
		q.y =     e_z.x * (n.y * n.x * (1.0 - cos(angle_rad)) - n.z * sin(angle_rad))
				+ e_z.y * (n.y * n.y * (1.0 - cos(angle_rad)) + cos(angle_rad))
				+ e_z.z * (n.y * n.z * (1.0 - cos(angle_rad)) + n.x * sin(angle_rad));
		
		q.z =     e_z.x * (n.z * n.x * (1.0 - cos(angle_rad)) + n.y * sin(angle_rad))
				+ e_z.y * (n.z * n.y * (1.0 - cos(angle_rad)) - n.x * sin(angle_rad))
				+ e_z.z * (n.z * n.z * (1.0 - cos(angle_rad)) + cos(angle_rad));
				
		e_z = q;
	}

	/******************************
	******************************/
	void scale(float x, float y, float z)
	{
		e_x *= x;
		e_y *= y;
		e_z *= z;
	}
	
	/******************************
	description
	
	param
		point
			変換後の空間上でのベクトル値.

		target
			return.
			original空間上での値.
	******************************/
	void get(ofVec3f point, ofVec3f& target)
	{
		target = center + point.x * e_x + point.y * e_y + point.z * e_z;
	}

};

/**************************************************
**************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	
	/********************
	********************/
	ofxPanel gui;
	
	ofxFloatSlider shift_x;
	ofxFloatSlider shift_y;
	ofxFloatSlider shift_z;
	
	ofxFloatSlider rotate_angle;
	ofxFloatSlider rotate_x_axis;
	ofxFloatSlider rotate_y_axis;
	ofxFloatSlider rotate_z_axis;
	
	ofxFloatSlider scale_x;
	ofxFloatSlider scale_y;
	ofxFloatSlider scale_z;
	
	ofxToggle b_vbo;
	ofxToggle b_filled;
	ofxIntSlider LineWidth;
	
	
    ofxColorSlider color;
	
	ofEasyCam cam;
	
	/********************
	********************/
	enum{
		NUM_VERTS = 4,
	};
	ofVbo Vbo;
	ofVec3f vbo_Verts[NUM_VERTS];
	ofFloatColor vbo_Color[NUM_VERTS];
	

public:
	/****************************************
	****************************************/
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
};
