#include "Ice.h"

const std::string Ice::GetType() const
{
	return m_type;
}

bool Ice::IsPassable() const
{
	return m_isPassable;
}

bool Ice::IsBreakable() const
{
	return m_isBreakable;
}