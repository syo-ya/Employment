#pragma once
#include "DxLib.h"
#include <vector>

// ヘッダーにインクルードを書きたくないので前方定義
class CollisionAABB;
class CollisionSphere;
class StageObject;

int GetStageRollFlg();

enum PlayerAnimationType
{
	PLAYER_ANIMATION_JUMP = 1,
	PLAYER_ANIMATION_RUN = 2,
};

// プレイヤークラス
class Player 
{
public:
	Player();	// コンストラクタ
	~Player();	// デストラクタ

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

public:
	VECTOR GetPos() { return m_Pos; }
	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphereCollision() { return m_SphereCollision; }

	void SetTransform(VECTOR pos, VECTOR rot, VECTOR scale) { m_Pos = pos; m_Rot = rot; m_Scale = scale; }

public:
	void CheckHitStageObjects(const std::vector<StageObject*>objects);
	void HitGoal();
	void PlayAnimation(PlayerAnimationType anim, bool isLoop);
	void UpdateAnimation();
	
private:
	int m_Handle;	// 画像ハンドル
	int m_AnimationAttachIndex;	// アニメーションのアタッチインデックス
	float m_AnimationTotalTime;	// 再生中のアニメーションの総時間
	float m_AnimationNowTime;	// 再生中のアニメーションの再生時間
	bool m_IsLoopAnimation;		// アニメーションをループさせるか
	PlayerAnimationType m_NowAnimation;	// 再生中のアニメーション
	VECTOR m_Pos;	// 座標
	VECTOR m_Rot;	// 回転
	VECTOR m_Scale;	// スケール
	VECTOR m_Move;	// 移動量
	VECTOR m_PrevPos; // 前回の座標
	CollisionAABB* m_AABB;	// AABBの当たり判定
	CollisionSphere* m_SphereCollision;
	bool m_IsGoal;
};

