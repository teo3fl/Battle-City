#pragma once
#include "PowerUp.h"
#include <string>

class Shovel : public PowerUp
{
public:
	 Shovel(std::string name);
	 std::string GetName() const;
private:
	 std::string m_name;
};