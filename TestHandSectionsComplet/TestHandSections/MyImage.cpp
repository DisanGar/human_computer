#include "MyImage.h"

MyImage::MyImage(){

}
MyImage::MyImage(int webCamera){

	cameraSrc = webCamera;
	cap = VideoCapture(webCamera);
}


