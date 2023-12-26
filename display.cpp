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
}


int main(void) {
	// Setup functions
	input_setup();
	if(!Setup())return -1;

	// Declare variables
	float temp_read, alt_read, tMax, tMin, aMin, aMax;
	char temp[30], alt[30], temp_min[30], temp_max[30], alt_min[30], alt_max[30];

	// Read in current values
	temp_read = 20;
	alt_read = 54.31;
	tMax = 73.32;
	tMin = 68.1;
	aMin = 50.12;
	aMax = 55.69;

	// Convert readings to string
	std::sprintf(temp, "%.1f F", temp_read);
	std::sprintf(alt, "%.1f M", alt_read);

 	std::sprintf(temp_min, "Min: %.1f F", tMin);
	std::sprintf(temp_max, "Max: %.1f F", tMax);
        std::sprintf(alt_min, "Min: %.1f M", aMin);
        std::sprintf(alt_max, "Max: %.1f M", aMax);
	Reading_Screen1(temp, alt, temp_min, temp_max, alt_min, alt_max);

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
