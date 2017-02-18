#pragma once
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "main.h"
#include "MyImage.h"

using namespace std;
using namespace cv;

class HandGesture
{
	
	public:

		MyImage m;
		HandGesture();

		// Almacena una matriz de puntos
		vector<vector<Point> > contours;
		
		// permiten crear el valor necesario para crear la funcion ConvexHull
		vector<vector<int> > hullI;
		vector<vector<Point> > hullP;

		// Vec4i es un vector definido de la siguente manera Vec<int, 4>
		vector <vector<Vec4i> > defects;	
		vector <Point> fingerTips;

		Rect rect;
		void printGestureInfo(Mat src);
		int cIdx;
		int frameNumber;
		int mostFrequentFingerNumber;
		int nrOfDefects;
		Rect bRect;
		double bRect_width;
		double bRect_height;
		bool isHand;
		bool detectIfHand();
		void initVectors();
		void getFingerNumber(MyImage *m);
		void eleminateDefects(MyImage *m);
		void getFingerTips(MyImage *m);
		void drawFingerTips(MyImage *m);

		void clickRightEvent();
		void clickLeftEvent();
		void moveMousePointer();
		void scrollDownEvent();
		void scrollUpEvent();

	private:
		string bool2string(bool tf);
		int fontFace;
		int prevNrFingerTips;
		void checkForOneFinger(MyImage *m);
		float getAngle(Point s,Point f,Point e);	
		vector<int> fingerNumbers;
		void analyzeContours();
		string intToString(int number);
		void computeFingerNumber();
		void drawNewNumber(MyImage *m);
		void addNumberToImg(MyImage *m);
		vector<int> numbers2Display;
		void addFingerNumberToVector();
		Scalar numberColor;
		int nrNoFinger;
		float distanceP2P(Point a,Point b);
		void removeRedundantEndPoints(vector<Vec4i> newDefects,MyImage *m);
		void removeRedundantFingerTips();
	
};

