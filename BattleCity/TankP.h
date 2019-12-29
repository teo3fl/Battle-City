#pragma once

#include "PowerUp.h"

class TankP : public PowerUp
{
public:
	TankP(std::string name);
	std::string GetName() const override;

private:
	std::string m_name;
};