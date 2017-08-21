/**
 * \file
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "command.hpp"

using namespace hwlib;

uint8_t MatrixDisplayParser::mirroruint8 (uint8_t b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

void MatrixDisplayParser::commandSender(const uint8_t *dataToSend){
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

void MatrixDisplayParser::shift(uint8_t *data, int rowsToShift, int mode){
    uint64_t shiftData[384] = {0};
    int segmentSelecter = 0;
    int sizeOfData = (sizeof(data)/sizeof(*data)); 
    for (int i = 0; i < sizeOfData; i++){
        for (int j = 0; j < rowsToShift; j++){
            shiftData[(j+segmentSelecter)] = data[i] & 0x01;
            data[i] >>= 1;
        }
        segmentSelecter = segmentSelecter + rowsToShift;
    }
    segmentSelecter = 0;
    for (int i = 1; i < sizeOfData+1; i++){
        for (int j = 0; j < rowsToShift; j++){
            if(i == sizeOfData && mode == 1){
                data[0] = data[0]  | shiftData[(((rowsToShift-1) - j)+segmentSelecter)] << (7 - j);
            }else{
                data[i] = data[i]  | shiftData[(((rowsToShift-1) - j)+segmentSelecter)] << (7 - j);
            }
        }
        segmentSelecter = segmentSelecter + rowsToShift;
        //cout << hex << (int)data[i] << endl;
    }
}

void MatrixDisplayParser::commandShifter(uint8_t *commands, int delay = 40, int rowsToShift = 1, int mode = 0){
    uint8_t toBe[32];
    if (mode == 0){
        commandSender(commands);
    }
    for (int i = 0; i < ((int)(sizeof(toBe)/sizeof(*toBe))*numberOfMatrices)/rowsToShift; i++){
        for (int currentRow = 0; currentRow < numberOfRows; currentRow++){
            for (int currentMatrix = 0; currentMatrix < numberOfMatrices; currentMatrix++){
                toBe[currentMatrix] = {commands[(currentRow + (currentMatrix*numberOfRows))]};
            }
            shift(toBe, rowsToShift, mode);
            for (int currentMatrix = 0; currentMatrix < numberOfMatrices; currentMatrix++){
                commands[(currentRow + (currentMatrix*numberOfRows))] = toBe[currentMatrix];
            }
        }
        wait_ms(delay*numberOfMatrices*rowsToShift);
        commandSender(commands);
    }
}

void MatrixDisplayParser::render(uint64_t renderInput) {
    static int listCounter = 0;
    for (int i = 0; i < numberOfRows; i++) {
        commands[listCounter++] = mirroruint8(renderInput & 0xFF);
        renderInput >>= 8;
    }
    if (listCounter == (8*12/*8*numberOfMatrices*/)) {
        switch (dEffect.type)
        {
            case effectType::EFFECT_SHIFT_RIGHT:
                commandShifter(commands, dEffect.delay, dEffect.steps);
                break;
            case effectType::EFFECT_SHIFT_LEFT:
                commandShifter(commands, -1, dEffect.delay);
                break;
            case effectType::EFFECT_SHIFT_WRAP_RIGHT:
                for(int i = 0; i < dEffect.cycles; i++){
                    commandShifter(commands, dEffect.delay, dEffect.steps, 1);
                }
                break;
            case effectType::EFFECT_FADING_IN:
                break;
            case effectType::EFFECT_FADING_OUT:
                break;
            case effectType::EFFECT_BLINK:
                break;
            default:
                commandSender(commands);
                break;
        }
    }
}

void MatrixDisplayParser::setEffect(displayEffect effect)
{
	dEffect = effect;
}