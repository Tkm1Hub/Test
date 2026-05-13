#include "stdafx.h"
#include "EnemyChaseState.h"
#include "Enemy.h"

void EnemyChaseState::OnStart()
{

}

void EnemyChaseState::OnUpdate()
{
	GetEnemy()->Chase();
}

void EnemyChaseState::OnExit()
{

}
