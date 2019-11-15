#include "Helmet.h"

Helmet::Helmet(std::string name) : m_name(name)
{
}

std::string Helmet::GetName() const
{
	return m_name;
}
