#include "opencv2/opencv.hpp"

#define PI 3.1415926

using namespace cv;
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

cv::Mat drawFractal(cv::Mat &frame, int &frame_num)
{
    frame.setTo(cv::Scalar::all(0));
    
    int xorigin = frame.cols / 2;
    int yorigin = frame.rows / 2;
    int r, c;
    int x1, y1;
    int x2, y2;
    int rad = 100;
    rad = pow(rad, 2);
    
    // equation (circle): rad^2 = r^2 + c^2
    // equation (ellipse): rad^2 = (r*0.8)^2 + c^2
    
    float loop_length = 60.0;
    if (frame_num > loop_length)
        frame_num = loop_length;
    float ratio1 = (loop_length - frame_num) / loop_length;
    float ratio2 = frame_num / loop_length;
    cout << "ratio1: " << ratio1 << "  ratio2: " << ratio2 << endl;
    
    
    
    // REVERSE THE ORDER??
    // Try finding an array of points to change to white (for each fractal)
    // 1*list1 + 0*list2 = white pixels
    
    vector<cv::Point2f> coords1;
    for (r = 0; r < frame.rows; r++){
        y1 = pow(r - yorigin, 2);
        for(c = 0; c < frame.cols; c++)
        {
            x1 = pow(c - xorigin, 2);
            if (x1 + y1 < rad)
                coords1.push_back(cv::Point2f(c, r) * ratio1);
            //else
            //    coords1.push_back(cv::Point2f(0, 0));
        }
    }
    
    vector<cv::Point2f> coords2;
    for (r = 0; r < frame.rows; r++){
        y1 = pow(r - yorigin, 2) * 0.6;
        for(c = 0; c < frame.cols; c++)
        {
            x1 = pow(c - xorigin, 2);
            if (x1 + y1 < rad)
                coords2.push_back(cv::Point2f(c, r) * ratio2);
            //else
            //    coords2.push_back(cv::Point2f(0, 0));
        }
    }
    
    
    
    // ERROR: the coordinates aren't matching up
    // Sort them/order by previous coordinates (like a 2D array), then you can compare 1-1
    cv::Point2f point1;
    cv::Point2f point2;
    if (coords1.size() > coords2.size()){
        for (int i = 0; i < coords1.size(); i++) {
            point1 = coords1[i];
            point2 = cv::Point2f(xorigin,yorigin);
            try {
                point2 = coords2[i];
            } catch (exception ex) {}
            frame.at<uchar>(point1 + point2) = 255;
        }
    }
    else{
        for (int i = 0; i < coords2.size(); i++) {
            point2 = coords2[i];
            point1 = cv::Point2f(xorigin,yorigin);
            try {
                point1 = coords1[i];
            } catch (exception ex) {}
            frame.at<uchar>(point1 + point2) = 255;
        }
    }
    
    cout << frame_num << endl;
    return frame;
}

int main(int, char**)
{
    
    cv::Mat frame = cv::Mat(600,1000, CV_8UC1, Scalar(0,0,0));
    namedWindow("frame",CV_WINDOW_AUTOSIZE);
    int frame_num = 0;
    
    for(;;)
    {
        frame = drawFractal(frame, frame_num);
        imshow("frame", frame);
        waitKey(1);
        frame_num++;
    }
    return 0;
}
