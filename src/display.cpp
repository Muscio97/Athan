/**
 * \file
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017; The R2D2 Team
 * \license   See LICENSE
 */

#include "display.hpp"
#include <cstring>

/// Chars that can be displayed.
const uint64_t charA = 0x6666667e66663c00;
const uint64_t CharB = 0x3e66663e66663e00;
const uint64_t charOne = 0x003f0c0c0c0c0e0c;
const uint64_t charTwo = 0x003f33061c30331e;
const uint64_t charThree = 0x001e33301c30331e;
const uint64_t charFour = 0x0078307f33363c38;
const uint64_t charFive =  0x001e3330301f033f;
const uint64_t charSix =  0x001e33331f03061c;
const uint64_t charSeven =  0x000c0c0c1830333f;
const uint64_t charEight =  0x001e33331e33331e;
const uint64_t charNine =  0x000e18303e33331e;
const uint64_t charZero =  0x003e676f7b73633e;


//static const uint8_t charSpace[8][8] = {
//        {1;1;0;0;0;0;0;0}; {0;0;1;1;1;0;0;0};
//        {0;1;1;1;1;0;0;0}; {0;0;0;1;1;0;0;0};
//        {0;0;0;1;1;0;0;0}; {0;0;0;1;1;0;0;0};
//        {0;1;1;1;1;1;1;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charOne[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;0;1;1;1;0;0;0};
//        {0;1;1;1;1;0;0;0}; {0;0;0;1;1;0;0;0};
//        {0;0;0;1;1;0;0;0}; {0;0;0;1;1;0;0;0};
//        {0;1;1;1;1;1;1;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charTwo[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;1;1;1;1;1;0;0};
//        {0;0;0;0;0;1;1;0}; {0;0;0;0;0;1;1;0};
//        {0;0;0;0;1;1;0;0}; {0;0;0;1;1;0;0;0};
//        {0;1;1;1;1;1;1;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charThree[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;1;1;1;1;1;0;0};
//        {0;0;0;0;0;1;1;0}; {0;0;0;1;1;1;1;0};
//        {0;0;0;1;1;1;1;0}; {0;0;0;0;0;1;1;0};
//        {0;1;1;1;1;1;0;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charFour[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;0;0;0;0;1;0;0};
//        {0;0;0;0;1;1;0;0}; {0;0;0;1;0;1;0;0};
//        {0;0;1;0;0;1;0;0}; {0;1;1;1;1;1;1;0};
//        {0;0;0;0;0;1;0;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charFive[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;1;1;1;1;1;1;0};
//        {0;1;0;0;0;0;0;0}; {0;1;1;1;1;1;0;0};
//        {0;0;0;0;0;0;1;0}; {0;0;0;0;0;0;1;0};
//        {0;1;1;1;1;1;0;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charSix[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;0;1;1;1;1;1;0};
//        {0;1;0;0;0;0;0;0}; {0;1;1;1;1;1;0;0};
//        {0;1;0;0;0;0;1;0}; {0;1;0;0;0;0;1;0};
//        {0;0;1;1;1;1;0;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charSeven[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;1;1;1;1;1;1;0};
//        {0;0;0;0;0;1;1;0}; {0;0;0;0;1;1;0;0};
//        {0;0;0;1;1;0;0;0}; {0;0;1;1;0;0;0;0};
//        {0;1;1;0;0;0;0;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charEight[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;0;1;1;1;1;0;0};
//        {0;1;0;0;0;0;1;0}; {0;0;1;1;1;1;0;0};
//        {0;1;0;0;0;0;1;0}; {0;1;0;0;0;0;1;0};
//        {0;0;1;1;1;1;0;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charNine[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;0;1;1;1;1;0;0};
//        {0;1;0;0;0;0;1;0}; {0;0;1;1;1;1;1;0};
//        {0;0;0;0;0;0;1;0}; {0;0;0;0;0;0;1;0};
//        {0;0;1;1;1;1;0;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charZero[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;0;1;1;1;1;0;0};
//        {0;1;0;0;0;0;1;0}; {0;1;0;0;0;0;1;0};
//        {0;1;0;0;0;0;1;0}; {0;1;0;0;0;0;1;0};
//        {0;0;1;1;1;1;0;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charMinus[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;0;0;0;0;0;0;0};
//        {0;0;0;0;0;0;0;0}; {0;1;1;1;1;1;1;0};
//        {0;1;1;1;1;1;1;0}; {0;0;0;0;0;0;0;0};
//        {0;0;0;0;0;0;0;0}; {0;0;0;0;0;0;0;0}};
//static const uint8_t charPlus[8][8] = {
//        {0;0;0;0;0;0;0;0}; {0;0;0;1;1;0;0;0};
//        {0;0;0;1;1;0;0;0}; {0;1;1;1;1;1;1;0};
//        {0;1;1;1;1;1;1;0}; {0;0;0;1;1;0;0;0};
//        {0;0;0;1;1;0;0;0}; {0;0;0;0;0;0;0;0}};
static const uint8_t settings[5][2] = {{0x09,0x00},{0x0c,0x01},{0x0f,0x00},{0x0A,0x04},{0x0B,0x07}};

void Setup::displayString(const char *inputString) {
    size_t stringLength = strlen(inputString) + numberOfUnusedMatrices;
    MatrixDisplayParser display(spiBus, chipSelect, numberOfMatrices, numberOfRows);
    display.settings(settings);

    for (int i = 0; i < numberOfUnusedMatrices; i++) {
        display.render(charZero, stringLength);
    }

    for (size_t i = 0; i < stringLength - numberOfUnusedMatrices; i++) {
        switch (inputString[i]) {
            case '1' : display.render(charOne, stringLength); break;
            case '2' : display.render(charTwo,  stringLength); break;
            case '3' : display.render(charThree, stringLength); break;
            case '4' : display.render(charFour, stringLength); break;
            case '5' : display.render(charFive, stringLength); break;
            case '6' : display.render(charSix, stringLength); break;
            case '7' : display.render(charSeven, stringLength); break;
            case '8' : display.render(charEight, stringLength); break;
            case '9' : display.render(charNine, stringLength); break;
            case '0' : display.render(charZero, stringLength); break;
//            case '+' : display.render(charPlus, stringLength); break;
//            case '-' : display.render(charMinus, stringLength); break;
//            default  : display.render(charSpace, stringLength); break;
        }
    }
}
