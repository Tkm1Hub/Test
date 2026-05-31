#include "stdafx.h"
#include "PlayerDamageState.h"

#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerWalkState.h"

#include "Input.h"
#include "Time.h"

void PlayerDamageState::OnStart()
{
    auto player = GetPlayer();
    if (!player) return;

    // 被弾情報取得
    const DamageInfo& info =
        player->GetLastDamageInfo();

    // ダメージ適用
    player->TakeDamage(info.damage);

    // ノックバック
    player->SetExternalVelocity(
        VScale(info.hitDir, info.knockBackPower)
    );

    // 地面解除
    player->SetIsGround(false);

    // 移動停止
    player->SetMoveVelocity(
        VGet(0.0f, 0.0f, 0.0f)
    );
}

void PlayerDamageState::OnUpdate()
{
    auto player = GetPlayer();
    if (!player) return;

    timer +=
        Time::GetInstance().GetScaledDeltaTime()
        * 60.0f;

    // 被弾終了
    if (timer >= player->GetParam().damageTime)
    {
        // 移動入力ある
        if (Input::GetInput().GetIsMoveLStick())
        {
            auto state =
                std::make_shared<PlayerWalkState>();

            player->ChangeState(state);
            return;
        }
        else
        {
            auto state =
                std::make_shared<PlayerIdleState>();

            player->ChangeState(state);
            return;
        }
    }
}

void PlayerDamageState::OnExit()
{

}