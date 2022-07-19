// Finds circle centers on the asymmetrical circle calibration board and draws lines between them

#include <vector>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Size patternsize(6, 15); //number of centers
    Mat gray = imread("calibcircles_1.tiff"); //source image
    vector<Point2f> centers; //this will be filled by the detected centers
    bool patternfound = findCirclesGrid(gray, patternsize, centers, CALIB_CB_ASYMMETRIC_GRID);
    drawChessboardCorners(gray, patternsize, Mat(centers), patternfound);
    imshow("image", gray);
    waitKey(0);
    destroyAllWindows();
    return 0;
}