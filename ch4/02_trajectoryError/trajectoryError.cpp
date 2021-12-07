#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

// #include <Eigen/Core>
// #include <Eigen/Dense>
#include <pangolin/pangolin.h>
#include <sophus/se3.hpp>

using namespace std;
using namespace Eigen;

string groundtruth_file = "../groundtruth.txt";
string estimated_file = "../estimated.txt";

typedef vector<Sophus::SE3d, Eigen::aligned_allocator<Sophus::SE3d> > TrajectoryType;

TrajectoryType read_trajectoryfile(const string path);

void draw_trajectory(const TrajectoryType gt, const TrajectoryType est);

double compute_rmse(const TrajectoryType gt, const TrajectoryType esti);

int main(int argc, char **argv)
{
    cout.precision(12);
    double rmse = 0;

    TrajectoryType groundtruth = read_trajectoryfile(groundtruth_file);
    TrajectoryType estimated   = read_trajectoryfile(estimated_file);

    rmse = compute_rmse(groundtruth, estimated);

    cout << "RMSE = " << rmse << endl;

    draw_trajectory(groundtruth, estimated);

    return 0;
}

TrajectoryType read_trajectoryfile(const string path)
{
    TrajectoryType ret_trajectory;

    ifstream fin(path);
    if (!fin) {
        cout << path << " open failed!" << endl;
        return ret_trajectory;
    }

    while (!fin.eof()) {
        double time, tx, ty, tz, qx, qy, qz, qw;
        fin >> time >> tx >> ty >> tz >> qx >> qy >> qz >> qw;
        Sophus::SE3d SE3(Quaterniond(qx, qy, qz, qw), Vector3d(tx, ty, tz));

        ret_trajectory.push_back(SE3);
    }

    return ret_trajectory;
}

double compute_rmse(const TrajectoryType gt, const TrajectoryType est)
{
    double ret = 0;

    for (size_t i = 0; i < est.size(); i++) {
        Sophus::SE3d SE3_gt = gt[i], SE3_est = est[i];
        double error = (SE3_gt.inverse() * SE3_est).log().norm();
        ret += error * error;
    }
    ret = sqrt(ret / (est.size()));

    return ret;
}

void draw_trajectory(const TrajectoryType gt, const TrajectoryType esti)
{
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
        for (size_t i = 0; i < gt.size() - 1; i++) {
        glColor3f(0.0f, 0.0f, 1.0f);  // blue for ground truth
        glBegin(GL_LINES);
        auto p1 = gt[i], p2 = gt[i + 1];
        glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
        glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
        glEnd();
        }

        for (size_t i = 0; i < esti.size() - 1; i++) {
        glColor3f(1.0f, 0.0f, 0.0f);  // red for estimated
        glBegin(GL_LINES);
        auto p1 = esti[i], p2 = esti[i + 1];
        glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
        glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
        glEnd();
        }
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }
    
}