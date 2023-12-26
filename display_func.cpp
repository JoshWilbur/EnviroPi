#include <bcm2835.h>
#include <iostream>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <thread>
#include <chrono>

#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT_graphics.hpp"
#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT.hpp"
#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT_Print.hpp"

// Global struct myTFT
ST7735_TFT myTFT;


// Static declaration of functions
int8_t Setup(void);
void Test_Text(void);
void Reading_Screen1(char* temp, char* pres, char* temp_min, char* temp_max, char* pres_min, char* pres_max);
void Shutdown_Display(void);

void Reading_Screen1(char* temp, char* pres, char* temp_min, char* temp_max, char* pres_min, char* pres_max){
        myTFT.TFTfillScreen(ST7735_GREY);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
        myTFT.TFTsetRotation(myTFT.TFT_Degrees_90); // Rotate screen so its in landscape mode
	myTFT.TFTdrawFastHLine(0, 63, 160, ST7735_GREEN);
	myTFT.TFTdrawFastHLine(0, 64, 160, ST7735_GREEN);
	myTFT.TFTdrawFastHLine(0, 65, 160, ST7735_GREEN);
	myTFT.TFTfillRoundRect(5, 8, 150, 50, 5, ST7735_BLACK);
	myTFT.TFTfillRoundRect(5, 70, 150, 50, 5, ST7735_BLACK);

	char temp_str[] = "Temperature";
	myTFT.TFTdrawText(45, 10, temp_str, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(15, 40, temp, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTdrawText(80, 20, temp_min, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(80, 30, temp_max, ST7735_WHITE, ST7735_BLACK, 1);

        char pres_str[] = "Pressure";
        myTFT.TFTdrawText(50, 75, pres_str, ST7735_WHITE, ST7735_BLACK, 1);
	myTFT.TFTdrawText(15, 103, pres, ST7735_WHITE, ST7735_BLACK, 2);
	myTFT.TFTdrawText(80, 85, pres_min, ST7735_WHITE, ST7735_BLACK, 1);
        myTFT.TFTdrawText(80, 95, pres_max, ST7735_WHITE, ST7735_BLACK, 1);

        std::this_thread::sleep_for(std::chrono::seconds(7)); // Display for three seconds before ending function
}

// Setup function from TFT library
int8_t Setup(void)
{
	std::cout << "TFT Start" << std::endl;
	if(!bcm2835_init())
	{
		std::cout << "Error : Problem with init bcm2835 library" << std::endl;
		return -1;
	}

// GPIO/SPI TYPE
	int8_t RST_TFT = 25;
	int8_t DC_TFT = 24;
	int8_t SCLK_TFT = -1;   // 5, change to any GPIO no for sw spi, -1 hw spi
	int8_t SDIN_TFT = -1;   // 6, change to any GPIO no for sw spi, -1 hw spi
	int8_t CS_TFT = -1;  // 8, change to any GPIO no for sw spi, -1 hw spi
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT, CS_TFT, SCLK_TFT, SDIN_TFT);


// Screen Setup
	uint8_t OFFSET_COL = 0;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0; // 3, with manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128; // Screen width
	uint16_t TFT_HEIGHT = 160; // Screen height
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);

// PCB_TYPE + SPI baud rate + SPI_CE_PIN
	uint32_t SCLK_FREQ =  8000000 ; // HW Spi only , freq in Hertz , MAX 125 Mhz MIN 30Khz
	uint8_t SPI_CE_PIN = 0; // HW Spi only which HW SPI chip enable pin to use,  0 or 1
	if(!myTFT.TFTInitPCBType(myTFT.TFT_ST7735R_Red, SCLK_FREQ, SPI_CE_PIN))return -1;
	return 0;
}

void Test_Text(void) {
	char teststr1[] = "testing"; // String to hold what is printed
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
        myTFT.TFTfillScreen(ST7735_BLACK);
        myTFT.TFTsetRotation(myTFT.TFT_Degrees_270); // Rotate screen so its in landscape mode
	myTFT.TFTdrawText(15, 30, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	std::this_thread::sleep_for(std::chrono::seconds(3)); // Display for three seconds before ending function
}

void Shutdown_Display(void)
{
	myTFT.TFTPowerDown(); // Power down device
	bcm2835_close(); // Close the bcm2835 library
	std::cout << "TFT End" << std::endl;
}
