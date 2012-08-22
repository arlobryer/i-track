#include "math.h"
#include "detection.hh"
#include "manager.hh"

using namespace cv;

IplImage* GetThresholdImage(IplImage* img){
  IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
  cvCvtColor(img, imgHSV, CV_BGR2HSV);
  IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
  cvInRangeS(imgHSV, Scalar(20, 100, 100), Scalar(30, 255, 255), imgThreshed);
  cvReleaseImage(&imgHSV);
  return imgThreshed;
}

Point2d GetCenter(Mat* im){
  Point2d center(im->cols/2, im->rows/2);
  return center;
}
  



int main(int, char**)
{
  if (!face_cascade.load(face_cascade_name)){
    std::cout<<"Error loading face_cascade"<<std::endl;
    return -1;
  }
  if (!eyes_cascade.load(eyes_cascade_name)){
    std::cout<<"Error loading eyes_cascade"<<std::endl;
    return -1;
  }
  if (!eyes_cascade2.load(eyes_cascade_name2)){
    std::cout<<"Error loading eyes_cascade2"<<std::endl;
    return -1;
  }


    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened()){  // check if we succeeded
      std::cout<<"Failed to open camera! Bailing."<<std::endl;
      return -1;
    }

    Mat *scaled = new Mat();    
    Mat *raw = new Mat(); 
    Mat *frame = new Mat();
    namedWindow("video", 1);
    namedWindow("threshold", 1);
    // namedWindow("zoomed", 1);
    while(true)
    {
        cap >> *frame; // get a new frame from camera
	//cvt syntax:(source, destination, conversion_code)
        cvtColor(*frame, *raw, CV_BGR2HSV);
        // GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        // Canny(edges, edges, 0, 30, 3);
	double zoom  = 7.;
	resize(*raw, *scaled, scaled->size(), zoom, zoom);
	Point2d raw_cent = GetCenter(raw);
	Point2d scale_cent = GetCenter(scaled);
	Point2d pt1(raw->cols/2 - raw->cols/(2*zoom), raw->rows/2 - raw->rows/(2*zoom));
	Point2d pt2(pt1.x + raw->cols/zoom, pt1.y + raw->rows/zoom);
	circle(*frame,                       /* the dest image */
		 raw_cent, 1,      /* center point and radius */
		 cvScalar(0, 0, 255, 0),    /* the color; red */
		 -1, 8, 0);
	// thickness, line type, shift
	rectangle(*frame, pt1, pt2, cvScalar(0, 0, 255, 0), 1, 8, 0);
		  
	Mat roi(*scaled, Rect(scaled->cols/2 - scaled->cols/(2*zoom), scaled->rows/2 - scaled->rows/(2*zoom), raw->cols, raw->rows));
	detectFace(*frame);
	detectEyes(*frame);
	detectZoomEyes(roi);
	moveWindow("video", frame->cols+50, 50);
	imshow("video", *frame);
	imshow("threshold", *raw);
	imshow("zoomed", roi);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
