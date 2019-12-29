#pragma once

#include "PowerUp.h"

class Timer : public PowerUp
{
public:
	Timer(std::string name);
	std::string GetName() const override;

private:
	std::string m_name;

};