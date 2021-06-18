#include <iostream>
#include <math.h>
#include "tracker.cpp"
#include "gpmc_driver_cpp.cpp"

#define PI 3.1415926535

unsigned short posToAngle (int, float);

int main(){
	std::string videoDevice = "/dev/video2";
	int createdSuccesfully = 0;
	Track tracker(videoDevice, 320, 240, &createdSuccesfully);
	if (createdSuccesfully == 0) return -1;
	tracker.setParameters(71, 128, 92, 103, 181, 255);

	char* gpmcDevice = "/dev/gpmc_fpga";
	gpmc_driver Device(gpmcDevice);
	//if(!Device.isValid()) return -1;

	int x, y;
	while(1){
		if (tracker.run(&x, &y) == 1){
			printf("x: %dpx, y: %dpx\n", x, y);
			unsigned short pan = posToAngle(x, 0.3);
			unsigned short tilt = posToAngle(y, 0.3);
			printf("pan: %urad, tilt: %urad\n", pan, tilt);
			Device.setValue(pan, 2);
			Device.setValue(tilt, 3);
		}
	}
	return 0;
} 


unsigned short posToAngle (int position, float scale){
	float distance = position * scale;
	float angle = atan2(distance, 100);
	printf("angle:%f\n", angle);
	unsigned short ret = (unsigned short) ((angle + PI) * 1000);
	return ret; 
}
