#pragma once
#include "Scene.h"

class TitleScene :public Scene
{
public:
	TitleScene(SceneManager& manager);
	~TitleScene();

	void Init() override;
	void Update() override;
	void Draw() const override;

};