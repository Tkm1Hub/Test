#pragma once
#include "Object.h"

class Stage : public Object
{
public:
	void Init() override;
	void Draw() override;

private:
	int stageModelHandle = -1;
};