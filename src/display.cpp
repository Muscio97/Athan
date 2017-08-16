/**
 * \file
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */
#include "display.hpp"
#include <cstring>

/// Chars that can be displayed.
/// Using static consts to save data into flash (ROM)
static const uint64_t A =  0x33333f33331e0c00;   static const uint64_t a =  0x006e333e301e0000;
static const uint64_t B =  0x3f66663e66663f00;   static const uint64_t b =  0x003b66663e060607;
static const uint64_t C =  0x3c66030303663c00;   static const uint64_t c =  0x001e3303331e0000;
static const uint64_t D =  0x1f36666666361f00;   static const uint64_t d =  0x006e33333e303038;
static const uint64_t E =  0x7f46161e16467f00;   static const uint64_t e =  0x001e033f331e0000;
static const uint64_t F =  0x0f06161e16467f00;   static const uint64_t f =  0x000f06060f06361c;
static const uint64_t G =  0x7c66730303663c00;   static const uint64_t g =  0x1f303e33336e0000;
static const uint64_t H =  0x3333333f33333300;   static const uint64_t h =  0x006766666e360607;
static const uint64_t I =  0x1e0c0c0c0c0c1e00;   static const uint64_t i =  0x001e0c0c0c0e000c;
static const uint64_t J =  0x1e33333030307800;   static const uint64_t j =  0x1e33333030300030;
static const uint64_t K =  0x6766361e36666700;   static const uint64_t k =  0x0067361e36660607;
static const uint64_t L =  0x7f66460606060f00;   static const uint64_t l =  0x001e0c0c0c0c0c0e;
static const uint64_t M =  0x63636b7f7f776300;   static const uint64_t m =  0x00636b7f7f330000;
static const uint64_t N =  0x6363737b6f676300;   static const uint64_t n =  0x00333333331f0000;
static const uint64_t O =  0x1c36636363361c00;   static const uint64_t o =  0x001e3333331e0000;
static const uint64_t P =  0x0f06063e66663f00;   static const uint64_t p =  0x0f063e66663b0000;
static const uint64_t Q =  0x381e3b3333331e00;   static const uint64_t q =  0x78303e33336e0000;
static const uint64_t R =  0x6766363e66663f00;   static const uint64_t r =  0x000f06666e3b0000;
static const uint64_t S =  0x1e33380e07331e00;   static const uint64_t s =  0x001f301e033e0000;
static const uint64_t T =  0x1e0c0c0c0c2d3f00;   static const uint64_t t =  0x00182c0c0c3e0c08;
static const uint64_t U =  0x3f33333333333300;   static const uint64_t u =  0x006e333333330000;
static const uint64_t V =  0x0c1e333333333300;   static const uint64_t v =  0x000c1e3333330000;
static const uint64_t W =  0x63777f6b63636300;   static const uint64_t w =  0x00367f7f6b630000;
static const uint64_t X =  0x63361c1c36636300;   static const uint64_t x =  0x0063361c36630000;
static const uint64_t Y =  0x1e0c0c1e33333300;   static const uint64_t y =  0x1f303e3333330000;
static const uint64_t Z =  0x7f664c1831637f00;   static const uint64_t z =  0x003f260c193f0000;

static const uint64_t charOne =  0x7e1818181c181800;     static const uint64_t charSix =  0x3c66663e06663c00;
static const uint64_t charTwo =  0x7e060c3060663c00;     static const uint64_t charSeven =  0x1818183030667e00;
static const uint64_t charThree =  0x3c66603860663c00;   static const uint64_t charEight =  0x3c66663c66663c00;
static const uint64_t charFour =  0x30307e3234383000;    static const uint64_t charNine =  0x3c66607c66663c00;
static const uint64_t charFive =  0x3c6660603e067e00;    static const uint64_t charZero =  0x3c66666e76663c00;

static const uint64_t nop =    0x0000000000000000;       static const uint64_t bslash =   0x406030180c060300;
static const uint64_t plus =     0x000c0c3f0c0c0000;     static const uint64_t minus =    0x0000003f00000000;
static const uint64_t muliply =  0x00663cff3c660000;     static const uint64_t divide =   0x0103060c18306000;
static const uint64_t procent =  0x63660c1833630000;     static const uint64_t equal =    0x003f00003f000000;
static const uint64_t tilde =    0x00000000003b6e00;     static const uint64_t bup =      0x00000063361c0800;
static const uint64_t bleft =    0x180c0603060c1800;     static const uint64_t bright =   0x060c1830180c0600;
static const uint64_t lbrecket = 0x180c0606060c1800;     static const uint64_t rbrecket = 0x060c1818180c0600;
static const uint64_t slbrckt =  0x1e06060606061e00;     static const uint64_t srbrckt =  0x1e18181818181e00;
static const uint64_t clbrckt =  0x380c0c070c0c3800;     static const uint64_t crbrckt =  0x070c0c380c0c0700;
static const uint64_t dot =      0x0c0c000000000000;     static const uint64_t comma =    0x060c0c0000000000;
static const uint64_t colon =    0x0c0c00000c0c0000;     static const uint64_t semi =     0x060c0c00000c0c00;     
static const uint64_t exclam =   0x180018183c3c1800;     static const uint64_t quest =    0x0c000c1830331e00;
static const uint64_t at =       0x1e037b7b7b633e00;     static const uint64_t also =     0x6e333b6e1c361c00;
static const uint64_t dollar =   0x0c1f301e033e0c00;     static const uint64_t hashtag =  0x36367f367f363600;
static const uint64_t hlcomma =  0x00000000180c0c00;     static const uint64_t hrcomma =  0x0000000003060600;

static const uint8_t settings[5][2] = {{0x09,0x00},{0x0c,0x01},{0x0f,0x00},{0x0A,0x04},{0x0B,0x07}};

void Setup::displayString(const char *inputString) {
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
