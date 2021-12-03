#include <iostream>
#include <cmath>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>


using namespace std;
using namespace Eigen;

/*
    1. 练习Eigen库的Geometry模块；
    2. 练习旋转的表达方式，以及他们之间的变换方式；
*/

int main(int argc, char **argv)
{
    cout.precision(3);
    // 1. 旋转矩阵和旋转向量
    // 1.1 声明 
    Matrix3d rotation_matrix = Matrix3d::Identity();
    AngleAxisd rotation_vector(M_PI / 2, Vector3d(0,0,1));

    cout << "rotation vector =\n" << rotation_vector.matrix() << endl; // 用matrix转换成矩阵
    cout << "-------------------------------------------------------------------" << endl;   

    // 1.2 相互变换
    rotation_matrix = rotation_vector.toRotationMatrix();

    // 1.3 坐标变换
    Vector3d v(1, 0, 0);
    Vector3d v_rotated_v = rotation_vector * v;
    cout << "(1, 0, 0) after rotation by angle axis = " << v_rotated_v.transpose() << endl;
    cout << "-------------------------------------------------------------------" << endl;  

    Vector3d v_rotated_m = rotation_matrix * v;
    cout << "(1, 0, 0) after rotation by matrix = " << v_rotated_m.transpose() << endl;
    cout << "-------------------------------------------------------------------" << endl;  

    // 2. 欧拉角
    Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);
    cout << "yaw pitch roll = " << euler_angles.transpose() << endl;
    cout << "-------------------------------------------------------------------" << endl;  

    // 3. 欧式变换
    Isometry3d T = Isometry3d::Identity();
    T.rotate(rotation_vector);
    T.pretranslate(Vector3d(1, 2, 3));
    cout << "Tranform matrix = \n" << T.matrix() << endl;

    Vector3d v_tranformed = T * v;
    cout << "T * v = " << v_tranformed.transpose() << endl;
    cout << "-------------------------------------------------------------------" << endl;  

    // 4. 放射变换和射影变换，使用Eigen::Affine3d和Eigen::Projective3d，略

    //5. 四元数
    Quaterniond q_v = Quaterniond(rotation_vector);
    cout << "quaternoin from rotation vector = " << q_v.coeffs().transpose() << endl;

    Quaterniond q_r = Quaterniond(rotation_matrix);
    cout << "quaternoin from rotation matrix = " << q_r.coeffs().transpose() << endl;

    Vector3d q_rotated = q_v * v;
    cout << "(1, 0, 0) after rotation by quaternoin = " << q_rotated.transpose() << endl;
    // 使用常规向量乘法表示：
    cout << "Should be equal to " << (q_v * Quaterniond(0,1,0,0) * q_v.inverse()).coeffs().transpose() << endl;
    cout << "-------------------------------------------------------------------" << endl;  
    return 0;
}