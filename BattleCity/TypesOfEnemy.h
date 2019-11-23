#pragma once

class TypesOfEnemy
{
	enum class Target { Close, Eagle };
	enum class Speed { Normal, Fast }; //Fast= 1.3*Normal
	enum class Behaviour { MoveToTarget, MoveToRandomDirection };
	enum class Fire { MovementDirection, OnTarget };

public:
	TypesOfEnemy(Target target, Speed speed, Behaviour behaviour, Fire fire);
	Target GetTarget();
	Speed GetSpeed();
	Behaviour GetBehaviour();
	Fire GetFire();

private:
	Target m_target;
	Speed m_speed;
	Behaviour m_behaviour;
	Fire m_fire;


	
};

