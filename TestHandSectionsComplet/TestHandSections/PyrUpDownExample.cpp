#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

/// Global variables
//Mat src, dst, tmp;
char* window_name = "Pyramids Demo";


/**
 * @function main
 */
/*int main( ){
 
	Mat src, dst, tmp;

	printf( "\n Zoom In-Out demo  \n " );
	printf( "------------------ \n" );
	printf( " * [u] -> Zoom in  \n" );
	printf( " * [d] -> Zoom out \n" );
	printf( " * [ESC] -> Close program \n \n" );

	src = imread("handTest.jpg", 1);
	if( !src.data )
    { printf(" No data! -- Exiting the program \n");
      return -1; }

	tmp = src;
	dst = tmp;

    /// Create window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );
  imshow( window_name, dst );

  /// Loop
  

	pyrUp( tmp, dst);
    printf( "** Zoom In: Image x 2 \n" );
    imshow( "Zoom IN", dst );

	pyrDown( tmp, dst, Size( tmp.cols/2, tmp.rows/2 ) );
    printf( "** Zoom Out: Image / 2 \n" );
	imshow("Zoom Out", dst );

	waitKey();
 
  return 0;
}*/