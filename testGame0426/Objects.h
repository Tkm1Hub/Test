#pragma once
#include "object.h"
class Objects
{
public:
	std::vector<std::shared_ptr<Object>> objects;

	void Add(std::shared_ptr<Object> obj);
	void Update();
	void Draw();
};