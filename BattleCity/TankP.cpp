#include "stdafx.h"
#include "TankP.h"

TankP::TankP(std::string name) : m_name(name)
{
}

std::string TankP::GetName() const
{
	return m_name;
}
