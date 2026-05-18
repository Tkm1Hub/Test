#include "stdafx.h"
#include "AttackToken.h"
#include "Enemy.h"

bool AttackToken::
RequestToken(Enemy* enemy)
{
    // Šù‚É‚Á‚Ä‚é
    if (HasToken(enemy))
        return true;

    // –ˆõ
    if (attackers.size() >= maxAttackers)
        return false;

    attackers.insert(enemy);

    return true;
}

void AttackToken::
ReleaseToken(Enemy* enemy)
{
    attackers.erase(enemy);
}

bool AttackToken::
HasToken(Enemy* enemy)
{
    return attackers.contains(enemy);
}