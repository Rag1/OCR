#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;
int main(int argc, char *argv[])
{
    Mat box = imread(".png",1);
    MSER ms;
    vector<vector<Point> > regions;
    ms(box, regions, Mat());
    for (int i = 0; i < regions.size(); i++)
    {
        ellipse(box, fitEllipse(regions[i]), Scalar(255));
    }
    imshow("mser", box);
    waitKey(0);
    return 0;
}
