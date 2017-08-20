#include "Displayable.hpp"
#include <cstring>

void Displayable::append(const char* str)
{
	size_t len = strlen(str);
	
	// Check for overflow
	if (index + len > 255)
		return;
	
	// Copy the contents of str to self contents
	for (unsigned int pos = 0; pos < len; pos++)
	{
		content[index] = str[pos];
		index++;
	}
}

Displayable & Displayable::operator<< (const char* str)
{
	append(str);
	return *this;
}

char* Displayable::operator>> (char* dump)
{
	size_t size = sizeof(*dump);
	
	for (unsigned int pos = 0; pos < size; pos++)
	{
		
	}
	
	return dump;
}

uint8_t Displayable::getLength()
{
	return index;
}

char* Displayable::getContent()
{
	return content;
}

void Displayable::enableEffect(effectType ef, uint16_t delay)
{
	effect.type = ef;
	effect.delay = delay;
}

Displayable::displayEffect Displayable::getEffect()
{
	return effect;
}

void Displayable::disableEffect()
{
	effect.type = effectType::EFFECT_NONE;
}

void Displayable::setBrightness(uint8_t value)
{
	brightness = value;
}

uint8_t Displayable::getBrightness()
{
	return brightness;
}

void Displayable::clear()
{
	// Reset index
	index = 0;
	
	// Reset animation to none
	effect.type = effectType::EFFECT_NONE;
}