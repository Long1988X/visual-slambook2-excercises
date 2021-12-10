#include <iostream>
#include <vector>
#include <chrono>

#include <opencv2/opencv.hpp>
#include <ceres/ceres.h>

using namespace std;

// 1. 代价函数计算模型
struct CURVE_FITTING_COST {
    CURVE_FITTING_COST(double x, double y) : _x(x), _y(y) { }

    template <typename T>
    bool operator() (const T* const abc, T* residual) const {
        residual[0] = T(_y) - ceres::exp(abc[0] * T(_x) * T(_x) + abc[1] * T(_x) + abc[2]);
        return true;
    }

    const double _x;
    const double _y;
};

int main(int argc, char **argv)
{
    double ar = 1.0, br = 2.0, cr = 1.0;
    double ae = 2.0, be = -1.0, ce = 5.0;
    // 数据点数量
    int data_nums = 100;
    // 迭代次数
    int iterations = 1000;

    // 噪声sigma值
    double w_sigma = 1.0;
    double inv_sigama = 1.0 / w_sigma;

    // OpenCV随机数生成器
    cv::RNG rng;

    vector<double> x_data, y_data;
    for (size_t i = 0; i < data_nums; i++) {
        double x = i / 100.0;
        x_data.push_back(x);
        y_data.push_back(ceres::exp(ar * x * x + br *x + cr) + rng.gaussian(w_sigma * w_sigma)); 
    }

    double abc[3] = {ae, be, ce};

    // 2. 构建最小二乘
    ceres::Problem problem;
    for (size_t i = 0; i < data_nums; i++) {
        ceres::CostFunction* cost_function = new ceres::AutoDiffCostFunction<CURVE_FITTING_COST, 1, 3>(new CURVE_FITTING_COST(x_data[i], y_data[i]));
        problem.AddResidualBlock(cost_function, nullptr, abc);
    }

    // 3. 配置求解器
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_NORMAL_CHOLESKY;
    options.minimizer_progress_to_stdout = true;

    ceres::Solver::Summary summary;
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    ceres::Solve(options, &problem, &summary);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>> (t2 - t1);
    cout << summary.BriefReport() << endl;
    cout << "Ceres curve fitting time cost : " << time_used.count() << " seconds." << endl;
    cout << "estimated parameters: ";
    for (auto p:abc) {
        cout << p << " ";        
    }
    cout << endl;

    return 0;
}