#pragma once
#include "PowerUp.h"
#include <string>

class TankP : public PowerUp
{
public:
	TankP(std::string name);
	std::string GetName() const override;

private:
	std::string m_name;
};