#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat redFilter(const Mat& src)
{
    assert(src.type() == CV_8UC3);

    Mat redOnly;
    inRange(src, Scalar(0, 0, 0), Scalar(0, 0, 255), redOnly);

    return redOnly;
}

/*int main()
{
    Mat input = imread("testInRange.png",1);

    imshow("input", input);
    waitKey();

    Mat redOnly = redFilter(input);

    imshow("redOnly", redOnly);
    waitKey();

    // detect squares after filtering...

    return 0;
}*/
