#include <iostream>
#include <chrono>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

string image_file = "../jinan.png";

int main(int argc, char **argv)
{
    // if (argc != 2) {
    //     cout << "Arguement Error! Usage: ./ok path..." << endl;
    //     return 1;
    // }

    // 1. 读取argv[1]指定的图像
    Mat image = imread(image_file);

    // 判断图像是否正确读取
    if (image.data == nullptr) {
        cerr << "Image " << argv[1] << " is not exist!" << endl;
        return 2;
    }

    // 输出文件基本信息
    cout << "图像宽为：" << image.cols << " ，高为：" << image.rows << " ，通道数：" << image.channels() << endl;

    // 2. 显示图片
    imshow("jinan station", image);
    waitKey(0);

    // 判断image的类型
    if (image.type() != CV_8UC1 && image.type() != CV_8UC3) {
        cout << "Please read a color pic or gray pic!" << endl;
        return 3;
    }
    

    // 3. 遍历图像
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for (size_t y = 0; y < image.rows; y++) {
        unsigned char *row_ptr = image.ptr<uchar>(y);
        for (size_t x = 0; x < image.cols; x++) {
            unsigned char *data_ptr = &row_ptr[x * image.channels()];

            for (size_t c = 0; c != image.channels(); c++) {
                unsigned char data = data_ptr[c];
            }
        }
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double> >(t2 - t1);
    // CMAKE_BUILD_TYPE Release模式会快很多
    cout << "遍历图像用时： " << time_used.count() << " 秒" << endl;


    return 0;
}