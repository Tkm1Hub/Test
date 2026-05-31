#pragma once
#include "CharacterBase.h"

struct StageCollisionResult
{
	VECTOR position;      // 補正後座標

	bool isGround = false;
	bool hitRoof = false;
};

class StageCollision
{
private:
	// コンストラクタを非公開にする
	StageCollision() {}

	// コピーコンストラクタと代入演算子を削除
	StageCollision(const StageCollision&) = delete;
	StageCollision& operator=(const StageCollision&) = delete;

	~StageCollision() {}

public:
	// インスタンスを取得
	static StageCollision& GetInstance()
	{
		static StageCollision instance;
		return instance;
	}

	void SetStageCollision(const int collisionModelHandle);

	StageCollisionResult CheckCollision(CharacterBase& object, const VECTOR& moveVec);

	int GetCollisionModelHandle()const { return modelHandle; }

private:
	static const int MaxHitColl = 2048;		// 処理するコリジョンポリゴンの最大数	
	static constexpr int HitTryNum = 128;	// 壁押し出し処理の最大試行回数
	static constexpr float HitSlideLength = 0.3f;	// 一度の壁押し出し処理でスライドさせる距離
	static constexpr float DefaultSize = 300.0f;	// 周囲のポリゴン検出に使用する球の初期サイズ

	// 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);

	// 壁ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
	VECTOR CheckHitWithWall(CharacterBase& object, const VECTOR& checkPosition);

	// 床ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
	void CheckHitWithFloor(CharacterBase& object, StageCollisionResult& checkPosition);


	// HACK: 壁はXZ平面に垂直である前提で成り立っている。それ以外を置くとバグる
	int		wallNum;			    // 壁ポリゴンと判断されたポリゴンの数
	int		floorNum;			    // 床ポリゴンと判断されたポリゴンの数

	MV1_COLL_RESULT_POLY* wall[MaxHitColl];	            // 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* floor[MaxHitColl];	        // 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列

	int modelHandle = -1;
	VECTOR initPos = { 0.0f,-10.0f,10.0f };
	VECTOR modelScale = { 0.1f,0.1f,0.1f };

};