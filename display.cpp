// Compile with: g++ -o display display.cpp display_func.cpp -lbcm2835 -lrt -lST7735_TFT_RPI
// Run using: sudo ./display
#include <bcm2835.h>
#include <iostream>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "display_func.cpp"
extern "C" {
	#include "button.c"
	#include "ADA1893.c"
}


int main(void) {
	// Setup functions
	input_setup();
	if(!Setup())return -1;
	ada1893_setup();

	// Declare variables
	float temp_read, pres_read, tMax, tMin, pMin, pMax;
	char temp[30], pres[30], temp_min[30], temp_max[30], pres_min[30], pres_max[30];

	// Read in current values
	temp_read = read_temp();
	pres_read = read_pres();
	tMax = 73.32;
	tMin = 68.1;
	pMin = 50.12;
	pMax = 55.69;

	// Convert readings to string
	std::sprintf(temp, "%.1f F", temp_read);
	std::sprintf(pres, "%.1f kPa", pres_read);

 	std::sprintf(temp_min, "Min: %.1f F", tMin);
	std::sprintf(temp_max, "Max: %.1f F", tMax);
        std::sprintf(pres_min, "Min: %.1f kPa", pMin);
        std::sprintf(pres_max, "Max: %.1f kPa", pMax);
	Reading_Screen1(temp, pres, temp_min, temp_max, pres_min, pres_max);

	int i;
	while(1){
	i = read_input();
	printf("%d", i);
	usleep(100);
	}

	// Close file descriptor and shut down display
	Shutdown_Display();
	return 0;
}
