/**
 *   resize show iamge opencv
 *   created on : Aug 15, 2018
 *     Author: Jing Wang
 **/

// compile: g++ resize_image_opencv.cpp -o resize_image `pkg-config --cflags --libs opencv`

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

VideoCapture cap(0);

void grabVideoFeed(Mat& frame)
{
    if (!cap.isOpened()) cerr << "Issue grabbing camera";
    
    cap.read(frame);
}
void showImageWindow(string filename){
    
    Mat frame = imread(filename, CV_LOAD_IMAGE_COLOR);
    if (!frame.data){
        cout << "Could not open or find the image" << std::endl;
    }
    for(;;)
     {
     // grabVideoFeed(frame);
     
     if (frame.empty()) break;
     
     namedWindow("Main", CV_WINDOW_AUTOSIZE);
     imshow("Main", frame);
     
     if (waitKey(30) >= 0) break;
     }
     
     cap.release();
     destroyAllWindows();
}
int resizeImage(string src, string target, string targetFile){
    Mat imagesrc = imread(src, CV_LOAD_IMAGE_COLOR);
    Mat imagetarget = imread(target, CV_LOAD_IMAGE_COLOR);
    if (!imagesrc.data){
        cout <<  "Could not open or find the source image" << std::endl ;
        return -1;
    }
    if (!imagetarget.data){
        cout <<  "Could not open or find the target image" << std::endl ;
        return -1;
    }
    resize(imagesrc, imagesrc, imagetarget.size());
    imwrite(targetFile, imagesrc);
    return 1;
}
/**
 int main(int argc, const char * argv[])
{
    //showImageWindow("512256.jpg");
    resizeImage("pla.jpg","512256.png","hello.png");
    showImageWindow("hello.png");
    return 0;
}
 **/
