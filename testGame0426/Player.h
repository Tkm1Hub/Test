#pragma once
#include "Object.h"

class Camera;
class Player :public Object
{
public:
	int HP;			// 体力
	int Energy;		// 射撃用エネルギー

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetCamera();

	const VECTOR& GetModelForward() const { return modelFoward; }

private:
	void PlayerMove();

	std::weak_ptr<Camera> camera;

	VECTOR moveVec;

	float moveSpeed = 0.5f;
	bool isMove;
};