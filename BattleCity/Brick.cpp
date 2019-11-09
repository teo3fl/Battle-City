#include "Brick.h"



const std::string Brick::GetType() const
{
	return m_type;
}

bool Brick::IsPassable() const
{
	return m_isPassable;
}

bool Brick::IsBreakable() const
{
	return m_isBreakable;
}
