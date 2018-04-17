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
#define CVUI_IMPLEMENTATION
#include "cvui/cvui.h"

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
        VideoCapture cap(names[i]);
        if ( !cap.isOpened() ){
            cout << "Cannot open the video file " << names[i] <<" \n";
            return -1;
        }
        files.push_back(cap);
        sizes.push_back(cap.get(CV_CAP_PROP_FRAME_COUNT));
        cout << names[i] << ": " << cap.get(CV_CAP_PROP_FRAME_COUNT) << " frames\n";
    }
    return 0;
}

int decodevids ( vector<VideoCapture> &files, cv::Size &disp_size, vector<vector<Mat> > &data)
{
    for (int i = 0; i < files.size(); i++)
    {
        Mat frame;
        vector<Mat> vid_data;
        int count = 0;
        int l = files[i].get(CV_CAP_PROP_FRAME_COUNT);
        while (true)
        {
            count ++;
            if (count >= l)
                break;
            files[i] >> frame;
            cv::resize(frame, frame,  disp_size);
            vid_data.push_back(frame);
        }
        data.push_back(vid_data);
        cout << "Loaded Video " << i << "\n";
    }
    return 0;
}

int outline (Mat &frame, int &low, int &high, Mat &output)
{
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    cv::Mat binaryMat(frame.size(), frame.type());
    cv::threshold(frame, binaryMat, 100, 250, cv::THRESH_BINARY);
    GaussianBlur(frame, frame, Size(7,7), 0.6, 0.6);
    Canny(frame, output, low, high, 3);
    return 0;
}

int colored_outline (Mat &frame, vector<vector<Point> > &contours, vector<Vec4i> &hierarchy, int &low, int &high, Mat &output)
{
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    cv::Mat binaryMat(frame.size(), frame.type());
    cv::threshold(frame, binaryMat, 100, 250, cv::THRESH_BINARY);
    GaussianBlur(frame, frame, Size(7,7), 0.6, 0.6);
    Canny(frame, frame, low, high, 3);
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

int test_function (Mat &frame, Mat&output)
{
    output = frame.clone();
    //blur( frame, output, Size( 30, 30 ), Point(-1,-1) );
    GaussianBlur (frame, output, Size( 7, 7 ), 0, 0);
    
    return 0;
}

int main(int argc, char** argv)
{
    bool preload = false;
    for (int i = 0; i < argc; ++i)
        if (std::strcmp(argv[i], "preload") == 0 or std::strcmp(argv[i], "pre_load") == 0 or std::strcmp(argv[i], "pre") == 0)
            preload = true;
    
    
    
    // GUI Components
    Mat guiframe = Mat(400, 500, CV_8UC3);
    bool contour_bool = false;
    bool colored_contour_bool = false;
    bool test_bool = false;
    
    std::string path = "videos/";
    std::vector<string> filenames;
    std::vector<VideoCapture> videos;
    std::vector<vector<Mat> > frames;
    std::vector<int> lengths;
    int WIDTH = 800, HEIGHT = 600;
    cv::Size disp_size = cv::Size(WIDTH, HEIGHT);
    int frame_count = 0;
    int current_video = 0;
    int canny_low_thresh = 50, canny_high_thresh = 150;
    std::vector<bool> videobools;
    Mat frame, altered;
    
    // define sub-structures
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    
    getdir(path, filenames);
    loadvids(filenames, videos, lengths);
    if(preload)
        decodevids(videos, disp_size, frames);
    int num_videos = videos.size();
    for (int i = 0; i < num_videos; i++){
        videobools.push_back(false);
    }
    videobools[current_video] = true;
    namedWindow("Processed",CV_WINDOW_NORMAL);
    cvui::init("User Control");
    
    while(true){
        if(preload){
            frame = frames.at(current_video).at(frame_count);
            frame_count ++;
            if (frame_count >= lengths[current_video] - 1){
                frame_count = 0;
                continue;
            }
        }
        else{
            videos[current_video] >> frame;
            frame_count ++;
            if (frame_count >= lengths[current_video]){
                videos[current_video].set(CV_CAP_PROP_POS_FRAMES, 0);
                frame_count = 0;
                continue;
            }
            cv::resize(frame, frame,  disp_size);
        }
        //imshow("Original", frame);
        if (contour_bool)
            if (colored_contour_bool)
                colored_outline(frame, contours, hierarchy, canny_low_thresh, canny_high_thresh, altered);
            else
                outline(frame, canny_low_thresh, canny_high_thresh, altered);
        else
            altered = frame;
        if(test_bool)
            test_function(altered, altered);
        imshow("Processed", altered);
        
        // GUI
        guiframe = cv::Scalar(49, 52, 49);
        cvui::beginRow(guiframe, 10, 20, 100, 50, 50);
            cvui::checkbox("contours", &contour_bool);
            cvui::checkbox("colored", &colored_contour_bool);
            if(cvui::button(100, 30, "Next Video"))
                current_video = (current_video + 1) % num_videos;
        cvui::endRow();
        cvui::beginColumn(guiframe, 10, 20, 100, 50, 50);
            cvui::trackbar(guiframe, 15, 110, 165, &canny_low_thresh, 5, 150);
            cvui::trackbar(guiframe, 15, 180, 165, &canny_high_thresh, 80, 300);
        cvui::endColumn();
        cvui::beginRow(guiframe, 10, 50, 100, 50, 50);
            cvui::checkbox("test function", &test_bool);
        cvui::endRow();

        cvui::update();
        cvui::imshow("User Control", guiframe);
        
        
        char c=(char)waitKey(25);
        if(c==27)
            break;
    }
    destroyAllWindows();
    return 0;
}
