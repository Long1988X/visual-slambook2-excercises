#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <vector>

#include <pangolin/pangolin.h>
#include <Eigen/Core>
#include <Eigen/Dense>



using namespace std;
using namespace Eigen;


string trajectory_file = "../trajectory.txt";  // 注意：相对路径请将外部构建目录作为当前路径，而不是源代码路径！

typedef vector<Isometry3d, Eigen::aligned_allocator<Isometry3d> > pose_Type;

void DrawTrajectory(pose_Type poses);


int main(int argc, char **argv)
{
    pose_Type poses;

    ifstream fin(trajectory_file);
    if (!fin) {
        cout << trajectory_file << " is open failed............." << endl;
        return 1;
    }

    while (!fin.eof()) {
        double time, tx, ty, tz, qx, qy, qz, qw;
        fin >> time >> tx >> ty >> tz >> qx >> qy >> qz >> qw;

        Isometry3d Twr(Quaterniond(qw, qx, qy, qz));
        Twr.pretranslate(Vector3d(tx, ty, tz));
        poses.push_back(Twr);
    
    }
    cout << "read total " << poses.size() << " pose entries." << endl;

    DrawTrajectory(poses);
    
    return 0;
}

void DrawTrajectory(pose_Type poses)
{
    if (poses.empty()) {
        cerr << "Trajectory is empty!" << endl;
        return;
    }

    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));

    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glLineWidth(2);

        for (size_t i = 0; i < poses.size(); i++) {
        // 画每个位姿的三个坐标轴
        Vector3d Ow = poses[i].translation();  // 获取欧式变换的t
        Vector3d Xw = poses[i] * (0.1 * Vector3d(1, 0, 0)); // 获取世界坐标系的x单位向量经过欧式变换T后，点的位置；0.1表示旋转后相机x轴长度显示0.1倍
        Vector3d Yw = poses[i] * (0.1 * Vector3d(0, 1, 0));
        Vector3d Zw = poses[i] * (0.1 * Vector3d(0, 0, 1));
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3d(Ow[0], Ow[1], Ow[2]);
        glVertex3d(Xw[0], Xw[1], Xw[2]);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3d(Ow[0], Ow[1], Ow[2]);
        glVertex3d(Yw[0], Yw[1], Yw[2]);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3d(Ow[0], Ow[1], Ow[2]);
        glVertex3d(Zw[0], Zw[1], Zw[2]);
        glEnd();
        }

        for (size_t i = 0; i < poses.size(); i++) {
            // glColor3f(1 - (float) i / poses.size(), 0.0f, (float) i / poses.size());
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_LINES);
            auto p1 = poses[i], p2 = poses[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }

        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    } 
} 