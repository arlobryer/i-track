#include "cv.h"
#include "highgui.h"

using namespace cv;

IplImage* GetThresholdImage(IplImage* img){
  IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
  cvCvtColor(img, imgHSV, CV_BGR2HSV);
  IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
  cvInRangeS(imgHSV, Scalar(20, 100, 100), Scalar(30, 255, 255), imgThreshed);
  cvReleaseImage(&imgHSV);
  return imgThreshed;
}


int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges, scale_edges;
    namedWindow("video", 1);
    namedWindow("threshold", 1);
    namedWindow("zoomed", 1);
    while(true)
    {
      Mat frame;
        cap >> frame; // get a new frame from camera
	//cvt syntax:(source, destination, conversion_code)
        cvtColor(frame, edges, CV_BGR2HLS);
        // GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        // Canny(edges, edges, 0, 30, 3);
	resize(edges, scale_edges, scale_edges.size(), 3., 3., INTER_AREA);
	Mat roi = scale_edges(cvRect(50, 50, 360, 360));
	moveWindow("video", frame.cols+50, 50);
	moveWindow("zoomed", 50, frame.rows+50);

	imshow("video", frame);
	imshow("threshold", edges);
	imshow("zoomed", roi);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
