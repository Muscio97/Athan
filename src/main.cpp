/**
 * \file
 */
#include "hwlib.hpp"
#include "setup.hpp"
#include <cstdio>

/**
 * \brief Casts int value of maximum 3 numbers to characters,
 *		  The characters are stored in the second parameter
 *		  mq5Char.
 */
void convertToChar(int toConvert, char converted[8]);

void convertToChar(int toConvert, char converted[8]) {
    converted[0] = ((char) (toConvert / 100000000 % 10) + '0');
    converted[1] = ((char) (toConvert % 10000000 / 1000000) + '0');
    converted[2] = ((char) (toConvert % 1000000 / 100000) + '0');
    converted[3] = ((char) (toConvert % 100000 / 10000) + '0');
    converted[0] = ((char) (toConvert % 10000 / 1000) + '0');
    converted[1] = ((char) (toConvert % 1000 / 100) + '0');
    converted[2] = ((char) (toConvert % 100 / 10) + '0');
    converted[3] = ((char) (toConvert % 10) + '0');
}

int main() {
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;
    // Matrix pins.
    target::pin_out digitalIn(target::pins::d4);
    target::pin_out chipSelect(target::pins::d5);
    target::pin_out clock(target::pins::d6);
    hwlib::spi_bus_bit_banged_sclk_mosi_miso spi(clock, digitalIn, hwlib::pin_in_dummy);

    const int numberOfUnusedMatrices = 0;
    const int numberOfMatrices = 12;
    char charValue[12]= {'1','2','3','4','5','6','7','8', '9', '0', '1', '2'};
    Setup matrix(spi, chipSelect, numberOfUnusedMatrices, numberOfMatrices);
    //int i =10000;
    using namespace hwlib;

   // sprintf(charValue, "%d", i);

    cout << charValue << endl;
    //while (true) {

        //convertToChar(i++, charValue);
        //sprintf(charValue, "%d", i++);
       // matrix.operate(charValue);

//    }
    matrix.operate(charValue);

    return 0;
}
