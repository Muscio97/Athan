/**
 * \file
 * \brief     Class that contains the functions that are needed to display text on the MAX7219.
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once

#include "hwlib.hpp"


class MatrixDisplayParser {
private:

    /**
     * SPI pins.
     */
    hwlib::spi_bus &spiBus;
    hwlib::pin_out &chipSelect;

   /// Amount of matrices used to display text.
    int numberOfMatrices;

    /// Number of rows per matrix.
    int numberOfRows;

    /// Represents the size of a matrix and is used to prevent no junk data is added to them.
    int numberOfCommands = 5;

    uint8_t temp = 0;
    /**
    * \brief Matrices used in .cc names represents their functionality.
     *
     * The size of the matrices and arrays support up to 20 characters.
    */
    uint8_t processedCommands[20];
    uint8_t commands[1000];
    /**
     * \brief Allows commands to be send via Hwlib SPI to the led matrix.
     *
     * This function expects a pointer to an array. This array contains a set of 8x2 matrices
     * that in turn contains the data that to be written per row, to the display matrices.
     * A example of one of these matrices {{0x00, 0xff},{0x01, 0xff}...{0x07, 0xff}
     * where the first hexadecimal value of the size 2 array is the address of of the led row on the matrix
     * and the second hexadecimal value is which leds to light up in bitwise fassion.
     * As in {0x00, 0xFF} light up all leds on row 0 of the matrix in question.
     *
     * \param[in] dataToSend A pointer to a location in an array that contains an 8x2 matrix.
     */
    
    void spiParseAndSend(const uint8_t (*dataToSend));
    /**
     * \brief This function converts a 8x8 matrix to a 8x2 matrix.
     *
     * This conversion makes the datsa use able for commander.
     * \param[in] renderInput       Accept 8x8 matrix.
     * \param[out] converterOutput  8x2 matrix.
     */
    //void converter(const uint8_t (*renderInput)[8], uint8_t (*converterOutput));

public:
    /**
     * \brief Constructor for command.
     *
     * Initializes stuff down below.
     * \param spiBus            Basic spi stuff.
     * \param chipSelect        Basic spi stuff.
     * \param numberOfMatrices  Is the number of matrices you have hooked up.
     * \param numberOfRows      Contains the amount of rows that the matrices have.
     */

    MatrixDisplayParser(hwlib::spi_bus &spiBus, hwlib::pin_out &chipSelect, int numberOfMatrices, int numberOfRows) :
            spiBus(spiBus), chipSelect(chipSelect), numberOfMatrices(numberOfMatrices), numberOfRows(numberOfRows){};

    /**
     * \brief This function is allot like commander but it sends settings to the MAX7219.
     *
     * [1] Address you want to speak to.
     * [2] Data you want to send.
     * \param settingsList list of settings.
     */
    void settings(const uint8_t (*settingsList)[2]);

    /**
     * \brief This function accepts a 8x8 matrix and displays it on the display matrices using commander and converter.
     *
     * \param[in] renderInput   Accepts 8x8 matrix.
     * \param[in] stringLength  Size of text to display on led matrices.
     */
    void render(uint64_t renderInput, const int stringLength);
	
	uint8_t mirroruint8 (uint8_t b);
};
