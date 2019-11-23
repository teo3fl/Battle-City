#include "TypesOfEnemy.h"

TypesOfEnemy::TypesOfEnemy(TypesOfEnemy::Target target, TypesOfEnemy::Speed speed, TypesOfEnemy::Behaviour behaviour, TypesOfEnemy::Fire fire)
{}


TypesOfEnemy::Target TypesOfEnemy::GetTarget()
{
	return TypesOfEnemy::m_target;
}

TypesOfEnemy::Speed TypesOfEnemy::GetSpeed()
{
	return TypesOfEnemy::m_speed;
}

TypesOfEnemy::Behaviour TypesOfEnemy::GetBehaviour()
{
	return TypesOfEnemy::m_behaviour;
}

TypesOfEnemy::Fire TypesOfEnemy::GetFire()
{
	return TypesOfEnemy::m_fire;
}
