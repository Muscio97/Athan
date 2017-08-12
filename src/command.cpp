/**
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#include "command.hpp"

void Command::commander(uint8_t (*commands), int offset) {
	int temp = 0;
	
	//hwlib::cout << hwlib::hex << (int) commands[0];
	
	for(int i = 0; i < stringLength; i++)
	{
		
		for(int j = 0; j <= 7; j++)
		{
			processedCommands[temp] = (uint8_t) j;
			//hwlib::cout << (int) processedCommands[temp] << ": ";
			temp++;
			processedCommands[temp] = commands[j];
			//hwlib::cout << hwlib::hex << (int) processedCommands[temp] << hwlib::endl;
			
			temp++;
			//commands++;
		}
		spiBus.write_and_read(chipSelect, s12), processedCommands, nullptr);
		hwlib::wait_ms(20);
	}	
	
/*
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
*/
}


void Command::settings(const uint8_t (*settingsList)[2]) {
	/** @Mike Waarom is hier gebruik gemaakt van stringLength.
	 * String length staat toch helemaal niet verband met de configuratie settings die gezonden moeten worden?
	 * Zie regel 81 in display.hpp.
	 * Waarschijnlijk is dit niet de oplossing van het probleem.
	**/
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



void Command::render(uint64_t renderInput) {
	//uint8_t *temp = (uint8_t *)&renderInput;
	
	for(int i = 0; i < 8; i++) {
		//hwlib::cout << hwlib::hex  << (int) (renderInput & 0xFF) << hwlib::endl;
		commands[i] = renderInput & 0xFF;
		renderInput >>= 8;
	}
	
    //for (int i = 0; i < 8; i++) {
        //commands[stringLength+i] = temp[i];
    //}
	
    numberOfWrites++;
	//enableShiftR();
	
	//hwlib::cout << "Writes: " << numberOfWrites << hwlib::endl;
	//hwlib::cout << "String length: " << stringLength;
	
    if (numberOfWrites == stringLength) {
       // numberOfWrites = 0;
		if (shiftEnabledL)
		{
			for (int i = 0; i <= stringLength*2; i++)
			{
				commander(commands, i);
				hwlib::wait_ms(250);
			}
			
			return;
		}
		if (shiftEnabledR)
		{
			for (int i = stringLength*2; i >= 0; i--)
			{
				commander(commands, i);
				hwlib::wait_ms(250);
			}

			return;
		}
		
		commander(commands, stringLength);
    }
}

void Command::enableShiftL()
{
	shiftEnabledL = true;
}

void Command::disableShiftL()
{
	shiftEnabledL = false;
}

void Command::enableShiftR()
{
	shiftEnabledR = true;
}

void Command::disableShiftR()
{
	shiftEnabledR = false;
}