#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat detectRed(const cv::Mat &frame){
    cv:: Mat hsv, mask1, mask2, mask;
    // Convert from BGR to HSV color space
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

    //Threshold for lower red hue 
    // S > 150 ensures bright red, ignores pink/pale tones
    // V> 100 ensures not too dark
    cv::inRange(hsv,cv::Scalar(0,150,100), cv::Scalar(10,255,255),mask1);
    //Upper Red Range
    cv::inRange(hsv,cv::Scalar(160,150,100), cv::Scalar(179,255,255),mask2);

    //Combines both masks into one 
    cv::bitwise_or(mask1, mask2, mask);
    
    //Removes small noise
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5));
    cv::morphologyEx(mask,mask,cv::MORPH_CLOSE, kernel);
    return mask;
}

bool redDetected(const cv::Mat &mask, double areaThreshold = 500.0){
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask,contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for(const auto &c :contours){
        if(cv::contourArea(c) > areaThreshold)
            return true;
    }
    return false;
}
void drawGreenBoxes(cv:: Mat &frame, const cv::Mat &mask, double areaThreshold = 500.0){
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask,contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (const auto &c : contours){
        if(cv::contourArea(c) > areaThreshold){
            cv::Rect bbox = cv::boundingRect(c);
            cv::rectangle(frame, bbox, cv::Scalar(0,255,0),2);
        }
    }
}

int main() {
    cv::VideoCapture cap(0); // 0 = default webcam
    if (!cap.isOpened()) {
        std::cerr << "ERROR: Cannot openwebcam\n";
        return -1;
    }

    cv::Mat frame;
    while(true){
        cap >> frame;
        if (frame.empty()) break;

        cv::Mat redMask = detectRed(frame);
        if (redDetected(redMask)) {
            std::cout << "STOP" << std::endl; // Output words
        }
        else {
            std::cout << "GO" << std::endl; // normal logic
        }

        drawGreenBoxes(frame,redMask);
        cv::imshow("Webcam Feed", frame);
        cv::imshow("Red Mask", redMask);



        if (cv::waitKey(1) == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}