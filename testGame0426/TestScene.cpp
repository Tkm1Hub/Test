#include "stdafx.h"
#include "TestScene.h"
#include "Input.h"
#include "Debug.h"
#include "Objects.h"
#include "Player.h"
#include "Camera.h"

TestScene::TestScene(SceneManager& manager)
	:Scene{manager}{ }

TestScene::~TestScene(){}

void TestScene::Init()
{
	debug = std::make_shared<Debug>();
	objects = std::make_shared<Objects>();
	player = std::make_shared<Player>();

	// オブジェクトリストに追加
	objects->Add(player);

	// カメラ設定
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 5.0f, -10.0f), VGet(0.0f, 5.0f, 1.0f));
	SetCameraNearFar(10, 500);

}

void TestScene::Update()
{
	Input::GetInput().Update();
}

void TestScene::Draw() const
{
	debug->Draw();
	objects->Draw();
}