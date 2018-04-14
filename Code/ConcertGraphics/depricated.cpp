#include "opencv2/opencv.hpp"

#define PI 3.1415926

using namespace cv;
using namespace std;


#if ! defined LINE_FINDER
#define LINE_FINDER

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

/*
 NOTES FOR CONTROL SCHEMA
 
 'c' = contours on/off
 'l' = loop on/off
 '=' = longer loop
 '-' = shorter loop
 ' ' = switch to camera/video
 'b' = both videos moving forward or just one
 'w' = switch which video is showing
 
 MODES
 'c' = contours
 'o' = infinite loop
 'v' = masking
 'r' = reset background
 't' = moving background colors
 'o' = off
 
 */

class LineFinder {
private:
    
    // original image
    cv ::Mat img;
    
    // vector containing the end points
    // of the detected lines
    std ::vector< cv::Vec4i > lines;
    
    // accumulator resolution parameters
    double deltaRho;
    double deltaTheta;
    
    // minimum number of votes that a line
    // must receive before being considered
    int minVote;
    
    // min length of a line
    double minLength;
    
    // max allowed gap along the line
    double maxGap;
    
public:
    
    // Default accumulator resolution is 1 pixel by 1 degree
    // no gap, no minimum length
    LineFinder () : deltaRho(1 ), deltaTheta( PI / 180),
    minVote (10), minLength(0. ), maxGap( 0.) {}
    
    // Set the resolution of the accumulator
    void setAccResolution( double dRho, double dTheta ) {
        deltaRho = dRho;
        deltaTheta = dTheta;
    }
    
    // Set the minimum number of votes
    void setMinVote( int minV) {
        minVote = minV;
    }
    
    // Set line length and gap
    void setLineLengthAndGap( double length, double gap ) {
        minLength = length;
        maxGap = gap;
    }
    
    // Apply probabilistic Hough Transform
    std ::vector< cv::Vec4i > findLines( cv::Mat &binary) {
        lines .clear();
        cv ::HoughLinesP( binary, lines ,
                         deltaRho , deltaTheta, minVote, minLength , maxGap);
        
        return lines;
    }
    
    
    // Draw the detected lines on image
    void drawDetectedLines( cv::Mat &image,
                           cv ::Scalar color = cv::Scalar (0, 0, 255)) {
        // Draw the lines
        std ::vector< cv::Vec4i >::const_iterator it2 = lines.begin ();
        
        while ( it2 != lines .end()){
            cv ::Point pt1((* it2)[0 ], (* it2)[1 ]);
            cv ::Point pt2((* it2)[2 ], (* it2)[3 ]);
            cv ::line( image, pt1 , pt2, color);
            ++ it2;
        }
    }
};

#endif

//LINE FINDER CODE END


int main(int, char**)
{
    string filename1 = "maze.mp4";
    string filename2 = "hypercube.mp4";
    string filename3 = "dream.mp4";
    string filename4 = "drugs.mp4";
    string filename5 = "hygene.mp4";
    VideoCapture cap_one(filename1);
    VideoCapture cap_two(filename2);
    VideoCapture cap_three(filename3);
    VideoCapture cam(0);
    bool both = false;
    bool which_vid = 0;
    Mat first_frame;
    cam >> first_frame;
    if(!cam.isOpened())  // check if we succeeded
        return -1;
    
    char mode = 'c';
    bool colored_lines = false;
    bool camera = false;
    bool infinite_loop = false;
    bool completed_loop = false;
    Mat edges;
    namedWindow("pretty",CV_WINDOW_AUTOSIZE);
    //cvSetWindowProperty("edges", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
    int back_red = 0;
    int back_green = 0;
    int back_blue = 0;
    int red_delt = 0;
    int green_delt = 0;
    int blue_delt = 0;
    int red_color = rand() % 256;
    int blue_color = rand() % 256;
    int green_color = rand() % 256;
    Mat stripes;
    int frame_num = 1;
    stripes = imread("stripes.jpg", CV_LOAD_IMAGE_COLOR);
    //if(! stripes.data )                              // Check for invalid input
    //{
    //    cout <<  "Could not open or find the image" << std::endl ;
    //    return -1;
    //}
    
    vector<cv::Mat> previous_frames;
    int loop_length = 3;
    int loop_num = 40;
    bool looped_mode = false;
    
    Mat frame;
    Mat frame2;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    int current_lower_threshold = 30;
    int current_upper_threshold = 15;
    bool rising = true;
    
    double current_blur = 0.6;
    bool high_memory = false;
    bool blur_rising = false;
    bool binaried = true;
    
    double blur_red = (rand() % 15);
    double blur_green = (rand() % 15);
    double blur_blue = (rand() % 15);
    double blur_red_d = (rand() % 5)/5.0 + 0.001;
    double blur_green_d = (rand() % 5)/5.0 + 0.001;
    double blur_blue_d = (rand() % 5)/5.0 + 0.001;
    
    bool colored_back = false;
    
    int vid_num = 1;
    
    bool vid_switch = false;
    int frames_per_seg = 100;
    int current_seg_frame = 1;
    
    for(;;)
    {
        if (vid_switch){
            if (current_seg_frame >= frames_per_seg){
                if (vid_num == 1 || vid_num == 2){
                    frames_per_seg = (rand() % 250) + 50;
                    vid_num = 3;
                    high_memory = true;
                }
                else
                    if (vid_num == 3){
                        high_memory = false;
                        if (rand() % 2 >= 1){
                            frames_per_seg = (rand() % 10) * 6;
                            vid_num = 1;
                        }
                        else{
                            frames_per_seg = (rand() % 10) * 3;
                            vid_num = 2;
                        }
                    }
                current_seg_frame = 1;
            }
        }
        
        if (vid_num == 1){
        int prev_frames = cap_one.get(CV_CAP_PROP_POS_FRAMES);
        cap_one >> frame;
        if(cap_one.get(CV_CAP_PROP_POS_FRAMES) < prev_frames){
            std::cout << "RESTARTING" << endl;
            cap_one = VideoCapture(filename1);
            cap_one >> frame;
        }
        }
        else
            if(vid_num == 2){
                int prev_frames = cap_two.get(CV_CAP_PROP_POS_FRAMES);
                cap_two >> frame;
                if(cap_two.get(CV_CAP_PROP_POS_FRAMES) < prev_frames){
                    std::cout << "RESTARTING" << endl;
                    cap_two = VideoCapture(filename2);
                    cap_two >> frame;
                }
            }
            else
                if(vid_num == 3){
                    int prev_frames = cap_three.get(CV_CAP_PROP_POS_FRAMES);
                    cap_three >> frame;
                    if(cap_three.get(CV_CAP_PROP_POS_FRAMES) < prev_frames){
                        std::cout << "RESTARTING" << endl;
                        cap_three = VideoCapture(filename3);
                        cap_three >> frame;
                    }
                }
        //cv::resize(frame, frame, first_frame.size());
        
        /* FIRST PARTY
         
         frame2 = Mat();
         if (mode != 'o'){
         if (!completed_loop){
         if (!camera){
         if (both){
         if (which_vid == 0){
         cap_one >> frame; // get a new frame from camera
         cap_two >> frame2;
         }
         else{
         cap_two >> frame;
         cap_one >> frame2;
         }
         }
         else{
         cap_one >> frame;
         //if (which_vid == 0)
         //    cap_one >> frame;
         //else
         //    cap_two >> frame;
         }
         }
         else{
         cam >> frame;
         }
         cv::resize(frame, frame, first_frame.size());
         }
         if (looped_mode){
         previous_frames.push_back(frame);
         if (previous_frames.size() > loop_length){
         if (frame_num % (loop_length * loop_num) == 0){
         previous_frames.erase(previous_frames.begin(), previous_frames.end());
         }
         else{
         previous_frames.pop_back();
         frame = previous_frames.at(frame_num%loop_length);
         }
         }
         }
         if (infinite_loop){
         if (completed_loop)
         frame = previous_frames.at(frame_num%loop_length);
         else{
         previous_frames.push_back(frame);
         if (previous_frames.size() > loop_length){
         if (frame_num % (loop_length) == 0){
         completed_loop = true;
         }
         else{
         previous_frames.pop_back();
         frame = previous_frames.at(frame_num%loop_length);
         }
         }}
         }
         
         }*/
        
        
        if (mode == 'o')
            imshow("pretty", Mat(first_frame.rows, first_frame.cols, CV_8UC3, Scalar(0,0,0)));
        else
            if (mode =='c'){
                cvtColor(frame, edges, COLOR_BGR2GRAY);
                
                //Binary image
                cv::Mat binaryMat(edges.size(), edges.type());
                //Apply thresholding
                
                if(high_memory){
                    if (binaried)
                        cv::threshold(edges, binaryMat, 100, 250, cv::THRESH_BINARY);
                    else{
                        cv::threshold(edges, edges, 100, 250, cv::THRESH_BINARY);
                    }
                    GaussianBlur(edges, edges, Size(7,7), current_blur, current_blur);
                    
                    double amount = 0.05;
                    if (current_blur < 0.8){
                        if (rand() % (current_lower_threshold * 20) < (current_lower_threshold * 20) - 3)
                            amount = 0.05;
                        else
                            amount = 0;
                    }
                    if (blur_rising)
                        current_blur += amount;
                    else
                        current_blur -= amount;
                    if (current_blur >= 0.8 || current_blur <= 0.1){
                        if(current_blur <= 0.1)
                            current_blur = 0.1;
                        if(current_blur >= 0.8)
                            current_blur = 0.8;
                        blur_rising = !blur_rising;
                    }
                    cvtColor(edges, edges, COLOR_GRAY2BGR);
                    if (colored_back){
                    if (blur_red > 255 || blur_red < 0){
                        blur_red_d *= -1;
                    }
                    if (blur_blue > 255 || blur_blue < 0){
                        blur_blue_d *= -1;
                    }
                    if (blur_green > 255 || blur_green < 0){
                        blur_green_d *= -1;
                    }
                    blur_red += blur_red_d;
                    blur_green += blur_green_d;
                    blur_blue += blur_blue_d;
                    for(int y=0;y<edges.rows;y++)
                    {
                        for(int x=0;x<edges.cols;x++)
                        {
                            // get pixel
                            Vec3b color = edges.at<Vec3b>(Point(x,y));
                            
                            // ... do something to the color ....
                            color(0) += blur_red;
                            color(1) += blur_green;
                            color(2) += blur_blue;
                            
                            // set pixel
                            edges.at<Vec3b>(Point(x,y)) = color;
                        }
                    }
                    }
                    cv::resize(edges, edges, first_frame.size());
                    imshow("pretty", edges);
                }
                else{
                    cv::threshold(edges, binaryMat, 100, 250, cv::THRESH_BINARY);
                    GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
                    Canny(edges, edges, current_lower_threshold, current_lower_threshold * 2, 3);
                    int amount = 1;
                    if (frame_num %3 == 0){
                        if (current_lower_threshold < 40){
                            if (rand() % current_lower_threshold < current_lower_threshold - 3)
                                amount = 1;
                            else
                                amount = 0;
                        }
                        if (rising)
                            current_lower_threshold += amount;
                        else
                            current_lower_threshold -= amount;
                        if (current_lower_threshold >= 125 || current_lower_threshold <= 4){
                            if (current_lower_threshold <= 4)
                                current_lower_threshold = 4;
                            rising = !rising;
                        }
                    }
                    
                    findContours(edges, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, Point(0,0));
                    Mat colored_edges(frame.rows, frame.cols, CV_8UC3, Scalar(back_red,back_green,back_blue));
                    back_red += red_delt;
                    back_green += green_delt;
                    back_blue += blue_delt;
                    if (back_red > 255 or back_red < 0)
                        red_delt *= -1;
                    if (back_green > 255 or back_green < 0)
                        green_delt *= -1;
                    if (back_blue > 255 or back_blue < 0)
                        blue_delt *= -1;
                    
                    if (colored_lines){
                        
                        red_color = rand() % 256;
                        blue_color = rand() % 256;
                        green_color = rand() % 256;
                        int mult = rand() % 2 + 3;
                        for (unsigned int i=0; i<contours.size(); i++){
                            if (hierarchy[i][3] < 0){
                                double area0 = arcLength(contours[i], false);
                                if (area0 > 500)
                                    //drawContours(colored_edges, contours, i, Scalar(255), 1, 8);
                                    drawContours(colored_edges, contours, i, Scalar(green_color, blue_color+i*mult,red_color), 1, 8);
                                else
                                    drawContours(colored_edges, contours, i, Scalar(green_color, blue_color+i*mult, red_color), 1, 8);
                            }
                        }
                    }
                    else{
                        for (unsigned int i=0; i<contours.size(); i++){
                            if (hierarchy[i][3] < 0){
                                drawContours(colored_edges, contours, i, Scalar(255,255,255), 1, 8);
                            }
                        }
                    }
                    cv::resize(colored_edges, colored_edges, first_frame.size());
                    imshow("pretty", colored_edges);
                }
            }
            else
                if (mode == 'z'){
                    cvtColor(frame, edges, COLOR_BGR2GRAY);
                    
                    //Binary image
                    cv::Mat binaryMat(edges.size(), edges.type());
                    cv::threshold(edges, binaryMat, 100, 250, cv::THRESH_BINARY);
                    // Create a kernel that we will use for accuting/sharpening our image
                    Mat kernel = (Mat_<float>(3,3) <<
                                  1,  1, 1,
                                  1, -8, 1,
                                  1,  1, 1); // an approximation of second derivative, a quite strong kernel
                    // do the laplacian filtering as it is
                    // well, we need to convert everything in something more deeper then CV_8U
                    // because the kernel has some negative values,
                    // and we can expect in general to have a Laplacian image with negative values
                    // BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
                    // so the possible negative number will be truncated
                    Mat imgLaplacian;
                    Mat sharp = frame; // copy source image to another temporary one
                    filter2D(sharp, imgLaplacian, CV_32F, kernel);
                    frame.convertTo(sharp, CV_32F);
                    Mat imgResult = sharp - imgLaplacian;
                    // convert back to 8bits gray scale
                    imgResult.convertTo(imgResult, CV_8UC3);
                    // imshow( "Laplace Filtered Image", imgLaplacian );
                    frame = imgResult; // copy back
                    // Create binary image from source image
                    sharp = Mat();
                    cvtColor(frame, sharp, CV_BGR2GRAY);
                    threshold(sharp, sharp, 40, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
                    // Perform the distance transform algorithm
                    distanceTransform(sharp, sharp, CV_DIST_L2, 3);
                    // Normalize the distance image for range = {0.0, 1.0}
                    // so we can visualize and threshold it
                    normalize(sharp, sharp, 0, 1., NORM_MINMAX);
                    
                    cv::resize(sharp, sharp, first_frame.size());
                    imshow("pretty", sharp);
                }
        
        char key = waitKey(1);
        if (key == 'h')
            vid_switch = !vid_switch;
        if (key == 'f')
            binaried = !binaried;
        if (key == 'g'){
            blur_red_d = (rand() % 5)/5.0 + 0.001;
            blur_green_d = (rand() % 5)/5.0 + 0.001;
            blur_blue_d = (rand() % 5)/5.0 + 0.001;
            colored_back = !colored_back;
        }
        if (key == 'z'){
            if (mode == 'z')
                mode = 'c';
            else
                mode = 'z';
        }
        if (key == '1'){
            vid_num = 1;
            high_memory = false;
            cap_one = VideoCapture(filename1);
        }
        if (key == '2'){
            vid_num = 2;
            high_memory = false;
            cap_one = VideoCapture(filename2);
        }
        if (key == '3'){
            vid_num = 3;
            cap_one = VideoCapture(filename3);
            high_memory = true;
        }
        if (key == '4'){
            cap_one = VideoCapture(filename4);
        }
        if (key == '5'){
            cap_one = VideoCapture(filename5);
        }
        if (key == ' '){
            camera = !camera;
        }
        if (key == 'b' and !camera){
            both = !both;
        }
        if (key == 'w' and !camera){
            which_vid = (which_vid + 1) % 2;
        }
        if (key == '='){
            if (!looped_mode){
                loop_length += 1;
            }
        }
        if (key == '-'){
            if (!looped_mode){
                if (loop_length > 2)
                    loop_length -= 1;
            }
        }
        if (key == 'l'){
            previous_frames.erase(previous_frames.begin(), previous_frames.end());
            looped_mode = !looped_mode;
        }
        if (key == 'o'){
            infinite_loop = !infinite_loop;
            completed_loop = false;
            previous_frames.erase(previous_frames.begin(), previous_frames.end());
        }
        if (key == 'c'){
            if (mode == 'c')
                mode = 'o';
            else
                if (mode == 'o')
                    mode = 'c';
        }
        if (key == 'v' and !camera){
            if (mode == 'v'){
                back_red = 0;
                back_green = 0;
                back_blue = 0;
                red_delt = 0;
                blue_delt = 0;
                green_delt = 0;
                colored_lines = false;
                mode = 'c';
            }
            else{
                back_red = rand() % 50;
                back_green = rand() % 50;
                back_blue = rand() % 50;
                red_delt = rand() % 5+1;
                green_delt = rand() % 5+1;
                blue_delt = rand() % 5+1;
                colored_lines = false;
                mode = 'v';
            }
        }
        if (mode == 'c'){
            if(key == 'r'){
                back_red = 0;
                back_green = 0;
                back_blue = 0;
            }
            if(key == 't'){
                if (red_delt > 0 and green_delt > 0 and blue_delt > 0){
                    red_delt = 0;
                    blue_delt = 0;
                    green_delt = 0;
                    back_red = 0;
                    back_green = 0;
                    back_blue = 0;
                }
                else{
                    back_red = rand() % 50;
                    back_green = rand() % 50;
                    back_blue = rand() % 50;
                    red_delt = rand() % 5+1;
                    green_delt = rand() % 5+1;
                    blue_delt = rand() % 5+1;
                }
            }
        }
        if(key == 'e'){
            colored_lines = !colored_lines;
        }
        if(key == 27) break;
        frame_num++;
        current_seg_frame++;
        
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}