#pragma once
#include <cstdint>
#include <string>

class tank
{
public :
	virtual std::string GetName() const = 0;
	virtual uint16_t GetPoints() const = 0;
	virtual uint8_t GetHealth() const = 0;
	virtual uint8_t GetMovement() const = 0;
	virtual uint8_t GetBullet() const = 0;
};

