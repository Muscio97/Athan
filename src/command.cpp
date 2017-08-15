/**
 * \file
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "command.hpp"

void MatrixDisplayParser::spiParseAndSend(const uint8_t (*dataToSend)[8]) {
    for (int j = 0; j <= numberOfRows; j++) {
        int l = 0;
        for (int k = 0; k < numberOfMatrices; k++) {
            processedCommands[l] = {(uint8_t) j};
            l++;
            processedCommands[l] = {(uint8_t) dataToSend[k][j-1]};
            l++;
        }
        
        spiBus.write_and_read(chipSelect, static_cast<const size_t >(2 * numberOfMatrices), processedCommands, nullptr);
    }
    hwlib::cout << hwlib::endl;
}

void MatrixDisplayParser::settings(const uint8_t (*settingsList)[2]) {
    int l = 0;
    for (int i = 0; i < numberOfMatrices; i++) {
        processedCommands[l++] = {settingsList[i][0]};
        processedCommands[l++] = {settingsList[i][1]};
    }
    spiBus.write_and_read(chipSelect, static_cast<const size_t >(2 * numberOfMatrices), processedCommands, nullptr);
}

void MatrixDisplayParser::render(uint64_t renderInput, const int stringLength) {
    for (int i = 0; i < numberOfRows; i++) {
        commands[numberOfWrites][i] = renderInput & 0xFF;
        renderInput >>= 8;
    }
    numberOfWrites++;
    if (numberOfWrites == stringLength) {
        numberOfWrites = 0;
        spiParseAndSend(commands);
    }
}
