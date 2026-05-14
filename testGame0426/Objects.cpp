#include "Objects.h"
#include "stdafx.h"

void Objects::Add(std::shared_ptr<Object> obj)
{
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
	for (auto& obj : objects)
	{
		if (obj->GetIsActive()) 
			obj->Update();
	}

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

	// 追加予約を反映
	for (auto& obj : pendingObjects)
	{
		obj->Init();
		objects.push_back(obj);
	}

	pendingObjects.clear();
}

void Objects::Draw()
{
	for (auto& obj : objects)
	{
		if (obj->GetIsActive())
			obj->Draw();
	}
}

