/**
 * \file
 */
#include "hwlib.hpp"
#include "display.hpp"
/**
 * \brief Casts int value of maximum 3 numbers to characters,
 *		  The characters are stored in the second parameter
 *		  mq5Char.
 */
int main() {
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;
    // Matrix pins.
    target::pin_out digitalIn(target::pins::d4);
    target::pin_out chipSelect(target::pins::d5);
    target::pin_out clock(target::pins::d6);
    hwlib::spi_bus_bit_banged_sclk_mosi_miso spi(clock, digitalIn, hwlib::pin_in_dummy);

    const int numberOfMatrices = 100;
    //char charValue[16]= {'1','*','+','+',' ','6','7',' ', '9', '0', '1', 'k', 'a', 'b', 'c', 'd'};
	char charValue[100] = "1234567890shdfkabfksdbfhacbs,,hdbakhvakdshvbckhvdaskhfbvbccbkjbdskhabvksdbva.kbdkjbvkjdsbjk";
    Display matrix(spi, chipSelect, numberOfMatrices);

    using namespace hwlib;

	matrix << charValue;
	/**matrix << charValue;
	
	displayString text;
	
	text.setValue("Hallo");
	text << "hallo";
	
	text.setBold();
	text.enableSwiftEffect();
	text.setStartx(10);
	
	// In matrix class
	text.getOptions();**/
	
	//matrix << text;
	
	

    return 0;
}
