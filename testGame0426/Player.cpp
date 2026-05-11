#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

void Player::Init()
{

}

void Player::Update()
{

}

void Player::Draw()
{
	DrawCapsule3D(pos, VAdd(pos, VGet(0.0f, 1.7f, 0.0f)), 0.5f, 8, GetColor(18, 105, 204), GetColor(255, 255, 255),TRUE);
}

void Player::PlayerMove()
{
	// HACK: 移動距離が0.01未満で微妙に移動していた場合はじんわり移動してバグる
// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if (fabs(moveVec.x) > 0.01f || fabs(moveVec.z) > 0.01f)
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}

	// Inputから移動ベクトルを取得


	// 移動速度を計算


	pos = VAdd(pos, moveVec);
}