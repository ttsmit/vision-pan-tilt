#include <iostream>
#include <math.h>
#include "tracker.cpp"
#include "gpmc_driver_cpp.cpp"

#define PI 3.1415926535

float posToAngle (int, float);

int main(){
	std::string videoDevice = "/dev/video0";
	int createdSuccesfully = 0;
	Track tracker(videoDevice, 320, 180, &createdSuccesfully);
	if (createdSuccesfully == 0) return -1;
	tracker.setParameters(81, 57, 96, 95, 116, 241);

	char* gpmcDevice = "/dev/gpmc_fpga";
	gpmc_driver Device(gpmcDevice);
	//if(!Device.isValid()) return -1;

	int x, y;
	while(1){
		if (tracker.run(&x, &y) == 1){
			printf("x: %dpx, y: %dpx\n", x, y);
			float pan = posToAngle(x, 0.43);
			float tilt = posToAngle(y, 0.43);
			unsigned short pan_s = static_cast<unsigned short>(pan + PI) * 10000;
			unsigned short tilt_s = static_cast<unsigned short>(tilt + PI) * 10000;
			printf("pan: %frad, tilt: %frad\n", pan_s, tilt);
			Device.setValue(pan_s, 2);
			Device.setValue(tilt_s, 3);
		}
	}
	return 0;
} 


float posToAngle (int position, float scale){
	float distance = position * scale;
	return atan2(distance, 100);
}
