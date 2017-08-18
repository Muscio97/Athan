#include "hwlib.hpp"
#include "display.hpp"

const int numberOfUnusedMatrices = 0;
const int numberOfMatrices = 4;

int main() {
    uint64_t now = hwlib::now_us();
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);
    // Matrix pins.
    target::pin_out digitalIn(target::pins::d4);
    target::pin_out chipSelect(target::pins::d5);
    target::pin_out clock(target::pins::d6);
    hwlib::spi_bus_bit_banged_sclk_mosi_miso spi(clock, digitalIn, hwlib::pin_in_dummy);

    Display matrix(spi, chipSelect, numberOfUnusedMatrices, numberOfMatrices);

    const char charValue[5]= "5555";    
    matrix.displayString(charValue);
	matrix << charValue;
    
    hwlib::cout << "\n\nThe program finished in " << (hwlib::now_us() - now) << "us";
    return 0;
}

/**if (effect == DISPLAY_ANIM_SHIFT)
{
	
}

switch(effect)
{
	case DISPLAY_ANIM_SHIFT_L:
		// Actions to take for lefting shifting
		break;
	case DISPLAY_ANIM_SHIFT_R;
		// Actions to take for right shiftling
		break;
}\

matrix.render("Hello world", 3);

enum {
	DISPLAY_ANIM_SHIFT,
}
**/