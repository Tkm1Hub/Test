#include "stdafx.h"
#include "Animation.h"
#include "Time.h"

void Animation::LoadModel(int handle)
{
	modelHandle = handle;
}

void Animation::AddAnimation(
	int animID,
	int animHandle
)
{
	animTable[animID] = animHandle;
}

void Animation::Play(int animIndex, bool loop)
{
	//--------------------------------
	// 同じアニメなら無視
	//--------------------------------

	if (currentAnimIndex == animIndex)
	{
		return;
	}

	//--------------------------------
	// アニメ存在チェック
	//--------------------------------

	if (animTable.find(animIndex) ==
		animTable.end())
	{
		return;
	}

	//--------------------------------
	// 前回アニメ削除
	//--------------------------------

	if (prevPlayAnim != -1)
	{
		MV1DetachAnim(
			modelHandle,
			prevPlayAnim
		);

		prevPlayAnim = -1;
	}

	//--------------------------------
	// 現在アニメをPrevへ
	//--------------------------------

	if (currentPlayAnim != -1)
	{
		prevPlayAnim = currentPlayAnim;

		prevAnimCount =
			MV1GetAttachAnimTime(
				modelHandle,
				currentPlayAnim
			);
	}

	//--------------------------------
	// 新しいアニメを再生
	//--------------------------------

	currentPlayAnim =
		MV1AttachAnim(
			modelHandle,
			0,
			animTable[animIndex]
		);

	//--------------------------------
	// 再生失敗
	//--------------------------------

	if (currentPlayAnim == -1)
	{
		return;
	}

	//--------------------------------
	// 状態更新
	//--------------------------------

	currentAnimIndex = animIndex;

	currentAnimCount = 0.0f;

	isLoop = loop;

	isAnimFinished = false;

	animBlendRate =
		(prevPlayAnim == -1)
		? 1.0f
		: 0.0f;
}

void Animation::Update()
{
	float animTotalTime;

	//--------------------------------
	// ブレンド率更新
	//--------------------------------

	if (animBlendRate < 1.0f)
	{
		animBlendRate +=
			ANIM_BLEND_SPEED *
			Time::GetInstance().GetWorldTimeScale();

		if (animBlendRate > 1.0f)
		{
			animBlendRate = 1.0f;
		}
	}

	//=========================================================
	// 現在アニメ
	//=========================================================

	if (currentPlayAnim != -1)
	{
		animTotalTime =
			MV1GetAttachAnimTotalTime(
				modelHandle,
				currentPlayAnim
			);

		//--------------------------------
		// 再生時間更新
		//--------------------------------

		currentAnimCount +=
			ANIM_PLAY_SPEED *
			Time::GetInstance().GetWorldTimeScale();

		//--------------------------------
		// 終端処理
		//--------------------------------

		if (currentAnimCount >= animTotalTime)
		{
			if (isLoop)
			{
				currentAnimCount =
					static_cast<float>(
						fmod(
							currentAnimCount,
							animTotalTime
						)
						);
			}
			else
			{
				currentAnimCount =
					animTotalTime;

				isAnimFinished = true;
			}
		}

		//--------------------------------
		// 時間反映
		//--------------------------------

		MV1SetAttachAnimTime(
			modelHandle,
			currentPlayAnim,
			currentAnimCount
		);

		//--------------------------------
		// ブレンド率反映
		//--------------------------------

		MV1SetAttachAnimBlendRate(
			modelHandle,
			currentPlayAnim,
			animBlendRate
		);
	}

	//=========================================================
	// 前回アニメ
	//=========================================================

	if (prevPlayAnim != -1)
	{
		MV1SetAttachAnimTime(
			modelHandle,
			prevPlayAnim,
			prevAnimCount
		);

		MV1SetAttachAnimBlendRate(
			modelHandle,
			prevPlayAnim,
			1.0f - animBlendRate
		);

		if (animBlendRate >= 1.0f)
		{
			MV1DetachAnim(
				modelHandle,
				prevPlayAnim
			);

			prevPlayAnim = -1;
		}
	}
}