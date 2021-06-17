#include "tracker.cpp"


int main(){
	std::string device = "/dev/video0";
	int createdSuccesfully = 0;
	Track tracker(device, 320, 180, &createdSuccesfully);
	if (createdSuccesfully == 0) return -1;
	tracker.setParameters(81, 57, 96, 95, 116, 241);
	int x, y;
	while(1){
		if (tracker.run(&x, &y) == 1){
			printf("x: %d, y: %d\n", x, y);
		}
	}
	return 0;
} 
