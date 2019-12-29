#pragma once

#include "PowerUp.h"

class Helmet : public PowerUp
{
public:
	Helmet(std::string name);
	std::string GetName() const override;

private:
	const std::string m_name;
};