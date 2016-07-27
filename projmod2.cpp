#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;

int main()
{
  int r,s;
  Point p,q;
  Mat img=imread("5.jpg",CV_8UC3);
  Mat mserOutMask(img.size(),CV_8UC1,Scalar(0));
  Ptr<MSER> mserExtractor  = MSER::create();

  vector<vector<Point> > mserContours;
  vector<KeyPoint> mserKeypoint;
  vector<Rect> mserBbox;
  mserExtractor->detectRegions(img, mserContours,  mserBbox);

  for (int i=0; i<mserContours.size(); ++i){
      for (int j=0; j<mserContours[i].size(); ++j){
        Point p =  mserContours[i][j];
          // cout << p.x << ", " << p.y << endl;
          mserOutMask.at<uchar>(p.y, p.x) = 255;
      }
  }
  imshow("",mserOutMask);
  Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    threshold(mserOutMask, threshold_output, 100, 255, THRESH_BINARY );
  imshow(" ",threshold_output);
    findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    vector<vector<Point> > contours_poly( contours.size() );
    vector<Rect> boundRect( contours.size() );
    for( size_t i = 0; i < contours.size(); i++ )
       { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
         boundRect[i] = boundingRect( Mat(contours_poly[i]) );
       }
       for( size_t i = 0; i < contours.size(); i++ )
          {
            rectangle(img,boundRect[i],Scalar(0,0,0),1,8,0);
          }

  imshow("mser", img);
waitKey(0);
  return 0;
}
