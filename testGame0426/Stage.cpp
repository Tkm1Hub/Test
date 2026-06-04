#include "stdafx.h"
#include "Stage.h"

void Stage::Init()
{
	modelHandle = MV1LoadModel("data/model/Collision.mv1");
	stageModelHandle = MV1LoadModel("data/model/Stage.mv1");
	pos = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(1.5f, 1.5f, 1.5f);
	MV1SetPosition(modelHandle,pos);
	MV1SetScale(modelHandle, scale);
	MV1SetScale(stageModelHandle, scale);
}

void Stage::Draw()
{
	//MV1DrawModel(modelHandle);
	MV1DrawModel(stageModelHandle);
}