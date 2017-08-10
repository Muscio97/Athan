#include <cstring>
#include "setup.hpp"

void Setup::operate(char *inputString) {
    int stringLength = std::strlen(inputString) + numberOfUnusedMatrices;

    Command display(spiBus, chipSelect, numberOfMatrices, numberOfRows, stringLength);
    display.settings(settings);

    for (int i = 0; i < numberOfUnusedMatrices; i++) {
        display.render(CharSpace);
    }

    for (int i = 0; i < stringLength - numberOfUnusedMatrices; i++) {
        hwlib::cout << inputString[i] << "\n\r";
        hwlib::cout << stringLength-numberOfUnusedMatrices<< "\n\r";
        
    }
}
