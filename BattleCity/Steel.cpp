#include "Steel.h"

const std::string Steel::GetType() const
{
	return m_type;
}

bool Steel::IsPassable() const
{
	return m_isPassable;
}

bool Steel::IsBreakable() const
{
	return m_isBreakable;
}
