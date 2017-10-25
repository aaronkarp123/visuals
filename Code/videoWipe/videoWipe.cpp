#include "opencv2/opencv.hpp"

#define PI 3.1415926

using namespace cv;
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>



/*
 ---------------- DIAGRAM ---------------
 ---------a--------|    a->
 b-----------------|    b->
*/

Mat combine_images(Mat image1, Mat image2, Mat image3, int num_to_copy, int dir){
    enum direction {UP=0, DOWN=1, LEFT=2, RIGHT=3};
    int height = image1.rows;
    int width = image1.cols;
    switch(dir) {
        case UP: image1.rowRange(num_to_copy, height).copyTo(image3.rowRange(num_to_copy, height));
        case DOWN: image1.rowRange(num_to_copy, height).copyTo(image3.rowRange(num_to_copy, height));
    }
    return image3;
}



int main(int, char**)
{
    
    String filename = "video";
    int WIDTH=800, HEIGHT = 600;
    int BPM=20;  // probably halve this
    
    VideoCapture cap("lemonade_4.mov"); //("rocket.mp4"); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    
    float fps = cap.get(CV_CAP_PROP_FPS); // framerate of the video
    float loop_length_f = fps * 1/((float)BPM / 60.0); // length of loop in # of frames
    cout << loop_length_f << endl;
    int loop_length = int(loop_length_f + 0.5);
    float rows_per_frame = WIDTH/(float)loop_length; // # of rows to adjust on each run of the main loop
    float cols_per_frame = HEIGHT/(float)loop_length; // # of cols to adjust on each run of the main loop
    
    namedWindow(filename,1);
    Mat frame1, frame2, composite;
    vector<cv::Mat> previous_frames;
    bool first_iteration = true;
    int frame_num = 0;
    int rows_to_copy;
    int loop_num = 0;
    enum direction {UP=0, DOWN=1, LEFT=2, RIGHT=3};
    int facing = 0;
    
    cout << "Welcome! Press 'Esc' to exit.\n" << endl;
    cout << "fps = " << fps << endl;
    cout << "BPM = " << BPM << endl;
    cout << "Video Size = " << WIDTH << " x " << HEIGHT << endl;
    
    for(;;)
    {
        
        frame_num ++;
        if (frame_num % loop_length == 0){
            loop_num ++;
        }
        
        if (loop_num == 0){ // if you haven't completed the first-half loop yet
            cap >> frame1; // get a new frame from camera
            cv::resize(frame1, frame1, cv::Size(WIDTH, HEIGHT));
            previous_frames.push_back(frame1);
            composite = frame1;
        }
        
        else if (loop_num == 1){ // if you haven't completed the 2nd-half loop yet
            cap >> frame1;  // frame1 = previous_frames.at((frame_num + loop_length) % (loop_length * 2));
            cv::resize(frame1, frame1, cv::Size(WIDTH, HEIGHT));
            previous_frames.push_back(frame1);
            frame2 = previous_frames.at(frame_num % (loop_length));
            rows_to_copy = min((int)((rows_per_frame * (frame_num % loop_length))), HEIGHT - 1);
            rows_to_copy = HEIGHT - rows_to_copy - 1;
            if (loop_num % 2 == 1)
                composite = combine_images(frame2, frame1, frame1, rows_to_copy, facing);
            else
                composite = combine_images(frame1, frame2, frame2, rows_to_copy, facing);
        }
        
        else{ // if you have completed the first full loop
            rows_to_copy = min((int)((rows_per_frame * (frame_num % loop_length))), HEIGHT - 1);
            rows_to_copy = HEIGHT - rows_to_copy - 1;
            frame2 = previous_frames.at(frame_num % (loop_length * 2 - 1));
            frame1 = previous_frames.at((frame_num + loop_length) % (loop_length * 2 - 1));
            if (loop_num % 2 == 0)
                composite = combine_images(frame2, frame1, frame1, rows_to_copy, facing);
            else
                composite = combine_images(frame1, frame2, frame2, rows_to_copy, facing);
        }
        
        imshow(filename, composite);
        
        char key = waitKey(30);
        
        if(key == 27) break;
    }
    
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
