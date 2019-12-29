#include "stdafx.h"
#include "Shovel.h"

Shovel::Shovel(std::string name) : m_name(name)
{
}

std::string Shovel::GetName() const
{
	return m_name;
}