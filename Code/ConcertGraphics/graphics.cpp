#include "opencv2/opencv.hpp"

#define PI 3.1415926

using namespace cv;
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

int main(int, char**)
{
	VideoCapture cam(0);
	if(!cam.isOpened())  // check if we succeeded
        return -1;
	Mat frame;
	namedWindow("Name",CV_WINDOW_NORMAL);
    while(true){
        cam >> frame;
        imshow("Name", frame);
    }
}
