#include "stdafx.h"
#include "TestScene.h"
#include "Input.h"
#include "Debug.h"
#include "Objects.h"
#include "Player.h"
#include "Camera.h"
#include "Time.h"
#include "EnemyMelee.h"
#include "PlayerHPUI.h"
#include "UIManager.h"

TestScene::TestScene(SceneManager& manager)
	:Scene{manager}{ }

TestScene::~TestScene(){}

void TestScene::Init()
{
	// オブジェクト生成
	debug = std::make_shared<Debug>();
	player = std::make_shared<Player>();
	camera = std::make_shared<Camera>();
	enemyMelee = std::make_shared<EnemyMelee>();

	camera->SetPlayer(player);
	player->SetCamera(camera);
	enemyMelee->SetPlayer(player);

	// オブジェクトリストに追加
	Objects::GetInstance().Add(player);
	Objects::GetInstance().Add(enemyMelee);

	// オブジェクト初期化
	Objects::GetInstance().Init();
	camera->Init();
	enemyMelee->Init();

	// UI生成
	auto playerHPUI = std::make_shared<PlayerHPUI>();
	playerHPUI->SetPlayer(player.get());

	// UIリスト追加
	UIManager::GetInstance().Add(playerHPUI);

	SetMaterialUseVertSpcColor(false);

	MATERIALPARAM Material;

	Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
	Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Emissive = GetColorF(0.0f, 0.0f, 0.1f, 0.0f);
	Material.Power = 20.0f;
	SetMaterialParam(Material);

	SetLightDifColor(GetColorF(0.7f, 0.7f, 0.7f, 0.0f));
}

void TestScene::Update()
{
	Input::GetInput().Update();
	Time::GetInstance().Update();
	Objects::GetInstance().Update();
	camera->Update();
	UIManager::GetInstance().Update();
}

void TestScene::Draw() const
{
	debug->Draw();
	Objects::GetInstance().Draw();
	UIManager::GetInstance().Draw();
}