#include <iostream>
#include <cmath>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <sophus/se3.hpp>

using namespace std;
using namespace Eigen;


int main(int argc, char **argv)
{
    cout.precision(3);
    // 1. 旋转矩阵、旋转向量、四元数
    Matrix3d rotation_matrix = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).toRotationMatrix();
    Quaterniond q(rotation_matrix);

    cout << "rotation matrix is\n" << rotation_matrix << endl;
    cout << "quaternion q is " << q.coeffs().transpose() << endl;
    cout << "----------------------------------------------------------------" << endl;
    // 2. SO(3)
    // 2.1 对象构建
    Sophus::SO3d SO3_R(rotation_matrix);
    Sophus::SO3d SO3_q(q);

    cout << "SO(3) from matrix:\n" << SO3_R.matrix() << endl;
    cout << "SO(3) from quaternoin:\n" << SO3_q.matrix() << endl;
    cout << "----------------------------------------------------------------" << endl;
    // 2.2 李代数so(3)
    Vector3d so3 = SO3_R.log();
    cout << "so3 = " << so3.transpose() << endl;
    cout << "so3 hat =\n" << Sophus::SO3d::hat(so3) << endl;
    cout << "so3 hat vee =\n" << Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose() << endl;
    cout << "----------------------------------------------------------------" << endl;
    // 2.3 增量扰动模型的更新
    Vector3d update_so3(1e-3, 0, 0);
    Sophus::SO3d SO3_l_updated = Sophus::SO3d::exp(update_so3) * SO3_R;
    Sophus::SO3d SO3_r_updated = SO3_R * Sophus::SO3d::exp(update_so3);
    cout << "left SO3 updated =\n" << SO3_l_updated.matrix() << endl;
    cout << "right SO3 updated =\n" << SO3_r_updated.matrix() << endl;
    cout << "----------------------------------------------------------------" << endl;


    // 3. SE(3)
    // 3.1 对象构造
    Vector3d t(1, 0, 0);
    Sophus::SE3d SE3_Rt(rotation_matrix, t);
    Sophus::SE3d SE3_qt(q, t);
    cout << "SE(3) from R,t = \n" << SE3_Rt.matrix() << endl; 
    cout << "SE(3) from q,t = \n" << SE3_qt.matrix() << endl; 
    cout << "----------------------------------------------------------------" << endl;
    // 3.2 李代数se(3)
    typedef Matrix<double, 6, 1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout << "se(3) = " << se3.transpose() << endl;
    cout << "se3 hat =\n" << Sophus::SE3d::hat(se3) << endl;
    cout << "se3 hat vee = " << Sophus::SE3d::vee(Sophus::SE3d::hat(se3)).transpose() << endl;
    cout << "----------------------------------------------------------------" << endl;
    // 3.3 增量扰动模型的更新
    Vector6d update_se3;
    update_se3.setZero();
    update_se3(0, 0) = 1e-4d;
    Sophus::SE3d SE3_updated = Sophus::SE3d::exp(update_se3) * SE3_Rt;
    cout << "SE3 updated = \n" << SE3_updated.matrix() << endl;
    return 0;
}