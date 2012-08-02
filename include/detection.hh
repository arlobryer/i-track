#include "objdetect/objdetect.hpp"
#include "imgproc/imgproc.hpp"
using namespace cv;

//http://nashruddin.com/opencv_eye_detection
//http://docs.opencv.org/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
CascadeClassifier face_cascade, eyes_cascade;
String face_cascade_name = "bin/haarcascades/haarcascade_frontalface_alt.xml";

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


// bool findEyes(IplImage* img){
//   CvSeq *faces = cvHaarDetectObject(
// 				    img, 
// 				    cascade_f,
// 				    storage,
// 				    1.1, 3, 0,
// 				    cvSize(40, 40)
// 				    );
//   if (faces->total == 0){
//     return true;
//   }
// }
