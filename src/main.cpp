#include "hwlib.hpp"
#include "display.hpp"
#include "Displayable.hpp"

const int numberOfUnusedMatrices = 0;
const int numberOfMatrices = 4;



int main() {
    /**int rowsToShift = 4;
    uint8_t data[15] = {0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};
    uint64_t shiftData[384] = {0};  // need to go to hpp
    //uint8_t storage = 0x00;
    int segmentSelecter = 0;        // need to go to hpp
        int sizeOfData = (sizeof(data)/sizeof(*data)); 
    for(int temp = 0; temp < 32; temp++){
        rowsToShift = 4;
        segmentSelecter = 0;
    
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
                if(i == 15){
                    data[0] = data[0]  | shiftData[(((rowsToShift-1) - j)+segmentSelecter)] << (7 - j);
                }else{
                    data[i] = data[i]  | shiftData[(((rowsToShift-1) - j)+segmentSelecter)] << (7 - j);
                }
            }
            segmentSelecter = segmentSelecter + rowsToShift;
        }
        hwlib::wait_ms(1000);
        for (int i = 0; i < sizeOfData; i++){
            if (data[i] == 0 ){
                hwlib::cout << i << ": " << data[i] << hwlib::endl;
            }else{
                hwlib::cout << hwlib::hex << (int)data[i] << hwlib::endl;
            }
        }
        hwlib::cout << "===========\n";
    }
    for(;;){}**/

    
    uint64_t now = hwlib::now_us();
    namespace target = hwlib::target;

    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);
    // Matrix pins.
    target::pin_out digitalIn(target::pins::d4);
    target::pin_out chipSelect(target::pins::d5);
    target::pin_out clock(target::pins::d6);
    hwlib::spi_bus_bit_banged_sclk_mosi_miso spi(clock, digitalIn, hwlib::pin_in_dummy);

    Display matrix(spi, chipSelect, numberOfUnusedMatrices, numberOfMatrices);
	Displayable dAble;
	
	const char charValue[5] = "1234";   
	
	dAble.append(charValue);
	dAble.enableEffect(effectType::EFFECT_NONE);
	matrix.display(dAble);
    
    hwlib::cout << "\n\nThe program finished in " << (hwlib::now_us() - now) << "us";
    return 0;
}

/**if (effect == DISPLAY_ANIM_SHIFT)
{
	
}

switch(effect)
{
	case DISPLAY_ANIM_SHIFT_L:
		// Actions to take for lefting shifting
		break;
	case DISPLAY_ANIM_SHIFT_R;
		// Actions to take for right shiftling
		break;
}\

matrix.render("Hello world", 3);

enum {
	DISPLAY_ANIM_SHIFT,
}
**/