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
#include "PlayerBulletUI.h"
#include "TargetMarkerUI.h"
#include "UIContainer.h"
#include "EffectContainer.h"
#include "Font.h"
#include "Stage.h"
#include "Shadow.h"
#include "StageCollision.h"
#include "Sword.h"

TestScene::TestScene(SceneManager& manager)
	:Scene{manager}{ }

TestScene::~TestScene(){}

void TestScene::Init()
{
	// オブジェクト生成
	auto stage = std::make_shared<Stage>();
	debug = std::make_shared<Debug>();
	player = std::make_shared<Player>();
	auto sword = std::make_shared<Sword>();
	camera = std::make_shared<Camera>();
	shadow = std::make_shared<Shadow>();

	camera->SetPlayer(player);
	player->SetCamera(camera);
	sword->SetOwner(player);

	// オブジェクトリストに追加
	Objects::GetInstance().Add(stage);
	Objects::GetInstance().Add(player);
	Objects::GetInstance().Add(sword);

	// オブジェクト初期化
	camera->Init();

	EffectContainer::GetInstance().Init();

	StageCollision::GetInstance().SetStageCollision(stage->GetModelHandle());

	Font::Init();

	shadow->Init();

	// UI生成
	auto playerHPUI = std::make_shared<PlayerHPUI>();
	playerHPUI->SetPlayer(player.get());
	auto playerBulletUI = std::make_shared<PlayerBulletUI>();
	playerBulletUI->SetPlayer(player.get());
	auto targetMarkerUI = std::make_shared<TargetMarkerUI>();
	targetMarkerUI->SetPlayer(player.get());

	// UIリスト追加
	UIContainer::GetInstance().Add(playerHPUI);
	UIContainer::GetInstance().Add(playerBulletUI);
	UIContainer::GetInstance().Add(targetMarkerUI);

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
	debug->Update();

	// デバッグ：Meleeスポーン
	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_DPAD_UP))
	{
		auto enemy = std::make_shared<EnemyMelee>();

		enemy->SetPlayer(player);

		Objects::GetInstance().Add(enemy);

		enemy->SetPosition(player->GetPosition());
	}

	// デバッグ：Shooterスポーン
	if (Input::GetInput().IsTrigger(XINPUT_BUTTON_DPAD_RIGHT))
	{
		auto enemy = std::make_shared<EnemyShooter>();

		enemy->SetPlayer(player);

		Objects::GetInstance().Add(enemy);
		
		enemy->SetPosition(player->GetPosition());
	}


	UIContainer::GetInstance().Update();
	Objects::GetInstance().Update();
	camera->Update();

	shadow->Update(player->GetPosition());

	EffectContainer::GetInstance().Update();

}

void TestScene::Draw() const
{
	clsDx();

	//シャドウマップの準備
	ShadowMap_DrawSetup(shadow->GetShadowMapHandle());

	// 影有効オブジェクトの描画
	Objects::GetInstance().Draw();

	//シャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, shadow->GetShadowMapHandle());

	// オブジェクトの描画
	Objects::GetInstance().Draw();

	// 描画に使用するシャドウマップの設定を解除
	SetUseShadowMap(0, -1);

	// デバッグの描画
	debug->Draw();

	// エフェクトの描画
	EffectContainer::GetInstance().Draw();

	// UIの描画
	UIContainer::GetInstance().Draw();
}