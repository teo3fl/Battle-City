#include "stdafx.h"
#include "Grenade.h"

Grenade::Grenade(std::string name) : m_name(name)
{
}

std::string Grenade::GetName() const
{
	return m_name;
}


