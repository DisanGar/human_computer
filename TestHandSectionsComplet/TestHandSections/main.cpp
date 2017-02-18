#include "main.h"
#include "MyImage.h"
#include "ROI.h"



using namespace std;
using namespace cv;

int square_len;
int iSinceKFinit =0;
int c_lower[NSAMPLES][3];
int c_upper[NSAMPLES][3];

VideoWriter out;
Mat edges;
vector<My_ROI> roi;

//Promedio de color en este caso basado en una muestreo de 7 colores
int avgColor[NSAMPLES][3];// crear una aplicacion de 7 x 3

void init(){
	
	square_len = 20;
	iSinceKFinit = 0;

}

// Imprime el texto en una seccion del video, el color reprensentado por el Scalar
// Texto Ini = Generando regiones de interes, y el otro dice modelo de color elaborado
void printText(Mat src, string text){
	int fontFace = FONT_HERSHEY_SIMPLEX;

	putText(src, text, Point(src.cols/4, src.rows /10), fontFace, 0.7f,Scalar(200,0,0),2);
}

void waitForPalmCover(MyImage* m){

	// tiempo de espera para capturar las regiones de interes
	int waitCapture = 50;
	
	m->cap >> m->src;
	flip(m->src, m->src, 1);

	// No entiendo porque utiliza dentro del Push back el constructor del ROI
	roi.push_back(My_ROI(Point(m->src.cols/3, m->src.rows/6), Point(m->src.cols/3 + square_len,m->src.rows/6 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols/4, m->src.rows/2), Point(m->src.cols/4 + square_len,m->src.rows/2 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols/3, m->src.rows/1.5), Point(m->src.cols/3 + square_len,m->src.rows/1.5 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols/2, m->src.rows/2), Point(m->src.cols/2 + square_len,m->src.rows/2 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols/2.3, m->src.rows/2.3), Point(m->src.cols/2.3 + square_len,m->src.rows/2.3 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols/2, m->src.rows/1.5), Point(m->src.cols/2 + square_len,m->src.rows/1.5 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols/2.5, m->src.rows/1.8), Point(m->src.cols/2.5 + square_len,m->src.rows/1.8 + square_len), m->src));
	
	// Incremetado las regiones de interes logramos establcer un mejor aproximacion en el modelo de color.
	roi.push_back(My_ROI(Point(m->src.cols/3.5, m->src.rows/1.8), Point(m->src.cols/3.5 + square_len,m->src.rows/1.8 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols/2.8, m->src.rows/1.9), Point(m->src.cols/2.8 + square_len,m->src.rows/1.9 + square_len), m->src));
	roi.push_back(My_ROI(Point(m->src.cols/2.2, m->src.rows/2), Point(m->src.cols/2.2 + square_len,m->  src.rows/2 + square_len), m->src));

	//std::cout<<"m->src.cols"<<m->src.cols<<"m->src.ows "<<m->src.rows<<"squere_len"<<square_len; // lineas de la camara es de 
	//m->src.cols = 400 y m->src.rows= 640 y square_len = 20
	for(int i =0; i < waitCapture; i++){
		// Lo que captura del video  lo pasa a una imagen "src" 
    	m->cap >> m->src;
		flip(m->src, m->src, 1);
		
		for(int j = 0; j < NSAMPLES; j++){
			
			roi[j].draw_rectangle(m->src);
		}
		string imgText=string("Regiones de Interes de la mano");
		printText(m->src,imgText);	
		
		if(i==30){

			//imwrite("./waitforpalm.jpg",m->src);
		}

		// Muestra la mano de salida con las regiones ubicadas para generar el modelo de color.
		imshow("img1", m->src);
		out << m->src;
        if(cv::waitKey(30) >= 0) break;
	}

}

// Para que obtenemos la mediana de las regiones de interes?
// Obtenemos el valor medio de la distribucion de valores
// La mediana nos puede dar de manera mas rapida un valor tipico en una serie de valores sin sesgar el valor a uno minimo o maximo
// Es utilizada para sesgar una serie  de datos

int getMedian(vector<int> val){
	
	int median;
	size_t size = val.size();

	// Regularmente viene el valor 256 de tamaño
	// ordenamos el vector desde el menor al mas grande
	sort(val.begin(), val.end());
		// Si el valor del vector es par 
		if (size  % 2 == 0)  {
			// Otenemos el valor  del pixel en posicion central en un conjunto de datos ordenados
			median = val[size / 2 - 1] ;
		} else{
			// si el valor del vector es impar
			 median = val[size / 2];
		}
  

		return median;
}


void getAvgColor(My_ROI roi, int avg[3]){
	
	Mat r;
	roi.roi_ptr.copyTo(r);

			
	// Valores de color apartir del modelo de entrada, descartamos el uso de HSL 
	vector<int>hm; 
	vector<int>sm;  
	vector<int>vm;
	
	// generate vectors 256 valores para cada canal de color hm, sm, vm

	// Son lo tres valores de color.
	//int val = r.channels();
	
	for(int i=2; i < r.rows-2; i++){
    	for(int j=2; j < r.cols-2; j++){

			hm.push_back(r.data[r.channels() * (r.cols * i + j) + 0]);
        	sm.push_back(r.data[r.channels() * (r.cols * i + j) + 1]);
			vm.push_back(r.data[r.channels() * (r.cols * i + j) + 2]);
   		}
	}

	avg[0] = getMedian(hm);
	avg[1] = getMedian(sm);
	avg[2] = getMedian(vm);
}

void showRoiS(){

	Mat r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;

		roi[0].roi_ptr.copyTo(r1);
		roi[1].roi_ptr.copyTo(r2);
		roi[2].roi_ptr.copyTo(r3);
		roi[3].roi_ptr.copyTo(r4);
		roi[4].roi_ptr.copyTo(r5);
		roi[5].roi_ptr.copyTo(r6);
		roi[6].roi_ptr.copyTo(r7);
		roi[7].roi_ptr.copyTo(r8);
		roi[8].roi_ptr.copyTo(r9);		
		roi[9].roi_ptr.copyTo(r10);

		imshow("img1Roi", r1);
		imshow("img2Roi", r2);
		imshow("img3Roi", r3);
		imshow("img4Roi", r4);
		imshow("img5Roi", r5);
		imshow("img6Roi", r6);
		imshow("img7Roi", r7);
		imshow("img8Roi", r8);
		imshow("img9Roi", r9);	
		imshow("img10Roi", r10);	
		
}

void average(MyImage *m){
	
	m->cap >> m->src;
	
	// El valor 1 en la función flip sobre una entrada bidimensional significa que va a rotar sobre el eje Y
	flip(m->src, m->src, 1);
	for(int i=0; i<10; i++){

		m->cap >> m->src;
		flip(m->src, m->src, 1);
		// cambiamos el espacio de color de RGB a HSV
		// el color en modelo HSV nos permite manejar una base en escala de grices
		// donde la componente V sera representada en un rango de 0 a 255, este 
		// convencion nos permite tener un mejor aproximacion en entrada de video 
		// donde se tenga imagenes muy brillosas.
		cvtColor(m->src, m->src, ORIGCOL2COL);
		
		for(int j=0; j < NSAMPLES; j++){

			// Obtenemos el promedio del color 
			getAvgColor(roi[j], avgColor[j]);

			// Dibujamos el rectangulo sobre la region de interes establecida
			roi[j].draw_rectangle(m->src);

		}	

		//showRoiS();
		
		// el resultado final despues de ocupar el modelo de color HSV, lo cambiamos de
		// vuelta a un color RGB para su posterior binarizado.
		cvtColor(m->src, m->src, COL2ORIGCOL);
		//imwrite("alpha.png", m->);
		//imshow("alpha.png",m->src);
		string imgText = string("Encontrando el promedio del color (mano)");
		printText(m->src , imgText);	
		imshow("img1", m->src);
        if(cv::waitKey(30) >= 0) break;
	}
}



void iniTrackbars(){

	for(int i =0; i < NSAMPLES; i++){
		c_lower[i][0] = 30;//12;
		c_upper[i][0] = 30;//7;
		c_lower[i][1] = 30;
		c_upper[i][1] = 100; //40;
		c_lower[i][2] = 100;//80;
		c_upper[i][2] = 100;//80;
	}
}

// Este paso en el sistema es de suma utilidad debido a que la distribucion de los valores de color
// en una imagen depende de su iluminacion, la cual varea en las condiciones de luz presentes en la 
// imagen, camara, y otros factores de entrada. La normalizacion de color permite a las tecnicas de reconocimiento
// basadas en color compensar estas variaciones.
void normalizeColors(){
	
	// copy all boundries read from trackbar
	// to all of the different boundries

	// Copiamos todos los limites obtenidos a partir del trackbar
	for(int i=1; i < NSAMPLES; i++){
		for(int j=0; j < 3; j++){
			c_lower[i][j] = c_lower[0][j];	
			c_upper[i][j] = c_upper[0][j];	
		}	
	}

	// Normalizamos los limites dentro de un umbral de 0 a 255
	for(int i=0; i < NSAMPLES; i++){

		if((avgColor[i][0] - c_lower[i][0]) < 0){
			c_lower[i][0] = avgColor[i][0] ;
		
		}if((avgColor[i][1] - c_lower[i][1]) < 0){
			c_lower[i][1] = avgColor[i][1] ;
		
		}if((avgColor[i][2] - c_lower[i][2]) < 0){
			c_lower[i][2] = avgColor[i][2] ;
		
		}if((avgColor[i][0] + c_upper[i][0]) > 255){ 
			c_upper[i][0] = 255 - avgColor[i][0] ;
		
		}if((avgColor[i][1] + c_upper[i][1]) > 255){
			c_upper[i][1] = 255 - avgColor[i][1] ;
		
		}if((avgColor[i][2] + c_upper[i][2]) > 255){
			c_upper[i][2] = 255 - avgColor[i][2] ;
		}
	}
}

void showHandBinaries(MyImage *m){

	string arrTitle[] = {"img1","img2","img3","img4","img5","img6","img7","img8","img9","img10"};
	for(int i =0; i < 10; i++){
		imshow(arrTitle[i], m->bwList[i]);
	}

}


void produceBinaries(MyImage *m){	
	
	Scalar lowerBound;
	Scalar upperBound;
	Mat foo;
	
	for(int i=0; i < NSAMPLES; i++){

		normalizeColors();

		lowerBound = Scalar( avgColor[i][0] - c_lower[i][0] , avgColor[i][1] - c_lower[i][1], avgColor[i][2] - c_lower[i][2] );
		upperBound = Scalar( avgColor[i][0] + c_upper[i][0] , avgColor[i][1] + c_upper[i][1], avgColor[i][2] + c_upper[i][2] );
		// CV_8U  es  un pixel sin signo 8bit, puede tener valores de entre 0 a 255 que es el rango normal
		// para la mayoria de los formatos de video
		m->bwList.push_back(Mat(m->srcLR.rows, m->srcLR.cols, CV_8U));	
		
		//Construye una imagen a partir del modelo de color establecido en los limites
		inRange(m->srcLR, lowerBound, upperBound, m->bwList[i]);	
	}
	
	showHandBinaries(m);
	

	m->bwList[0].copyTo(m->bw);

	for(int i=1; i < NSAMPLES; i++){
		m->bw += m->bwList[i];	
	}

	imshow("imgResultUnion", m->bw);

	

	// Documentar median Blur
	medianBlur(m->bw, m->bw, 7);
}

void initWindows(){//(MyImage m){
    
	
	// Estas funciones despliegan las ventanas que mostraran el video y los trackbars
	//namedWindow("trackbars",CV_WINDOW_KEEPRATIO);
    namedWindow("img1",CV_WINDOW_FULLSCREEN);
}

/*
int findBiggestContour(vector<vector<Point>> contours){
    
	int indexOfBiggestContour = -1;
    int sizeOfBiggestContour = 0;

    for (int i = 0; i < contours.size(); i++){
        if(contours[i].size() > sizeOfBiggestContour){
            sizeOfBiggestContour = contours[i].size();
            indexOfBiggestContour = i;
        }
    }
    return indexOfBiggestContour;
}

void myDrawContours(MyImage *m, HandGesture *hg){
	
	int fontFace = FONT_HERSHEY_PLAIN;

	drawContours(m->src, hg->hullP, hg->cIdx, Scalar(200,180,0), 2, 8, vector<Vec4i>(), 0, Point());
	rectangle(m->src, hg->bRect.tl(), hg->bRect.br(), Scalar(0,0,200));
	vector<Vec4i>::iterator d = hg->defects[hg->cIdx].begin();
		
	
	vector<Mat> channels;
	Mat result;
		for(int i = 0; i<3 ;i++)
			channels.push_back(m->bw);
		
	merge(channels,result);
	//drawContours(result,hg->contours,hg->cIdx,cv::Scalar(0,200,0),6, 8, vector<Vec4i>(), 0, Point());
	drawContours(result,hg->hullP,hg->cIdx,cv::Scalar(0,0,250),10, 8, vector<Vec4i>(), 0, Point());

		
	
   		circle(result, ptFar, 9, Scalar(0,205,255), 5 );
		d++;

   	 }

	imwrite("contour_defects_before_eliminate.jpg",result);

}

void makeContours(MyImage *m, HandGesture* hg){
	
	Mat aBw;
	Mat showImg;

	m->src.copyTo(showImg);
	//imshow("imgBeforeUPMContours", showImg);	
	pyrUp(m->bw, m->bw);

	m->bw.copyTo(aBw);

	//imshow("imgUpDContours", aBw);
	//Canny(aBw, aBw, 100, 200, 3);
	findContours(aBw, hg->contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	hg->initVectors(); 
	hg->cIdx = findBiggestContour(hg->contours);
	
	if(hg->cIdx != -1){
	
		//	approxPolyDP( Mat(hg->contours[hg->cIdx]), hg->contours[hg->cIdx], 11, true );
		hg->bRect = boundingRect(Mat(hg->contours[hg->cIdx]));		
		convexHull(Mat(hg->contours[hg->cIdx]),hg->hullP[hg->cIdx],false,true);
		convexHull(Mat(hg->contours[hg->cIdx]),hg->hullI[hg->cIdx],false,false);
		approxPolyDP( Mat(hg->hullP[hg->cIdx]), hg->hullP[hg->cIdx], 18, true );
		
		if(hg->contours[hg->cIdx].size()>3 ){
			convexityDefects(hg->contours[hg->cIdx],hg->hullI[hg->cIdx],hg->defects[hg->cIdx]);
			hg->eleminateDefects(m);
		}
		
		bool isHand=hg->detectIfHand();
		//hg->printGestureInfo(m->src);//***********************************COMENTADA IMPORTANTE*********
		if(isHand){	
			hg->getFingerTips(m);
			hg->drawFingerTips(m);
			myDrawContours(m,hg);
		}
	}
}

*/

void showWindows(MyImage m){
	
	// Para disminuir la muetra de la imagen y desenfocar la imagen de salida
	pyrDown(m.bw, m.bw);
	pyrDown(m.bw , m.bw);

	Rect roi(Point( 3 * m.src.cols/4,0 ), m.bw.size());
	vector<Mat> channels;
	Mat result;
	
	// Tres canales de  color que posteriormente vamos a unir con la funcion merge
	for(int i=0; i < 3;i++)
		channels.push_back(m.bw);

	merge(channels, result);
	result.copyTo( m.src(roi));
	imshow("img1",m.src);	
}


int main(){

	Mat edges;
	MyImage m(0);

	init();

	m.cap >> m.src;

	if(!m.cap.isOpened()){
		return -1;
	}

	namedWindow("img1", CV_WINDOW_KEEPRATIO);

	waitForPalmCover(&m);
	average(&m);
	destroyWindow("img1");
	
	//m.cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
	//m.cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);
	bool isColor = (m.src.type() == CV_8UC3);
	int codec = CV_FOURCC('M','J','P','G');
	double fps = 25.0;

	string filename = "./live.avi";
	out.open(filename, codec, fps,  m.src.size(), isColor);

	destroyWindow("img1");

	namedWindow("img1",CV_WINDOW_FULLSCREEN);
	iniTrackbars();
	
	for(;;){
	
		m.cap >> m.src;
		flip(m.src,m.src,1);

		// Esta funcion me permite aplicar un disminucion  a la imagen por medio de una piramide Gaussina
		pyrDown(m.src, m.srcLR);//funcion de opencv
		blur(m.srcLR, m.srcLR, Size(3,3));//FUNCION DE OPENCV blur
		
		cvtColor(m.srcLR, m.srcLR, ORIGCOL2COL);//FUNCION DE OPENCV 
		imshow("ColorHSV", m.srcLR);
		produceBinaries(&m);

		/*cvtColor(m.srcLR,m.srcLR,COL2ORIGCOL);//FUNCION DE CVCOLOR 

		
			//FUNCION ARRIBA 

		cvtColor(m.srcLR,m.srcLR,COL2ORIGCOL);//FUNCION DE CVCOLOR 
		makeContours(&m, &hg);//FUNCION ARRIBA
		hg.getFingerNumber(&m);//FUNCION ARRIBA
		showWindows(m);
		out << m.src;*/
	

		//showWindows(m);
		//out << m.srcLR;
		

        if(cv::waitKey(30) == char('q')) break;
	
	}
	waitKey();

	destroyAllWindows();
	//out.release();
	m.cap.release();
	return 0;
    
}