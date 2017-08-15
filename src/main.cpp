#include "hwlib.hpp"
#include "display.hpp"

const int numberOfUnusedMatrices = 0;
const int numberOfMatrices = 4;
int main() {
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);


    // Matrix pins.
    target::pin_out digitalIn(target::pins::d4);
    target::pin_out chipSelect(target::pins::d5);
    target::pin_out clock(target::pins::d6);
    hwlib::spi_bus_bit_banged_sclk_mosi_miso spi(clock, digitalIn, hwlib::pin_in_dummy);

    Setup matrix(spi, chipSelect, numberOfUnusedMatrices, numberOfMatrices);

    const char charValue[5]= "*/|<";

    matrix.displayString(charValue);

    return 0;
}
