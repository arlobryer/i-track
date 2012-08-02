#include "objdetect/objdetect.hpp"
#include "imgproc/imgproc.hpp"
using namespace cv;

//http://nashruddin.com/opencv_eye_detection
//http://docs.opencv.org/doc/tutorials/objdetect/cascade_classifier/cascade_classifier.html
CascadeClassifier face_cascade, eyes_cascade;
String face_cascade_name = "bin/haarcascades/haarcascade_frontalface_alt.xml";


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
