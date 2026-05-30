#include "stdafx.h"
#include "DamageTextUI.h"
#include "Time.h"
#include "Font.h"

void DamageTextUI::Init(
	const VECTOR& worldPos,
	int damage
)
{
	screenPos =
		ConvWorldPosToScreenPos(worldPos);

	this->damage = damage;
}

void DamageTextUI::Update()
{
	timer +=
		Time::GetInstance().GetScaledDeltaTime()
		* 60.0f;

	//--------------------------------
	// 上へ移動
	//--------------------------------

	screenPos.y += velocityY;

	//--------------------------------
	// フェードアウト
	//--------------------------------

	float rate =
		1.0f - (timer / lifeTime);

	rate = std::clamp(
		rate,
		0.0f,
		1.0f
	);

	alpha =
		static_cast<int>(255 * rate);

	//--------------------------------
	// 拡大演出
	//--------------------------------

	float scaleTime = 10.0f;

	float t =
		std::clamp(
			timer / scaleTime,
			0.0f,
			1.0f
		);

	// EaseOutQuad
	float ease =
		1.0f -
		(1.0f - t) *
		(1.0f - t);

	scale =
		1.8f +
		(1.0f - 1.8f) *
		ease;

	//--------------------------------
	// 削除
	//--------------------------------

	if (timer >= lifeTime)
	{
		isDestroy = true;
	}
}

void DamageTextUI::Draw()
{
    SetDrawBlendMode(
        DX_BLENDMODE_ALPHA,
        alpha
    );

    //--------------------------------
    // ダメージ文字列作成
    //--------------------------------

    char str[32];

    sprintf_s(
        str,
        "%d",
        damage
    );

    //--------------------------------
    // 中央揃え
    //--------------------------------

    int width =
        GetDrawStringWidthToHandle(
            str,
            static_cast<int>(strlen(str)),
            Font::DamageFont
        );

    int x =
        static_cast<int>(
            screenPos.x -
            width * scale * 0.5f
            );

    int y =
        static_cast<int>(
            screenPos.y
            );

    //--------------------------------
    // 本体描画
    // EdgeColorで縁取り
    //--------------------------------

    DrawRotaStringToHandle(
        x,
        y,
        scale,
        scale,
        0.5,
        0.5,
        0.0,
        GetColor(255, 255, 255),
        Font::DamageFont,
        GetColor(0, 0, 0),
        FALSE,
        str
    );

    SetDrawBlendMode(
        DX_BLENDMODE_NOBLEND,
        0
    );
}