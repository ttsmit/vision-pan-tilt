#include <iostream>
#include <math.h>
#include "tracker.cpp"
#include "gpmc_driver_cpp.cpp"

#define PI 3.1415926535

unsigned short posToAngle (int, float);

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
			unsigned short pan = posToAngle(x, 0.43);
			unsigned short tilt = posToAngle(y, 0.43);
			printf("pan: %frad, tilt: %frad\n", pan, tilt);
			Device.setValue(pan, 2);
			Device.setValue(tilt, 3);
		}
	}
	return 0;
} 


unsigned short posToAngle (int position, float scale){
	float distance = position * scale;
	float angle = atan2(distance, 100);
	return static_cast<unsigned short>(angle + PI) * 10000;
}
