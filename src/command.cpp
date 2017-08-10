/**
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "command.hpp"

void Command::commander(uint8_t (*commands)[8][2], int offset) {
		for (int j = 0; j <= 8; j++) {
			int l = 0;
			for (int k = 0; k < stringLength; k++) {
				processedCommands[l] = {(uint8_t) j};
				l++;
				processedCommands[l] = {commands[k + offset][j - 1][1]};
				l++;
			}

			spiBus.write_and_read(chipSelect, static_cast<const size_t >(2 * stringLength), processedCommands, nullptr);
		}
}


void Command::settings(const uint8_t (*settingsList)[2]) {
    for (int i = 0; i < numberOfCommands; i++) {
        int l = 0;
        for (int k = 0; k < stringLength; k++) {
            processedCommands[l] = {settingsList[i][0]};
            l++;
            processedCommands[l] = {settingsList[i][1]};
            l++;
        }
        spiBus.write_and_read(chipSelect, static_cast<const size_t >(2 * stringLength), processedCommands, nullptr);
    }
}

void Command::converter(uint8_t (*renderInput)[8], uint8_t (*converterOutput)[2]) {
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t shiftVariable = 0;
        int rowCounter = 0;
        for (int j = 8; j >= 0; j--) {
            shiftVariable |= renderInput[i][rowCounter - 1] << (j);
            rowCounter++;
        }
        converterOutput[i][0] = i + static_cast<uint8_t >(1);
        converterOutput[i][1] = shiftVariable;
    }

}

void Command::render(uint8_t (*renderInput)[8]) {
    converter(renderInput, converterOutput);
    for (int i = 0; i < 8; i++) {
        commands[numberOfWrites][i][1] = converterOutput[i][1];
    }
    numberOfWrites++;
	enableShift();
    if (numberOfWrites == stringLength) {
       // numberOfWrites = 0;
		if (shiftEnabled)
		{
			for (int i = 0; i <= stringLength; i++)
			{
				commander(commands, i);
				hwlib::wait_ms(250);
			}
			
			return;
		}
		
		commander(commands);
    }
}

void Command::enableShift()
{
	shiftEnabled = true;
}

void Command::disableShift()
{
	shiftEnabled = false;
}

bool Command::shiftStatus()
{
	return shiftEnabled;
}