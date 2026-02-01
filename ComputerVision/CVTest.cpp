#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat img = cv::imread("Images/test.jpeg");

    if (img.empty()) {
        std::cout << "Image not loaded\n";
        return -1;
    }

    cv::imshow("Image", img);
    cv::waitKey(1);
    cv::waitKey(0);
    return 0;
}