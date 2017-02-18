#include "Roi.h"
#include "MyImage.h"

My_ROI::My_ROI(){
	
	upper_corner = Point(0,0);
	lower_corner = Point(0,0);
}

My_ROI::My_ROI(Point u_corner, Point l_corner, Mat src){

	upper_corner = u_corner;
	lower_corner = l_corner;
	color = Scalar(0,0,255);
	border_thickness = 2;

	roi_ptr = src(Rect(u_corner.x, u_corner.y, l_corner.x - u_corner.x, l_corner.y - u_corner.y));

}

void My_ROI::draw_rectangle(Mat src){
	
	rectangle(src, upper_corner, lower_corner, color, border_thickness);
}





