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
    int del = 0;
    Size patternsize(6, 15); //number of centers

    // Get calibration board coordinates
    vector<Point3f> board_points_;
    int n_rows = patternsize.height;
    int n_cols = patternsize.width;
    double spacing = 22 / sqrt(2); // using diag spacing in mm
    board_points_.resize(n_cols * n_rows);
    for (int n = 0; n < board_points_.size(); ++n) {
        int row_n = n / n_cols;
        int col_n = n % n_cols;

        board_points_[n].x = (float) ((2 * col_n + row_n % 2) * spacing);
        board_points_[n].y = (float) (row_n * spacing);
        board_points_[n].z = 0.0;
    }

    // Get image points
    vector<vector<Point3f>> objpoints;
    vector<vector<Point2f>> imgpoints;
    vector<String> filenames;

    // Get all jpg images in folder calibimgs
    cv::glob("/home/nroede/rosproj/cpp_files/circlegrid/calibimgs/*.png", filenames);

    for(int i = 0; i < filenames.size(); i++) {
        Mat img = imread(filenames[i], IMREAD_GRAYSCALE); //source image
        vector<Point2f> centers; //this will be filled by the detected centers
        bool patternfound = findCirclesGrid(img, patternsize, centers, CALIB_CB_ASYMMETRIC_GRID);
        if (!patternfound) {
            string imgname = filenames[i].substr(52);
            string newimg = "/home/nroede/rosproj/cpp_files/circlegrid/calibimgs/badimgs/" + imgname;
            cout << imgname << " moved to badimgs" << endl;
            rename(filenames[i].c_str(), newimg.c_str());
            continue;
        }
//        drawChessboardCorners(img, patternsize, Mat(centers), patternfound);
//        imshow("image", img);
//        waitKey(0);
//        destroyAllWindows();
        objpoints.push_back(board_points_);
        imgpoints.push_back(centers);
    }

    cv::Mat cameraMatrix, distCoeffs, R, T;

    cv::calibrateCamera(objpoints, imgpoints, patternsize, cameraMatrix, distCoeffs, R, T);
    cout << "cameraMatrix : " << cameraMatrix << endl;
    cout << "distCoeffs : " << distCoeffs << endl;
    cout << "Rotation vector : " << R << endl;
    cout << "Translation vector : " << T << endl;
    return 0;
}