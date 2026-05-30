#include "stdafx.h"
#include "SceneManager.h"
#include "TestScene.h"

//画面設定
int constexpr SCREEN_WIDTH = 1920;
int constexpr SCREEN_HEIGHT = 1080;
int constexpr SCREEN_COLOR = 32;


///<summary>
///main
/// </summary>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//全画面モード
	ChangeWindowMode(FALSE);

	// 画面のサイズと色深度の設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);

	//DXライブラリの初期化
	if (DxLib_Init() == -1)return -1;

	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	Effekseer_Set2DSetting(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	// 裏画面に描画
	SetDrawScreen(DX_SCREEN_BACK);

	std::shared_ptr<SceneManager> sceneManager = std::make_shared<SceneManager>();

	sceneManager->Add<TestScene>("Test");

	//メインループ開始、ESCキーで終了
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// DXライブラリのカメラとEffekseerのカメラを同期する。
		Effekseer_Sync3DSetting();

		auto prevTime = GetNowHiPerformanceCount();//処理が始まる前の時間

		sceneManager->Update();

		ClearDrawScreen();//画面の初期化

		sceneManager->Draw();

		ScreenFlip(); // 画面の更新

		// 雑なfps固定処理
		// 差を求めて、1回の画面更新が1/60秒になるようにwhileループ回して待つ
		auto afterTime = GetNowHiPerformanceCount(); // 処理が終わった後の時間
		while (afterTime - prevTime < 16667)
		{
			afterTime = GetNowHiPerformanceCount();
		}
	}

	// Effekseerを終了する。
	Effkseer_End();

	//Dxライブラリの後始末
	DxLib_End();

	//終了
	return 0;
}