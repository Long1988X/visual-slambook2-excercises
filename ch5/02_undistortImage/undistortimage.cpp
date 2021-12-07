#include <iostream>
#include <string>
#include <chrono>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;

string image_file = "../distorted.png";

int main(int argc, char **argv)
{
    // 相机内参和畸变参数
    double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;
    double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;

    // read distorted image
    Mat image_distorted = imread(image_file, 0);
    int rows = image_distorted.rows, cols = image_distorted.cols;
    Mat image_undistorted = Mat(rows, cols, CV_8UC1);
    Mat opencv_image = Mat(rows, cols, CV_8UC1);


    // 1. 手写去畸变
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for (size_t v = 0; v < rows; v++) {
        for (size_t u = 0; u < cols; u++) {
            // 计算归一化平面上的x，y
            double x = (u - cx) / fx, y = (v - cy) / fy;
            double r = sqrt(x * x + y * y);
            // 计算畸变后正确的归一化坐标x_distorted, y_distorted
            double x_distorted = x * (1 + k1 * r * r + k2 * r * r * r * r) + 2 * p1 * x * y + p2 * (r * r + 2 * x * x);
            double y_distorted = y * (1 + k1 * r * r + k2 * r * r * r * r) + p1 * (r * r + 2 * y * y) + 2 * p2 * x * y;

            double u_distorted = fx * x_distorted + cx;
            double v_distorted = fy * y_distorted + cy;

            if (u_distorted >= 0 && u_distorted < cols && v_distorted >= 0 && v_distorted < rows) {
                image_undistorted.at<uchar>(v, u) = image_distorted.at<uchar>((int)v_distorted, (int)u_distorted);

            } else {
                image_undistorted.at<uchar>(v, u) = 255;
            }

        }
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double> >(t2 - t1);

    cout << "my undistorted process used time: " << time_used.count() << " s." << endl;


    // 2. Opencv自带函数undistort()
    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);

    //内参矩阵, 就算复制代码，也不要用我的参数。摄像头都不一样...
    cameraMatrix.at<double>(0, 0) = 458.654;
    cameraMatrix.at<double>(0, 1) = 0;
    cameraMatrix.at<double>(0, 2) = 367.215;
    cameraMatrix.at<double>(1, 1) = 457.296;
    cameraMatrix.at<double>(1, 2) = 248.375;
    //畸变参数，不要用我的参数~
    Mat distCoeffs = Mat::zeros(5, 1, CV_64F);
    distCoeffs.at<double>(0, 0) = -0.28340811;
    distCoeffs.at<double>(1, 0) = 0.07395907;
    distCoeffs.at<double>(2, 0) = 0;
    distCoeffs.at<double>(3, 0) = 0.00019359;
    distCoeffs.at<double>(4, 0) = 1.76187114e-05;

    t1 = chrono::steady_clock::now();
    undistort(image_distorted, opencv_image, cameraMatrix, distCoeffs);
    t2 = chrono::steady_clock::now();
    time_used = chrono::duration_cast<chrono::duration<double> >(t2 - t1);

    cout << "opencv undistorted process used time: " << time_used.count() << " s." << endl;

    imshow("distorted image", image_distorted);
    imshow("undistorted image", image_undistorted);
    imshow("opencv image", opencv_image);
    waitKey(0);

    return 0;
}