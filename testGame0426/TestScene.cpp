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
	camera = std::make_shared<Camera>();

	camera->SetPlayer(player);
	player->SetCamera(camera);

	// オブジェクトリストに追加
	objects->Add(player);

	objects->Init();
	camera->Init();

	SetMaterialUseVertSpcColor(false);

	MATERIALPARAM Material;

	Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
	Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Emissive = GetColorF(0.0f, 0.0f, 0.5f, 0.0f);
	Material.Power = 20.0f;
	SetMaterialParam(Material);

	SetLightDifColor(GetColorF(0.7f, 0.7f, 0.7f, 0.0f));
}

void TestScene::Update()
{
	Input::GetInput().Update();
	objects->Update();
	camera->Update();
}

void TestScene::Draw() const
{
	debug->Draw();
	objects->Draw();
}