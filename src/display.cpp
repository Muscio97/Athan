/**
 * \file
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include <cstring> 
#include "mem.hpp"
#include "display.hpp"

void Display::displayString(const char *inputString) {
    size_t stringLength = strlen(inputString) + numberOfUnusedMatrices;
    MatrixDisplayParser display(spiBus, chipSelect, numberOfMatrices, numberOfRows);
    display.settings(settings);

    for (int counter = 0; counter < numberOfUnusedMatrices; counter++) {
		display.render(nop, stringLength);
    }

    for (size_t counter = 0; counter < stringLength - numberOfUnusedMatrices; counter++) {
        switch (inputString[counter]) {
            case 'A' : display.render(A, stringLength); break;            case 'a' : display.render(a, stringLength); break;
            case 'B' : display.render(B, stringLength); break;            case 'b' : display.render(b, stringLength); break;
            case 'C' : display.render(C, stringLength); break;            case 'c' : display.render(c, stringLength); break;
            case 'D' : display.render(D, stringLength); break;            case 'd' : display.render(d, stringLength); break;
            case 'E' : display.render(E, stringLength); break;            case 'e' : display.render(e, stringLength); break;
            case 'F' : display.render(F, stringLength); break;            case 'f' : display.render(f, stringLength); break;
            case 'G' : display.render(G, stringLength); break;            case 'g' : display.render(g, stringLength); break;
            case 'H' : display.render(H, stringLength); break;            case 'h' : display.render(h, stringLength); break;
            case 'I' : display.render(I, stringLength); break;            case 'i' : display.render(i, stringLength); break;
            case 'J' : display.render(J, stringLength); break;            case 'j' : display.render(j, stringLength); break;
            case 'K' : display.render(K, stringLength); break;            case 'k' : display.render(k, stringLength); break;
            case 'L' : display.render(L, stringLength); break;            case 'l' : display.render(l, stringLength); break;
            case 'M' : display.render(M, stringLength); break;            case 'm' : display.render(m, stringLength); break;
            case 'N' : display.render(N, stringLength); break;            case 'n' : display.render(n, stringLength); break;
            case 'O' : display.render(O, stringLength); break;            case 'o' : display.render(o, stringLength); break;
            case 'P' : display.render(P, stringLength); break;            case 'p' : display.render(p, stringLength); break;
            case 'Q' : display.render(Q, stringLength); break;            case 'q' : display.render(q, stringLength); break;
            case 'R' : display.render(R, stringLength); break;            case 'r' : display.render(r, stringLength); break;
            case 'S' : display.render(S, stringLength); break;            case 's' : display.render(s, stringLength); break;
            case 'T' : display.render(T, stringLength); break;            case 't' : display.render(t, stringLength); break;
            case 'U' : display.render(U, stringLength); break;            case 'u' : display.render(u, stringLength); break;
            case 'V' : display.render(V, stringLength); break;            case 'v' : display.render(v, stringLength); break;
            case 'W' : display.render(W, stringLength); break;            case 'w' : display.render(w, stringLength); break;
            case 'X' : display.render(X, stringLength); break;            case 'x' : display.render(x, stringLength); break;
            case 'Y' : display.render(Y, stringLength); break;            case 'y' : display.render(y, stringLength); break;
            case 'Z' : display.render(Z, stringLength); break;            case 'z' : display.render(z, stringLength); break;
            
            case '1' : display.render(charOne, stringLength); break;      case '6' : display.render(charSix, stringLength); break;
            case '2' : display.render(charTwo, stringLength); break;      case '7' : display.render(charSeven, stringLength); break;
            case '3' : display.render(charThree, stringLength); break;    case '8' : display.render(charEight, stringLength); break;
            case '4' : display.render(charFour, stringLength); break;     case '9' : display.render(charNine, stringLength); break;
            case '5' : display.render(charFive, stringLength); break;     case '0' : display.render(charZero, stringLength); break;
                                                                                                                            
            case ' ' : display.render(nop, stringLength); break;        case '\\' : display.render(bslash, stringLength); break;
            case '+' : display.render(plus, stringLength); break;         case '-' : display.render(minus, stringLength); break;
            case '*' : display.render(muliply, stringLength); break;      case '/' : display.render(divide, stringLength); break;
            case '%' : display.render(procent, stringLength); break;      case '=' : display.render(equal, stringLength); break;
            case '~' : display.render(tilde, stringLength); break;        case '^' : display.render(bup, stringLength); break;
            case '<' : display.render(bleft, stringLength); break;        case '>' : display.render(bright, stringLength); break;
            case '(' : display.render(lbrecket, stringLength); break;     case ')' : display.render(rbrecket, stringLength); break;
            case '[' : display.render(slbrckt, stringLength); break;      case ']' : display.render(srbrckt, stringLength); break;
            case '{' : display.render(clbrckt, stringLength); break;      case '}' : display.render(crbrckt, stringLength); break;
            case '.' : display.render(dot, stringLength); break;          case ',' : display.render(comma, stringLength); break;
            case '!' : display.render(exclam, stringLength); break;       case '?' : display.render(quest, stringLength); break;
            case '@' : display.render(at, stringLength); break;           case '&' : display.render(also, stringLength); break;
            case '$' : display.render(dollar, stringLength); break;       case '#' : display.render(hashtag, stringLength); break;
            case '`' : display.render(hlcomma, stringLength); break;      case '|' : display.render(hrcomma, stringLength); break;
            
            default  : display.render(nop, stringLength); break;
        }
    }
}
