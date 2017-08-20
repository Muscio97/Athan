#pragma once

#include <hwlib.hpp>

class Displayable
{
private:
	char content[255];
	uint8_t index;
	uint8_t brightness;
	
	typedef enum {
		EFFECT_NONE,
		EFFECT_SHIFT_LEFT,
		EFFECT_SHIFT_RIGHT,
		EFFECT_BLINK,
		EFFECT_FADING_IN,
		EFFECT_FADING_OUT 
	} effectType;
	
	struct displayEffect {
		effectType type;
		uint16_t delay;
	};
	
	displayEffect effect;
	
public:
	Displayable():
		content{0},
		index(0),
		brightness(0x04)
	{};
	
	Displayable & operator<< (const char* str);
	char* operator>> (char* dump);
	void append(const char* str);
	uint8_t getLength();
	char* getContent();
	
	void enableEffect(effectType et, uint16_t delay = 100);
	displayEffect getEffect();
	void disableEffect();
	
	void setBrightness(uint8_t value);
	uint8_t getBrightness();
	
	void clear();
};