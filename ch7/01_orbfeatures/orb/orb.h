#ifndef _ORB_H
#define _ORB_H
#include <iostream>
#include <string>
#include <nmmintrin.h>
#include <cmath>
#include <chrono>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;

typedef vector<bool> DescType;

class orb
{
    public:
        orb(cv::Mat image);
        void compute_orb();
        void compute_descriptors();
        vector<cv::KeyPoint> keypoints;
        vector<DescType> descriptors;


    private:
        const int half_patch_size = 8;
        const int half_boundary = 16;

    private:
        cv::Mat _image;
        
        
        int badpoints = 0;
};




#endif