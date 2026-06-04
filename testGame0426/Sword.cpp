#include "stdafx.h"
#include "Sword.h"
#include "Player.h"

void Sword::Init()
{
	modelHandle = MV1LoadModel("data/model/Sword.mv1");
	
}

void Sword::Update()
{
	auto player = owner.lock();
	if (!player)return;

	//Player‚ÌŽè‚Ìƒ{[ƒ“‚ðŽæ“¾
	MATRIX handMat = player->GetHandMatrix();

	alpha = player->GetAlpha();
	MV1SetMatrix(modelHandle, handMat);

	VECTOR rot = MV1GetRotationXYZ(modelHandle);
	rot = VAdd(rot, VGet(180.0f, 0.0f, 0.0f));
	MV1SetRotationXYZ(modelHandle, rot);
}

void Sword:: Draw()
{
	Object::Draw();
}