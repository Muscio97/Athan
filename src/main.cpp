#include "hwlib.hpp"
#include "display.hpp"
#include "Displayable.hpp"

int main() {

    WDT->WDT_MR = WDT_MR_WDDIS;
    
    using namespace hwlib;
    
    uint64_t now = now_us();

    wait_ms(1000);
    // Matrix pins.
    target::pin_out digitalIn(target::pins::d4);
    target::pin_out chipSelect(target::pins::d5);
    target::pin_out clock(target::pins::d6);
    spi_bus_bit_banged_sclk_mosi_miso spi(clock, digitalIn, pin_in_dummy);
    
    int numberOfMatrices = 3;
    Display matrix(spi, chipSelect, numberOfMatrices);
    const char charValue[(numberOfMatrices+1)]= "AB";    
    matrix.displayString(charValue);
    
    //Displayable dAble;
	//const char charValue[5]= "5555";
	//dAble.append(charValue);
    //matrix << charValue;
	
    cout << "\n\nThe program finished in " << (now_us() - now) << "us";
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