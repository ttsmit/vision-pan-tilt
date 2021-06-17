#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class Track {
		int lowH, lowS, lowV;
		int highH, highS, highV;
		cv::VideoCapture cap;
		cv::Scalar lowerBound
		cv::Scalar upperBound
	public:
		int track(std::string, int, int);
		void setParameters(int, int, int, int, int, int);
		int run(int* x, int* y);
};

int Track::track (std::string device, int width, int height){
	std::string width_str = std::to_string(width);
	std::string height_str = std::to_Sting(height);
	const std::string device_settings = "v4l2src device=" + device + " ! video/x-raw, format=YUY2, width=" + width_str + ", height=" + height_str + ", pixel-aspect-ratio=1/1, framerate=30/1 ! videoconvert ! appsink";
	cap = cv::VideoCapture(device_settings, cv::CAP_GSTREAMER);
	if (cap.isOpened()) {
		return 1;
	}
	else {
		return 0;
	}
}

Track::setParameters(int lowH, int lowS, int lowV, int highH, int highS, int highV){
	lowerBound = cv::Scalar(lowH, lowS, lowV);
	upperBound = cv::Scalar(highH, highS, highV);
}

int Track::run(int* x, int* y){

}
