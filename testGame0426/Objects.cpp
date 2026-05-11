#include "Objects.h"
#include "stdafx.h"

void Objects::Add(std::shared_ptr<Object> obj)
{
	objects.push_back(obj);
}

void Objects::Init()
{
	for (auto obj : objects)
	{
		if (obj->GetIsActive())
			obj->Init();
	}
}

void Objects::Update()
{
	for (auto obj : objects)
	{
		if (obj->GetIsActive()) 
			obj->Update();
	}
}

void Objects::Draw()
{
	for (auto obj : objects)
	{
		if (obj->GetIsActive())
			obj->Draw();
	}
}