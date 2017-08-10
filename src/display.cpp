#include <cstring>
#include "display.hpp"

Display & Display::operator<< (char* rhs)
{
	operate(rhs);
	
	return *this;
}

void Display::operate(char *inputString) {
    int stringLength = std::strlen(inputString);
	
	if (stringLength > numberOfMatrices)
	{
		// We got overflow
		return;
	}
	
	int numberOfUnusedMatrices = numberOfMatrices - stringLength;
	
	if (stringLength < numberOfMatrices)
	{
		stringLength = numberOfMatrices;
	}
	
    Command display(spiBus, chipSelect, stringLength);
    display.settings(settings);
	
	display.enableShift();
	
    for (int i = 0; i < numberOfUnusedMatrices; i++) {
        display.render(CharSpace);
    }

    for (int i = 0; i < stringLength - numberOfUnusedMatrices; i++) {
        hwlib::cout << inputString[i] << "\n\r";
        hwlib::cout << stringLength-numberOfUnusedMatrices<< "\n\r";
        switch (inputString[i]) {
            case 'a' : display.render(CharA);       break;
            case 'b' : display.render(CharB);       break;
            case 'c' : display.render(CharC);       break;
            case 'd' : display.render(CharD);       break;
            case 'e' : display.render(CharE);       break;
            case 'f' : display.render(CharF);       break;
            case 'g' : display.render(CharG);       break;
            case 'h' : display.render(CharH);       break;
            case 'i' : display.render(CharI);       break;
            case 'j' : display.render(CharJ);       break;
            case 'k' : display.render(CharK);       break;
            case 'l' : display.render(CharL);       break;
            case 'm' : display.render(CharM);       break;
            case 'n' : display.render(CharN);       break;
            case 'o' : display.render(CharO);       break;
            case 'p' : display.render(CharP);       break;
            case 'q' : display.render(CharQ);       break;
            case 'r' : display.render(CharR);       break;
            case 's' : display.render(CharS);       break;
            case 't' : display.render(CharT);       break;
            case 'u' : display.render(CharU);       break;
            case 'v' : display.render(CharV);       break;
            case 'w' : display.render(CharW);       break;
            case 'x' : display.render(CharX);       break;
            case 'y' : display.render(CharY);       break;
            case 'z' : display.render(CharZ);       break;
            case '1' : display.render(CharOne);     break;
            case '2' : display.render(CharTwo);     break;
            case '3' : display.render(CharThree);   break;
            case '4' : display.render(CharFour);    break;
            case '5' : display.render(CharFive);    break;
            case '6' : display.render(CharSix);     break;
            case '7' : display.render(CharSeven);   break;
            case '8' : display.render(CharEight);   break;
            case '9' : display.render(CharNine);    break;
            case '0' : display.render(CharZero);    break;
            case ' ' : display.render(CharSpace);   break;
            case '!' : display.render(CharUit);     break;
            case '_' : display.render(CharUnder);   break;
            case '?' : display.render(CharQuestion);break;
            case '.' : display.render(CharPoint);   break;
            case ',' : display.render(CharComma);   break;
            case '[' : display.render(CharSquare_L);break;
            case ']' : display.render(CharSquare_R);break;
            case '+' : display.render(CharPlus);    break;
            case '-' : display.render(CharMinus);   break;
            case '*' : display.render(CharMultiply);break;
            case '/' : display.render(CharDivide);  break;
            case '=' : display.render(CharEqual);   break;
            case ';' : display.render(CharSemi);    break;
            case ':' : display.render(CharColon);   break;
            default:   display.render(CharSpace);   break;
        }
    }
}
