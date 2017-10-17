#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>

using std::cout;
using std::endl;
using std::string;
using cv::Mat;
using cv::Matx44f;
using cv::Matx34f;
using cv::Matx33f;
using cv::Point;
using cv::Point2f;
using cv::Point3f;
using cv::Vec3f;
using cv::imread;
using cv::imshow;
using cv::waitKey;

#define DEG2RAD CV_PI / 180.0
#define RAD2DEG 180.0 / CV_PI


// Vector alignment rotation matrix computation from:
//      https://math.stackexchange.com/a/476311/311746
void eulerAnglesFromVector(const cv::Vec3f &_vec, cv::Vec3f *rot,
                           const bool normalize = false) {
    cv::Vec3f vec = _vec;
    if (normalize) {
        double l2 = cv::norm(vec);
        vec /= l2;
    }

    const cv::Vec3f refVec(0, 0, 1);

    cv::Vec3f v = refVec.cross(vec);  // cross product

    double s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    double c = refVec.dot(vec);

    cv::Matx33f vx(0, -v[2], v[1], v[2], 0, -v[0], -v[1], v[0], 0);

    cv::Matx33f R;
    cv::add(cv::Mat::eye(3, 3, CV_32F), vx, R);
    cv::Matx33f tmp = (vx * vx) * (1/(1+c));
    cv::add(R, tmp, R);
    // At this point, R is the rotation matrix to align the z axis with the
    //   given vector vec.

    // We can compute the euler-angles/rotation-vector using Rodrigues
    cv::Rodrigues(R, *rot);
}

void showRotValues(const cv::Vec3f &rot) {
    std::cout << "Rotation: ["
              << rot[0] << ", "
              << rot[1] << ", "
              << rot[2] << "]::["
              << rot[0] * RAD2DEG << ", "
              << rot[1] * RAD2DEG << ", "
              << rot[2] * RAD2DEG << "]"
              << std::endl;
}

int main() {
    cv::Vec3f vec;
    cv::Vec3f rot;
    // Vector pointing z -> Zero rotation
    vec = cv::Vec3f(0, 0, 1);
    eulerAnglesFromVector(vec, &rot);
    std::cout << "Expected: [0, 0, 0]" << std::endl;
    showRotValues(rot);
    // Vector pointing x -> 90º on y
    vec = cv::Vec3f(1, 0, 0);
    eulerAnglesFromVector(vec, &rot);
    std::cout << "Expected: [0, 90, 0]" << std::endl;
    showRotValues(rot);
    // Vector pointing y -> 90º on x
    vec = cv::Vec3f(0, 1, 0);
    eulerAnglesFromVector(vec, &rot);
    std::cout << "Expected: [-90, 0, 0]" << std::endl;
    showRotValues(rot);
    // Vector pointing z and y -> -45º on x
    vec = cv::Vec3f(0, 1, 1);
    eulerAnglesFromVector(vec, &rot, true);
    std::cout << "Expected: [-45, 0, 0]" << std::endl;
    showRotValues(rot);
    // Vector pointing z and x -> 45º on y
    vec = cv::Vec3f(1, 0, 1);
    eulerAnglesFromVector(vec, &rot, true);
    std::cout << "Expected: [0, 45, 0]" << std::endl;
    showRotValues(rot);
    // Vector pointing y and x -> 90º on z and 45º on x or y
    vec = cv::Vec3f(1, 1, 0);
    eulerAnglesFromVector(vec, &rot, true);
    std::cout << "Expected: [?, ?, ?]" << std::endl;
    showRotValues(rot);
}
