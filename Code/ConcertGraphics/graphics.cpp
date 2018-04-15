#include "opencv2/opencv.hpp"

#define PI 3.1415926

using namespace cv;
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    
    while ((dirp = readdir(dp)) != NULL) {
        string name = string(dirp->d_name);
        if(name.length() > 3 && name.substr(name.length() - 3) == "mp4")
            files.push_back(dir + string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int loadvids (vector<string> &names, vector<VideoCapture> &files, vector<int> &sizes)
{
    for (unsigned int i = 0;i < names.size();i++) {
        cout << names[i] << endl;
        VideoCapture cap(names[i]);
        if ( !cap.isOpened() ){
            cout << "Cannot open the video file. \n";
            return -1;
        }
        files.push_back(cap);
        sizes.push_back(cap.get(CV_CAP_PROP_FRAME_COUNT));
    }
    return 0;
}

int outline (Mat &frame, Mat &output)
{
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    cv::Mat binaryMat(frame.size(), frame.type());
    cv::threshold(frame, binaryMat, 100, 250, cv::THRESH_BINARY);
    GaussianBlur(frame, frame, Size(7,7), 0.6, 0.6);
    Canny(frame, output, 30, 60, 3);
    return 0;
}

int colored_outline (Mat &frame, vector<vector<Point> > &contours, vector<Vec4i> &hierarchy, Mat &output)
{
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    cv::Mat binaryMat(frame.size(), frame.type());
    cv::threshold(frame, binaryMat, 100, 250, cv::THRESH_BINARY);
    GaussianBlur(frame, frame, Size(7,7), 0.6, 0.6);
    Canny(frame, frame, 30, 60, 3);
    findContours(frame, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, Point(0,0));
    output = Mat(frame.rows, frame.cols, CV_8UC3, Scalar(0,0,0));
    int red_color = rand() % 256, blue_color = rand() % 256, green_color = rand() % 256;
    int mult = rand() % 2 + 3;
    for (unsigned int i=0; i<contours.size(); i++){
        if (hierarchy[i][3] < 0){
            double area0 = arcLength(contours[i], false);
            if (area0 > 600)
                drawContours(output, contours, i, Scalar(green_color, blue_color+i*mult,red_color), 1, 8);
            else if(area0 > 300)
                drawContours(output, contours, i, Scalar(green_color, red_color+i*mult, blue_color), 1, 8);
            else
                drawContours(output, contours, i, Scalar(blue_color, green_color, red_color+i*mult), 1, 8);
        }
    }
    return 0;
}

int main(int, char**)
{
    std::string path = "videos/";
    std::vector<string> filenames;
    std::vector<VideoCapture> videos;
    std::vector<int> lengths;
    int WIDTH = 800, HEIGHT = 600;
    int frame_count = 0;
    int current_video = 2;
    
    // define sub-structures
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    
    getdir(path, filenames);
    loadvids(filenames, videos, lengths);
    int num_videos = videos.size();
	Mat frame;
    Mat altered;
	namedWindow("Original",CV_WINDOW_NORMAL);
    namedWindow("Test",CV_WINDOW_NORMAL);
    while(true){
        videos[current_video] >> frame;
        frame_count ++;
        if (frame_count >= lengths[current_video]){
            videos[current_video].set(CV_CAP_PROP_POS_FRAMES, 0);
            frame_count = 0;
            continue;
        }
        cv::resize(frame, frame, cv::Size(WIDTH, HEIGHT));
        //imshow("Original", frame);
        colored_outline(frame, contours, hierarchy, altered);
        imshow("Test", altered);
        char c=(char)waitKey(25);
        if(c==27)
            break;
    }
    destroyAllWindows();
    return 0;
}
