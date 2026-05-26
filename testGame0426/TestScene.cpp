#include "stdafx.h"
#include "TestScene.h"
#include "Input.h"
#include "Debug.h"
#include "Objects.h"
#include "Player.h"
#include "Camera.h"
#include "Time.h"
#include "EnemyMelee.h"
#include "EnemyShooter.h"
#include "PlayerHPUI.h"
#include "UIContainer.h"
#include "EffectContainer.h"

TestScene::TestScene(SceneManager& manager)
	:Scene{manager}{ }

TestScene::~TestScene(){}

void TestScene::Init()
{
	// オブジェクト生成
	debug = std::make_shared<Debug>();
	player = std::make_shared<Player>();
	camera = std::make_shared<Camera>();
	auto enemyMelee = std::make_shared<EnemyMelee>();

	camera->SetPlayer(player);
	player->SetCamera(camera);
	enemyMelee->SetPlayer(player);

	// オブジェクトリストに追加
	Objects::GetInstance().Add(player);
	Objects::GetInstance().Add(enemyMelee);

	// オブジェクト初期化
	camera->Init();

	EffectContainer::GetInstance().Init();

	// UI生成
	auto playerHPUI = std::make_shared<PlayerHPUI>();
	playerHPUI->SetPlayer(player.get());

	// UIリスト追加
	UIContainer::GetInstance().Add(playerHPUI);

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

	// デバッグ：Meleeスポーン
	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_DPAD_UP))
	{
		auto enemy = std::make_shared<EnemyMelee>();

		enemy->SetPlayer(player);

		Objects::GetInstance().Add(enemy);
	}

	// デバッグ：Shooterスポーン
	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_DPAD_RIGHT))
	{
		auto enemy = std::make_shared<EnemyShooter>();

		enemy->SetPlayer(player);

		Objects::GetInstance().Add(enemy);
	}


	UIContainer::GetInstance().Update();
	Objects::GetInstance().Update();
	camera->Update();

	EffectContainer::GetInstance().Update();

}

void TestScene::Draw() const
{
	Objects::GetInstance().Draw();

	debug->Draw();

	EffectContainer::GetInstance().Draw();

	UIContainer::GetInstance().Draw();
}