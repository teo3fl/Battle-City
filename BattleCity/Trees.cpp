#include "Trees.h"

const std::string Trees::GetType() const
{
	return m_type;
}

bool Trees::IsPassable() const
{
	return m_isPassable;
}

bool Trees::IsBreakable() const
{
	return m_isBreakable;
}
