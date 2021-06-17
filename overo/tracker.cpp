#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

class Track {
		int lowH, lowS, lowV;
		int highH, highS, highV;
		int width, heigth;
		cv::VideoCapture cap;
		cv::Scalar lowerBound;
		cv::Scalar upperBound;
	public:
		Track(std::string, int, int, int*);
		void setParameters(int, int, int, int, int, int);
		int run(int* x, int* y);
};

Track::Track (std::string device, int width, int height, int* succes){
	Track::width = width;
	Track::heigth = height;
	std::string width_str = std::__cxx11::to_string(width);
	std::string height_str = std::__cxx11::to_string(height);
	const std::string device_settings = "v4l2src device=" + device + " ! video/x-raw, format=YUY2, width=" + width_str + ", height=" + height_str + ", pixel-aspect-ratio=1/1, framerate=30/1 ! videoconvert ! appsink";
	cap = cv::VideoCapture(device_settings, cv::CAP_GSTREAMER);
	if (cap.isOpened()) {
		*succes = 1;
	}
	else {
		*succes = 0;
	}
}

void Track::setParameters(int lowH, int lowS, int lowV, int highH, int highS, int highV){
	lowerBound = cv::Scalar(lowH, lowS, lowV);
	upperBound = cv::Scalar(highH, highS, highV);

	Track::lowH = lowH;
	Track::lowS = lowS;
	Track::lowV = lowV;
	Track::highH = highH;
	Track::highS = highS;
	Track::highV = highV;
}

int Track::run(int* x, int* y){
	cv::Mat frame;
	//Resize large images to reduce processing load
	cap >> frame;

	//Convert RGB to HSV colormap
	//and apply Gaussain blur
	cv::Mat hsvFrame;
	cv::cvtColor(frame, hsvFrame, cv::COLOR_RGB2HSV);
	cv::blur(hsvFrame, hsvFrame, cv::Size(1, 1));

	//Threshold 
	cv::Mat threshFrame;
	cv::inRange(hsvFrame, lowerBound, upperBound,  threshFrame);

	//Erosion filter to reduce noise
	cv::Mat element;
	cv::erode(threshFrame, threshFrame, element);

	//Calculate X,Y centroid
	cv::Moments m = moments(threshFrame, false);
	cv::Point com(m.m10 / m.m00, m.m01 / m.m00);
	
	if (0 < com.x < Track::width && 0 < com.y < Track::heigth){
		*x = com.x;
		*y = com.y;
		return 1;
	}

	return 0;
}
