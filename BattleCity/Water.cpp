#include "Water.h"

const std::string Water::GetType() const
{
	return m_type;
}

bool Water::IsPassable() const
{
	return m_isPassable;
}

bool Water::IsBreakable() const
{
	return m_isBreakable;
}
