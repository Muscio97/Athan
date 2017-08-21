/**
 * \file
 * \brief     Class that contains the functions that are needed to display text on the MAX7219.
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#pragma once

#include <hwlib.hpp>
#include "command.hpp"
#include "Displayable.hpp"

class Display {
private:

    /// Spi pins.
    hwlib::spi_bus &spiBus;
    hwlib::pin_out &chipSelect;

    /// Settings.
    int numberOfMatrices;
    const int numberOfRows = 8;

public:

    /**
    * \brief Constructor for Setup, initializes stuff down below.
    *
    * \param spiBus                     Basic spi stuff.
    * \param chipSelect                 Basic spi stuff.
    * \param numberOfUnusedMatrices     Is the number of matrices that aren't used, these will display charSpace
    *                                   a 8x8 matrix filled with zeros.
    *                                   So the display won't display random stuff because of current leaking.
    * \param numberOfMatrices           Is the number of matrices you have hooked up.
    */
    Display(hwlib::spi_bus &spiBus, hwlib::pin_out &chipSelect, int numberOfMatrices):
            spiBus(spiBus),
            chipSelect(chipSelect),
            numberOfMatrices(numberOfMatrices)
    {}
	
	void display(Displayable &displayObject);

    /**
     * \brief This function takes a string and displays it on the matrices.
     *
     * There is a limit, you can only display 0 to 9, - and +. The max string length is 20.
     * The number of displayed chars on the this display is limited by the number of matrices
     * \param[in] inputString that will be displayed on the led matrix.
     */
    void displayString(MatrixDisplayParser& display, const char *inputString);
	
	Display & operator<< (const char *lhs);
	Display & operator<< (Displayable &rhs);

};

