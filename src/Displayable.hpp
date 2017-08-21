#pragma once

#include <hwlib.hpp>

/// @wvanbreukelen Subject to changes.
enum class effectType {
	EFFECT_NONE,
	EFFECT_SHIFT_LEFT,
	EFFECT_SHIFT_RIGHT,
    EFFECT_SHIFT_WRAP_RIGHT,
    EFFECT_SHIFT_WRAP_LEFT,
	EFFECT_BLINK,
	EFFECT_FADING_IN,
	EFFECT_FADING_OUT
};

/// Properties of an effect.
struct displayEffect {
	effectType type;
	uint16_t delay;
    uint8_t steps;
    uint8_t cycles;
};

class Displayable
{
public:
	Displayable():
		content{0},
		index(0),
		brightness(0x04)
	{};

	
	/**
	 * @brief Append string into displayable content.
	 * @param str String to append.
	 */
	Displayable & operator<< (const char* str);
	
	/**
	 * @brief Append string into displayable content.
	 * @param str String to append.
	 */
	bool append(const char* str);
	
	/**
	 * @brief Get length of displayable content.
	 * @return Length.
	 */
	uint8_t getLength();
	
	/**
	 * @brief Get holding content.
	 * @return Content, with a maximum size of 254 bytes (minus /0).
	 */
	char* getContent();
	
	/**
	 * @brief Enable an effect.
	 * @param et Effect type.
	 * @param delay Frame update delay.
	 */
	void enableEffect(effectType et, uint8_t steps = 1, uint16_t delay = 40, uint8_t cycles = 3);
	
	/**
	 * @brief Get effective effect.
	 * @return displayEffect datatype.
	 */
	displayEffect getEffect();
	
	effectType getEffectType();
	
	uint16_t getEffectDelay();
	
	uint8_t getEffectSteps();
    
    uint8_t getEffectCycles();
	
	/**
	 * @brief Disable effect.
	 * Changes effective effect to EFFECT_NONE.
	 */
	void disableEffect();
	
	/**
	 * @brief Set display brightness
	 * @param value Brightness level (as unsigned byte).
	 */
	void setBrightness(uint8_t value);
	
	/**
	 * @brief Get display brightness
	 * @return Brightness level (as unsigned byte).
	 */
	uint8_t getBrightness();
	
	/**
	 * @brief Clear ADT
	 */
	void clear();
	
private:
	/// Displayable content holden by the ADT.
	char content[255];
	
	/// Current position index in content.
	uint8_t index;
	
	/// Display brightness, may be moved @wvanbreukelen
	uint8_t brightness;
	
	displayEffect effect;
};