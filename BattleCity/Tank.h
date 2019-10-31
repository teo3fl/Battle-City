#pragma once
#include <cstdint>
#include <string>

class Tank
{
public :
	virtual std::string GetName() const = 0;
	virtual uint16_t GetPoints() const = 0;
	virtual uint8_t GetHealth() const = 0;
	virtual uint8_t GetMovement() const = 0; // returns the movement speed of the tank;
	virtual uint8_t GetBullet() const = 0;  // returns the velocity of the projectile
	
};

