#include "Timer.h"

Timer::Timer(std::string name) : m_name(name)
{
}

std::string Timer::GetName() const
{
	return m_name;
}


