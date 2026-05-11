#include "Camera.h"
#include "stdafx.h"
#include "Player.h"
#include "Input.h"

void Camera::SetPlayer(const std::weak_ptr<Player>& playerPtr)
{
	player = playerPtr;
}

void Camera::Init()
{
	angleV = 0.0f; // 上下角度リセット
	angleH = 0.0f; // 水平角度リセット

	if (auto p = player.lock())
	{
		VECTOR playerPos = p->GetPosition();
		VECTOR forward = p->GetModelForward(); // プレイヤーの前方向

		// 注視点はプレイヤーの頭上
		target = VAdd(playerPos, VGet(0.0f, LOOK_OFFSET_Y, 0.0f));

		// カメラはプレイヤーの後ろにDISTANCE_OFFSETだけ離す
		pos = VSub(target, VScale(forward, DISTANCE_OFFSET));

	}

}


void Camera::MoveCamera()
{

}