#include "objdetect/objdetect.hpp"
#include "imgproc/imgproc.hpp"
using namespace cv;

//http://nashruddin.com/opencv_eye_detection
//http://docs.opencv.org/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
CascadeClassifier face_cascade, eyes_cascade, eyes_cascade2;
String face_cascade_name = "bin/haarcascades/haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "bin/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
String eyes_cascade_name2 = "bin/haarcascades/haarcascade_eye.xml";

class iDetect{
public:
  iDetect(){}
  ~iDetect(){}
};

void detectFace(Mat f){
  std::vector<Rect> faces;
  Mat frame_gray;
  cvtColor( f, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );
  face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( int i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse(f, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 0, 0, 255 ), 2, 8, 0 );

    Mat faceROI = frame_gray( faces[i] );
  }
}


void detectEyes(Mat f){
  std::vector<Rect> faces;
  Mat frame_gray;
  cvtColor( f, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );
  face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( int i = 0; i < faces.size(); i++ )
  {
    Mat faceROI = frame_gray( faces[i] );
    std::vector<Rect> eyes;
    //-- In each face, detect eyes
    eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( int j = 0; j < eyes.size(); j++ )
     {
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( f, center, radius, Scalar(0, 0, 255), 1, 8, 0 );
     }
  }
}

void detectZoomEyes(Mat f){
  Mat RGB_frame;
  cvtColor(f, RGB_frame, CV_HSV2RGB);
  std::vector<Rect> eyes;
  eyes_cascade2.detectMultiScale( RGB_frame, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
for( int j = 0; j < eyes.size(); j++ )
     {
       Point center( eyes[j].x + eyes[j].width*0.5, eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( f, center, radius, Scalar(0, 0, 255), 1, 8, 0 );
     }
  }


  
