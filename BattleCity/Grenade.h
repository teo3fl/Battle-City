#pragma once
#include "PowerUp.h"
#include <string>

class Grenade : public PowerUp
{
public:
	Grenade(std::string name);
	std::string GetName() const override;

private:
	std::string m_name;
};