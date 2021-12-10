#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <chrono>

#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;
using namespace cv;

int main(int argc, char **argv)
{
    double ar = 1.0, br = 2.0, cr = 1.0;
    double ae = 1.1, be = 2.1, ce = 1.1;
    // 数据点数量
    int data_nums = 1000;
    // 迭代次数
    int iterations = 100;

    // 噪声sigma值
    double w_sigma = 1.0;
    double inv_sigama = 1.0 / w_sigma;

    // OpenCV随机数生成器
    RNG rng;

    ofstream ofs("data.txt");

    vector<double> x_data, y_data;
    for (size_t i = 0; i < data_nums; i++) {
        double x = i / 100.0;
        x_data.push_back(x);
        y_data.push_back(exp(ar * x * x + br *x + cr) + rng.gaussian(w_sigma * w_sigma)); 

        // !!!注意y的取值范围不要大于数据类型double的取值范围，否则拟合会不正确！
        ofs << x << " " << (exp(ar * x * x + br *x + cr) + rng.gaussian(w_sigma * w_sigma)) << endl;
    }
    double cost = 0, lastcost = 0;

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for (size_t iter = 0; iter < iterations; iter++) {
        Matrix3d H = Matrix3d::Zero();
        Vector3d g = Vector3d::Zero();
        cost = 0;

        for (size_t i = 0; i < data_nums; i++) {
            double xi = x_data[i], yi = y_data[i];
            double error = yi - exp(ae * xi * xi + be * xi + ce);

            Vector3d J;
            J[0] = -xi * xi * exp(ae * xi * xi + be * xi + ce);
            J[1] = -xi * exp(ae * xi * xi + be * xi + ce);
            J[2] = -exp(ae * xi * xi + be * xi + ce);

            H += J * J.transpose();
            g += -J * error;

            cost += error * error;
        }

        Vector3d dx = H.ldlt().solve(g);

        if (isnan(dx[0])) {
            cout << "result is nan!" << endl;
            break;
        }

        if (iter > 0 && cost >= lastcost) {
            cout << "cost: "  << cost << ">= lastcost: " << lastcost << " , break." << endl;
            break;
        }

        ae += dx[0];
        be += dx[1];
        ce += dx[2];

        lastcost = cost;

        cout << "total cost:" << cost << ", \t\tupdate:" << dx.transpose() << "\t\testimated parameters: " << ae <<", " << be <<", " << ce << endl;
        
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "solve time cost = " << time_used.count() << " seconds." << endl;
    cout << "estimated parameters: " << ae <<", " << be <<", " << ce << endl;

    return 0;
}