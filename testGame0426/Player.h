#pragma once
#include "Object.h"
#include "PlayerParameter.h"

class Camera;
class PlayerStateBase;
class Player :public Object
{
public:
	void Init() override;
	void Update() override;
	void Draw() override;

	void SetCamera(const std::weak_ptr<Camera>& cameraPtr);

	void ChangeState(std::shared_ptr<PlayerStateBase>a_spState);		// ステート変更

	void MoveInput();		// スティックによる移動入力

	PlayerParameter& GetParam() { return param; }

private:
	PlayerParameter param;				// パラメーター
	std::weak_ptr<Camera> camera;
};