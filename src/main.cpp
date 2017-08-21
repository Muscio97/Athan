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

    int numberOfMatrices = 12;
    Display matrix(spi, chipSelect, numberOfMatrices);
	Displayable dAble;

	const char charValue[13]= "STOP POLITIE";
    int steps = 1;
    int delay = 0;
    int cycles = 3;

	dAble.append(charValue);
	dAble.enableEffect(effectType::EFFECT_SHIFT_WRAP_RIGHT, steps, delay ,cycles);
	matrix.display(dAble);
    
    cout << "\n\nThe program finished in " << (now_us() - now) << "us";
    return 0;
}