/**
 * \file
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */



#include "command.hpp"

uint8_t MatrixDisplayParser::mirroruint8 (uint8_t b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

void MatrixDisplayParser::spiParseAndSend(const uint8_t *dataToSend){
    for (int currentRow = 0; currentRow < numberOfRows; currentRow++){
        int l = 0;
        for (int currentMatrix = 0; currentMatrix < numberOfMatrices; currentMatrix++){
            processedCommands[l++] = {(uint8_t)(currentRow+1)};
            processedCommands[l++] = {dataToSend[(currentRow + (currentMatrix*numberOfRows))]};
        }
		spiBus.write_and_read(chipSelect, static_cast<const size_t >(2 * numberOfMatrices), processedCommands, nullptr);
    }
}

void MatrixDisplayParser::settings(const uint8_t (*settingsList)[2]) {
    for (int i = 0; i < numberOfCommands; i++) {
        int l = 0;
        for (int k = 0; k < numberOfMatrices; k++) {
            processedCommands[l++] = {settingsList[i][0]};
            processedCommands[l++] = {settingsList[i][1]};
        }
        spiBus.write_and_read(chipSelect, static_cast<const size_t >(2 * numberOfMatrices), processedCommands, nullptr);
    }
}

void MatrixDisplayParser::shift(uint8_t *data, int rowsToShift){
    uint64_t shiftData[384] = {0};  // need to go to hpp
    int segmentSelecter = 0;        // need to go to hpp
    int sizeOfData = (sizeof(data)/sizeof(*data)); 
    for (int i = 0; i < sizeOfData; i++){
        for (int j = 0; j < rowsToShift; j++){
            shiftData[(j+segmentSelecter)] = data[i] & 0x01;
            data[i] >>= 1;
        }
        segmentSelecter = segmentSelecter + rowsToShift;
    }
    segmentSelecter = 0;
    for (int i = 1; i < sizeOfData; i++){
        for (int j = 0; j < rowsToShift; j++){
            data[i] = data[i]  | shiftData[(((rowsToShift-1) - j)+segmentSelecter)] << (7 - j);
        }
        segmentSelecter = segmentSelecter + rowsToShift;
    }
}

void MatrixDisplayParser::commandShifter(uint8_t *commands, int rowsToShift){
    uint8_t toBe[8];
    for(int i = 0; i < (numberOfRows*numberOfMatrices); i++){
        for (int currentRow = 0; currentRow < numberOfRows; currentRow++){
            for (int currentMatrix = 0; currentMatrix < numberOfMatrices; currentMatrix++){
                toBe[currentMatrix] = {commands[(currentRow + (currentMatrix*numberOfRows))]};
            }
            shift(toBe, rowsToShift);
            for (int currentMatrix = 0; currentMatrix < numberOfMatrices; currentMatrix++){
                commands[(currentRow + (currentMatrix*numberOfRows))] = toBe[currentMatrix];
            }
        }
        hwlib::wait_ms(150);
        spiParseAndSend(commands);
    }
}

void MatrixDisplayParser::render(uint64_t renderInput, const int stringLength) {
    static int listCounter = 0;
    for (int i = 0; i < numberOfRows; i++) {
        commands[listCounter++] = mirroruint8(renderInput & 0xFF);
        renderInput >>= 8;
    }
    if (listCounter == (8*stringLength)) {
        commandShifter(commands, 1);
    }
}
