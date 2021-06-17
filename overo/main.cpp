#include <iostream>
#include <math.h>
#include "tracker.cpp"
#include "gpmc_driver_cpp.h"

float posToAngle (int, float);

int main(){
	std::string videoDevice = "/dev/video0";
	int createdSuccesfully = 0;
	Track tracker(videoDevice, 320, 180, &createdSuccesfully);
	if (createdSuccesfully == 0) return -1;
	tracker.setParameters(81, 57, 96, 95, 116, 241);

	char* gpmcDevice = "/dev/gpmc_fpga";
	gpmc_driver Device(gpmcDevice);

	int x, y;
	while(1){
		if (tracker.run(&x, &y) == 1){
			printf("x: %dpx, y: %dpx\n", x, y);
			float pan = posToAngle(x, 0.43);
			float tilt = posToAngle(y, 0.43);
			printf("pan: %frad, tilt: %frad\n", pan, tilt);
		}
	}
	return 0;
} 


float posToAngle (int position, float scale){
	float distance = position * scale;
	return atan2(distance, 100);
}
