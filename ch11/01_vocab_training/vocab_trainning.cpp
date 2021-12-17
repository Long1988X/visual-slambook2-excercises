#include <iostream>
#include <vector>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "DBoW3/DBoW3.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    cout << "Reading images .............." << endl;
    vector<Mat> images;

    for (int i = 0; i < 10; i++) {
        string path = "../images/" + to_string(i+1) + ".png";
        images.push_back(imread(path));
    }

    cout << "ORB features detect .............." << endl;
    cout<<"detecting ORB features ... "<<endl;
    Ptr< Feature2D > detector = ORB::create();
    vector<Mat> descriptors;
    for ( Mat& image:images )
    {
        vector<KeyPoint> keypoints; 
        Mat descriptor;
        detector->detectAndCompute( image, Mat(), keypoints, descriptor );
        descriptors.push_back( descriptor );
    }

    // create vocabulary 
    cout<<"creating vocabulary ... "<<endl;
    DBoW3::Vocabulary vocab;
    vocab.create( descriptors );
    cout<<"vocabulary info: "<<vocab<<endl;
    vocab.save( "vocabulary.yml.gz" );
    cout<<"done"<<endl;

    return 0;
}