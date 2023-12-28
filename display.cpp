// Compile with: g++ -o display display.cpp display_func.cpp -lbcm2835 -lrt -lST7735_TFT_RPI
// Run using: sudo ./display
#include <bcm2835.h>
#include <iostream>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "display_func.cpp"
extern "C" {
	#include "ADA1893.c"
}


int main(void) {
	// Setup functions
	if(!Setup())return -1;
	ada1893_setup();

	// Declare variables
	float temp_read, pres_read;
	float tMax = -1;
	float tMin = 999;
	float pMax = -1;
	float pMin = 999;
	char temp[30], pres[30], temp_min[30], temp_max[30], pres_min[30], pres_max[30];

	// This while loop will read and display the statistics once every 3 seconds
	while(1){
		// Read in current values
		temp_read = read_temp();
		pres_read = read_pres();

		// Collect maximum readings
		if (temp_read > tMax) tMax = temp_read;
		if (pres_read > pMax) pMax = pres_read;

	        // Collect minimum readings
	        if (temp_read < tMin) tMin = temp_read;
        	if (pres_read < pMin) pMin = pres_read;

		// Convert readings to string
		std::sprintf(temp, "%.1f F", temp_read);
		std::sprintf(pres, "%.1f kPa", pres_read);
	 	std::sprintf(temp_min, "Min: %.1f F", tMin);
		std::sprintf(temp_max, "Max: %.1f F", tMax);
	        std::sprintf(pres_min, "Min: %.1f kPa", pMin);
	        std::sprintf(pres_max, "Max: %.1f kPa", pMax);

		// Call screen function to display readings
		Reading_Screen1(temp, pres, temp_min, temp_max, pres_min, pres_max);
		sleep(3);
	}

	// Close file descriptor and shut down display
	Shutdown_Display();
	return 0;
}
