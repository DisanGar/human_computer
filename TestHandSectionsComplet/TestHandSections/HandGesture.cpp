#include "HandGesture.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace cv;


HandGesture::HandGesture(){
	
	// Numero de cuadrod de la imagen
	frameNumber = 0;
	// Numero de dedos ubicados en la imagen
	nrNoFinger = 0;
	//Tamaño de letra del tamaño cuando reconoce los fingers es de tipo entero
	fontFace = FONT_HERSHEY_PLAIN;

}

