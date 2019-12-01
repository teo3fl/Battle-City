#pragma once
#include <string>
#include <iostream>
#include "TypesOfEnemy.h"
#include <list>
#include <vector>

class Enemy
{ 
public:
	Enemy();
	~Enemy();
	void CreateEnemy();
	void DestroyEnemy();
	void SetEnemyType();
	uint16_t getID();
	uint32_t getNumberOfEnemies();

private:
	uint32_t m_numberOfEnemies;
	uint16_t m_id;
	std::list<Enemy*> m_Enemies;         
	std::vector<TypesOfEnemy> m_EnemiesType;  
	
		


};

