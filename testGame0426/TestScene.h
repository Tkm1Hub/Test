#pragma once
#include "Scene.h"

class Debug;
class Player;
class Camera;
class TestScene :public Scene
{
public:
	TestScene(SceneManager& manager);
	~TestScene();

	void Init() override;
	void Update() override;
	void Draw() const override;


private:
	std::shared_ptr<Debug> debug = nullptr;
	std::shared_ptr<Player> player = nullptr;
	std::shared_ptr<Camera> camera = nullptr;
};