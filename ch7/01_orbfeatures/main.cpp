#include <iostream>


#include "./orb/orb.h"
using namespace std;

// string image_1 = "../jinan1.jpg";
// string image_2 = "../jinan2.jpg";

string image_1 = "../1.png";
string image_2 = "../2.png";

void BfMatch(const vector<DescType> &desc1, const vector<DescType> &desc2, vector<cv::DMatch> &matches);

int main(int argc, char **argv)
{
    cv::Mat image1 = cv::imread(image_1, 0);
    cv::Mat image2 = cv::imread(image_2, 0);

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();    
    orb orb1(image1);
    orb orb2(image2);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "extract ORB cost = " << time_used.count() << " seconds. " << endl;

    // find matches
    vector<cv::DMatch> matches;
    t1 = chrono::steady_clock::now();
    // BfMatch(orb1.descriptors, orb2.descriptors, matches);
    // TODO: try opencv flann algorithm
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
    matcher->match(orb1.descriptors, orb2.descriptors, matches);
    t2 = chrono::steady_clock::now();
    time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "match ORB cost = " << time_used.count() << " seconds. " << endl;
    cout << "matches: " << matches.size() << endl;

    // plot the matches
    cv::Mat image_show;
    cv::drawMatches(image1, orb1.keypoints, image2, orb2.keypoints, matches, image_show);
    cv::imshow("matches", image_show);
    cv::imwrite("matches.png", image_show);
    cv::waitKey(0);

  cout << "done." << endl;

    return 0;
}

// brute-force matching
void BfMatch(const vector<DescType> &desc1, const vector<DescType> &desc2, vector<cv::DMatch> &matches) {
  const int d_max = 40;
  cout << desc1.size() << " " << desc2.size() << endl;

  for (size_t i1 = 0; i1 < desc1.size(); ++i1) {
    if (desc1[i1].empty()) continue;

    cv::DMatch m{i1, 0, 256};
    
    for (size_t i2 = 0; i2 < desc2.size(); ++i2) {
      if (desc2[i2].empty()) continue;

      int distance = 0;
      for (int k = 0; k < 256; k++) {
        distance += (desc1[i1][k] ^ desc2[i2][k]);
      }
      if (distance < d_max && distance < m.distance) {
        m.distance = distance;
        m.trainIdx = i2;
      }
    }
    if (m.distance < d_max) {
      matches.push_back(m);
    }
  }
}