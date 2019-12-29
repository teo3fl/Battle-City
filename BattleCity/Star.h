#pragma once

#include "PowerUp.h"

class Star : public PowerUp
{
public:
	Star(std::string name);
	std::string GetName() const override;

private:
	std::string m_name;
};