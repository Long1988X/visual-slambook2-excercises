#include <iostream>
#include <ctime>
#include "eigen3/Eigen/Core"
#include "eigen3/Eigen/Dense"
// #include "eigen3/Eigen/Geometry"   

using namespace std;

/*********  练习Eigen库的使用 ********/

int main(int argc, char **argv)
{
    // 1.声明向量和矩阵
    // 1.1 使用Eigen::Matrix模板类声明向量和矩阵
    Eigen::Matrix<float, 2, 3> matrix_23f;
    Eigen::Matrix<float, 3, 1> matrix_31f;

    // 1.2 使用Eigen内置类型声明三维向量和三维矩阵
    Eigen::Matrix3d matrix33d = Eigen::Matrix3d::Zero();
    Eigen::Vector3d v_3d;
    
    // 1.3 声明动态矩阵
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;
    Eigen::MatrixXd matrix_x; 


    // 2.基本操作
    // 2.1 初始化
    matrix33d = Eigen::Matrix3d::Random();
    cout << "random matrix:\n" << matrix33d << endl;

    matrix33d.setConstant(5.5);
    cout << "const matrix:\n" << matrix33d << endl;

    matrix33d.setZero();
    cout << "zero matrix:\n" << matrix33d << endl;

    matrix33d.row(0) << 1, 2, 3;
    matrix33d.row(1) << 6, 5 , 4;
    cout << "row matrix:\n" << matrix33d << endl;    
    // 2.2 访问矩阵元素，使用（）
    v_3d.setZero();
    v_3d(1,0) = 2;
    cout << "() v_3d:\n" << v_3d << endl;
    
    // 3.矩阵、向量运算
    // 3.1 矩阵*向量
    matrix33d.setConstant(2);
    v_3d.setIdentity();
    Eigen::Vector3d v_r = matrix33d * v_3d;
    cout << "matrix * vector:\n" << v_r << endl;

    // 3.2 转置、迹、行列式、逆、数乘
    matrix33d = Eigen::Matrix3d::Random();
    cout << "matrix m:\n" << matrix33d << endl;
    cout << "matrix transpose:\n" << matrix33d.transpose() << endl;
    cout << "matrix trace:\n" << matrix33d.trace() << endl;
    cout << "matrix inverse:\n" << matrix33d.inverse() << endl;
    cout << "k * matrix:\n" << matrix33d * 10 << endl;

    // 3.3 向量内积、外积运算
    Eigen::Vector3d v(1,2,3);
    Eigen::Vector3d w(0,1,2);
    cout << "Dot product:\n" << v.dot(w) << endl;
    cout << "Cross product:\n" << v.cross(w) << endl;

    // 4.特征值、特征向量
    matrix33d.setRandom();
    Eigen::Matrix3d A = matrix33d + matrix33d.transpose(); 
    cout << "random symmetric matrix:\n" << A << endl;

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(A);
    cout << "The eigenvalues of A are:\n" << es.eigenvalues() << endl;
    cout << "The eigenvectors of A are:\n" << es.eigenvectors() << endl;
    Eigen::MatrixXd D = es.eigenvalues().asDiagonal();
    Eigen::MatrixXd V = es.eigenvectors();
    cout << "Finally, V * D * V^(-1):\n" << V*D*V.inverse() << endl;

    // 5. exercise 5 
    Eigen::Matrix<double, 10, 10> matrixnn;
    matrixnn.setRandom();
    cout << "matrixnn is \n" << matrixnn << endl;

    Eigen::Matrix3d matrix33 = Eigen::Matrix3d::Random();
    matrix33 = matrixnn.block(0,0,3,3);
    matrix33 = Eigen::Matrix3d::Identity();

    cout << "matrixnn with identity33 is \n" << matrixnn << endl;

    
    
    return 0;
}