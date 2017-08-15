/**
 * \file
 * \brief       GAS module main
 * \author      Chris Smeele
 * \author      David Driessen
 * \author      Paul Ettema
 * \author      Robbie Valkenburg
 * \author      Mike Hilhorst
 * \author      Bram van Bergeijk
 * \author      Wilco Louwerse
 * \author      David de Jong
 * \author      Nicky van Steensel van der Aa
 * \copyright   Copyright (c) 2017, The R2D2 Team
 * \license     See LICENSE
 *              https://github.com/R2D2-2017/R2D2-2017/wiki/Gas-safety-system
 *              https://trello.com/c/etqKmerH/93-gas-gas-safety-system
 */
#include "hwlib.hpp"
#include "display.hpp"
#include "command.hpp"
/**
 * \brief Casts int value of maximum 3 numbers to characters,
 *        The characters are stored in the second parameter
 *        mq5Char.
 */


const int numberOfUnusedMatrices = 0;
const int numberOfMatrices = 4;
const int startupLedWait = 200;
const int preHeatTime = 300;    // Time in seconds for preheating of the sensor.


int main() {
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;

    // Matrix pins.
    target::pin_out digitalIn(target::pins::d4);
    target::pin_out chipSelect(target::pins::d5);
    target::pin_out clock(target::pins::d6);
    hwlib::spi_bus_bit_banged_sclk_mosi_miso spi(clock, digitalIn, hwlib::pin_in_dummy);


    // Initialize variables
    char charValue[5] = "1166";

    Setup matrix(spi, chipSelect, numberOfUnusedMatrices, numberOfMatrices);

    // Start loop measurements, writing data and alarm.
    hwlib::wait_ms(500);
    
    matrix.displayString(charValue);
    return 0;
}
