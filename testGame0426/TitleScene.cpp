#include "stdafx.h"
#include "TitleScene.h"
#include "Input.h"

TitleScene::TitleScene(SceneManager& manager)
	:Scene{ manager } {
}

TitleScene::~TitleScene() {}

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	Input::GetInput().Update();

	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_A))
	{
		ChangeScene("Test");
	}
}

void TitleScene::Draw() const
{
	clsDx();
	printfDx("TitleScene\n");
	printfDx("Push A Start\n");
}