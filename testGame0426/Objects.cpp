#include "Objects.h"
#include "CharacterCollision.h"
#include "stdafx.h"

void Objects::Add(std::shared_ptr<Object> obj)
{
	obj->Init();
	pendingObjects.push_back(obj);
}

void Objects::Init()
{
	for (auto& obj : objects)
	{
		if (obj->GetIsActive())
			obj->Init();
	}
}

void Objects::Update()
{
	// オブジェクトの更新
	UpdateObjects();

	//キャラクター同士の当たり判定
	CharacterCollision::Resolve();

	// 無効オブジェクトの削除
	DestroyObjects();
}

void Objects::Draw()
{
	for (auto& obj : objects)
	{
		if (obj->GetIsActive())
			obj->Draw();
	}
}

void Objects::UpdateObjects()
{
	for (auto& obj : objects)
	{
		if (!obj) continue;

		if (obj->GetIsActive())
			obj->Update();
	}

	// 追加予約を反映
	for (auto& obj : pendingObjects)
	{
		objects.push_back(obj);
	}

	pendingObjects.clear();
}

void Objects::DestroyObjects()
{
	// 無効オブジェクトを削除
	objects.erase(
		std::remove_if(
			objects.begin(),
			objects.end(),
			[](const std::shared_ptr<Object>& obj)
			{
				return obj->GetIsDestoroy();
			}
		),
		objects.end()
	);
}