#include "stdafx.h"
#include "Star.h"

Star::Star(std::string name) : m_name(name)
{
}

std::string Star::GetName() const
{
	return m_name;
}

