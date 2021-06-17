#include <iostream>
#include <math.h>
#include "tracker.cpp"

#define PI 3.14159265

float posToAngle (int, float);

int main(){
	std::string device = "/dev/video0";
	int createdSuccesfully = 0;
	Track tracker(device, 320, 180, &createdSuccesfully);
	if (createdSuccesfully == 0) return -1;
	tracker.setParameters(81, 57, 96, 95, 116, 241);
	int x, y;
	while(1){
		if (tracker.run(&x, &y) == 1){
			printf("x: %dpx, y: %dpx\n", x, y);
			float pan = posToAngle(x, 0.43)*180/PI;
			float tilt = posToAngle(y, 0.43)*180/PI;
			printf("pan: %frad, tilt: %frad\n", pan, tilt);
		}
	}
	return 0;
} 


float posToAngle (int position, float scale){
	float distance = position * scale;
	return atan2(distance, 100);
}
