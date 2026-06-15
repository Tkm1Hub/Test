#include "stdafx.h"
#include "ParameterContainer.h"
#include "AttackData.h"
#include <fstream>

using json = nlohmann::json;

void ParameterContainer::Load()
{
    std::ifstream file("data/json/Player.json");

    if (!file.is_open())
    {
        return;
    }

    json j;
    file >> j;

    playerParameter.HP = j["HP"];
    playerParameter.BulletNum = j["BulletNum"];
    playerParameter.attackPower = j["attackPower"];
    playerParameter.stunPower = j["stunPower"];

    playerParameter.scale =
    {
        j["scale"]["x"],
        j["scale"]["y"],
        j["scale"]["z"]
    };

    playerParameter.moveAccel = j["move"]["moveAccel"];
    playerParameter.moveDecel = j["move"]["moveDecel"];
    playerParameter.maxMoveSpeed = j["move"]["maxMoveSpeed"];
    playerParameter.jumpPower = j["move"]["jumpPower"];
    playerParameter.angleSpeed = j["move"]["angleSpeed"];

    playerParameter.aimTriggerDeadZone = j["aim"]["aimTriggerDeadZone"];
    playerParameter.fireTriggerDeadZone = j["aim"]["fireTriggerDeadZone"];
    playerParameter.fireKnockBackPower = j["aim"]["fireKnockBackPower"];

    playerParameter.SearchEnemyDistance = j["attack"]["SearchEnemyDistance"];

    playerParameter.dodgeSpeed = j["dodge"]["dodgeSpeed"];
    playerParameter.dodgeTime = j["dodge"]["dodgeTime"];

    playerParameter.bodyHeight = j["collision"]["bodyHeight"];
    playerParameter.bodyRadius = j["collision"]["bodyRadius"];
    playerParameter.extraHitRadius = j["collision"]["extraHitRadius"];

    playerParameter.bulletSpeed = j["bullet"]["bulletSpeed"];

    auto& bullet = j["bullet"]["attackStep"];

    playerParameter.bullet.windupTime = bullet["windupTime"];
    playerParameter.bullet.activeTime = bullet["activeTime"];
    playerParameter.bullet.recoveryTime = bullet["recoveryTime"];

    playerParameter.bullet.damage = bullet["damage"];
    playerParameter.bullet.stunPower = bullet["stunPower"];

    playerParameter.bullet.attackMoveSpeed = bullet["attackMoveSpeed"];
    playerParameter.bullet.attackHitRadius = bullet["attackHitRadius"];
    playerParameter.bullet.attackForwardOffset = bullet["attackForwardOffset"];

    playerParameter.bullet.knockBackPower = bullet["knockBackPower"];

    playerParameter.combo.clear();

    for (auto& c : j["combo"])
    {
        AttackStep step;

        step.windupTime = c["windupTime"];
        step.activeTime = c["activeTime"];
        step.recoveryTime = c["recoveryTime"];
        step.damage = c["damage"];
        step.stunPower = c["stunPower"];
        step.attackMoveSpeed = c["attackMoveSpeed"];
        step.attackHitRadius = c["attackHitRadius"];
        step.attackForwardOffset = c["attackForwardOffset"];
        step.knockBackPower = c["knockBackPower"];

        playerParameter.combo.push_back(step);
    }

    playerParameter.SPAttack.clear();
    for (auto& c : j["SPAttack"])
    {
        AttackStep step;

        step.windupTime = c["windupTime"];
        step.activeTime = c["activeTime"];
        step.recoveryTime = c["recoveryTime"];
        step.damage = c["damage"];
        step.stunPower = c["stunPower"];
        step.attackMoveSpeed = c["attackMoveSpeed"];
        step.attackHitRadius = c["attackHitRadius"];
        step.attackForwardOffset = c["attackForwardOffset"];
        step.knockBackPower = c["knockBackPower"];

        playerParameter.SPAttack.push_back(step);
    }


}