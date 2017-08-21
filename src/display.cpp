/**
 * \file
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <cstring> 
#include "mem.hpp"
#include "display.hpp"

Display & Display::operator<< (const char *lhs)
{
	MatrixDisplayParser display(spiBus, chipSelect, numberOfMatrices, numberOfRows);
	displayString(display, lhs);
	return *this;
}

Display & Display::operator<< (Displayable &rhs)
{
	display(rhs);
	
	return *this;
}
void Display::display(Displayable &displayObject)
{
	MatrixDisplayParser display(spiBus, chipSelect, numberOfMatrices, numberOfRows);
	
	display.setEffect(displayObject.getEffect());
	displayString(display, displayObject.getContent());
}

void Display::displayString(MatrixDisplayParser& display, const char *inputString) {
    size_t stringLength = strlen(inputString);
    
    display.settings(settings);
    int numberOfUnusedMatrices = numberOfMatrices - stringLength;
    
    for (size_t counter = 0; counter < stringLength; counter++) {
        switch (inputString[counter]) {
            case 'A' : display.render(A); break;            case 'a' : display.render(a); break;
            case 'B' : display.render(B); break;            case 'b' : display.render(b); break;
            case 'C' : display.render(C); break;            case 'c' : display.render(c); break;
            case 'D' : display.render(D); break;            case 'd' : display.render(d); break;
            case 'E' : display.render(E); break;            case 'e' : display.render(e); break;
            case 'F' : display.render(F); break;            case 'f' : display.render(f); break;
            case 'G' : display.render(G); break;            case 'g' : display.render(g); break;
            case 'H' : display.render(H); break;            case 'h' : display.render(h); break;
            case 'I' : display.render(I); break;            case 'i' : display.render(i); break;
            case 'J' : display.render(J); break;            case 'j' : display.render(j); break;
            case 'K' : display.render(K); break;            case 'k' : display.render(k); break;
            case 'L' : display.render(L); break;            case 'l' : display.render(l); break;
            case 'M' : display.render(M); break;            case 'm' : display.render(m); break;
            case 'N' : display.render(N); break;            case 'n' : display.render(n); break;
            case 'O' : display.render(O); break;            case 'o' : display.render(o); break;
            case 'P' : display.render(P); break;            case 'p' : display.render(p); break;
            case 'Q' : display.render(Q); break;            case 'q' : display.render(q); break;
            case 'R' : display.render(R); break;            case 'r' : display.render(r); break;
            case 'S' : display.render(S); break;            case 's' : display.render(s); break;
            case 'T' : display.render(T); break;            case 't' : display.render(t); break;
            case 'U' : display.render(U); break;            case 'u' : display.render(u); break;
            case 'V' : display.render(V); break;            case 'v' : display.render(v); break;
            case 'W' : display.render(W); break;            case 'w' : display.render(w); break;
            case 'X' : display.render(X); break;            case 'x' : display.render(x); break;
            case 'Y' : display.render(Y); break;            case 'y' : display.render(y); break;
            case 'Z' : display.render(Z); break;            case 'z' : display.render(z); break;
            
            case '1' : display.render(charOne); break;      case '6' : display.render(charSix); break;
            case '2' : display.render(charTwo); break;      case '7' : display.render(charSeven); break;
            case '3' : display.render(charThree); break;    case '8' : display.render(charEight); break;
            case '4' : display.render(charFour); break;     case '9' : display.render(charNine); break;
            case '5' : display.render(charFive); break;     case '0' : display.render(charZero); break;
                                                                                                                            
            case ' ' : display.render(nop); break;        case '\\' : display.render(bslash); break;
            case '+' : display.render(plus); break;         case '-' : display.render(minus); break;
            case '*' : display.render(muliply); break;      case '/' : display.render(divide); break;
            case '%' : display.render(procent); break;      case '=' : display.render(equal); break;
            case '~' : display.render(tilde); break;        case '^' : display.render(bup); break;
            case '<' : display.render(bleft); break;        case '>' : display.render(bright); break;
            case '(' : display.render(lbrecket); break;     case ')' : display.render(rbrecket); break;
            case '[' : display.render(slbrckt); break;      case ']' : display.render(srbrckt); break;
            case '{' : display.render(clbrckt); break;      case '}' : display.render(crbrckt); break;
            case '.' : display.render(dot); break;          case ',' : display.render(comma); break;
            case '!' : display.render(exclam); break;       case '?' : display.render(quest); break;
            case '@' : display.render(at); break;           case '&' : display.render(also); break;
            case '$' : display.render(dollar); break;       case '#' : display.render(hashtag); break;
            case '`' : display.render(hlcomma); break;      case '|' : display.render(hrcomma); break;
            
            default  : display.render(nop); break;
        }
    }
        
    for (int counter = 0; counter < numberOfUnusedMatrices; counter++) {
        display.render(nop);
    }
}
