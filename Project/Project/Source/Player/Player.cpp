#include "Player.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../StageObject/StageObject.h"
#include "../Camera/Camera.h"

#define ROTATION_SPEED	0.1f
#define MOVE_SPEED_AUTO	0.1f
#define MOVE_SPEED		0.3
#define JUMP_POW		0.25f
#define GRAVITY			0.01f

int StageRoll = 1;

// コンストラクタ
Player::Player()
{
	// コンストラクタではメンバ変数を0初期化するくらい
	// ややこしい処理はしないこと
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0, 0.0f, 0.0f);
	m_PrevPos = VGet(0.0, 0.0f, 0.0f);
	m_AABB = nullptr;
	m_SphereCollision = nullptr;
	m_IsGoal = false;
}

// デストラクタ
Player::~Player()
{
	// 終了処理を呼べば削除した時の後始末忘れを防げる
	Fin();
}

// 初期化
void Player::Init()
{
}

// ロード
void Player::Load()
{
	// 3Dモデルをロードする
	m_Handle = MV1LoadModel("Data/Player/Player.x");
}

// 開始
void Player::Start()
{
	// 移動量を初期化
	m_Move = VGet(0.0, 0.0f, 0.0f);

	// AABBの当たり判定を設定
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
	m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));

	// 球の当たり判定を設定
	m_SphereCollision = CollisionManager::GetInstance()->CreateSphere();
	m_SphereCollision->SetTargetPos(&m_Pos);
	m_SphereCollision->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
	m_SphereCollision->SetRadius(0.5f);

	// ゴールフラグを折る
	m_IsGoal = false;
}

// ステップ
void Player::Step()
{
	if (GetStageCameraFlg() == 1)
	{
		if (StageRoll == 1)
		{
			m_Move = VGet(0.0, m_Move.y, 0.0f);

			m_Move.y -= GRAVITY;

			if (Input::IsInputKey(KEY_LEFT))
			{
				m_Move.x = -MOVE_SPEED;
			}
			if (Input::IsInputKey(KEY_RIGHT))
			{
				m_Move.x = MOVE_SPEED;
			}

			if (Input::IsTriggerKey(KEY_SPACE))
			{
				m_Move.y = JUMP_POW;
			}
		}
		if (StageRoll == 2)
		{
			m_Move = VGet(m_Move.x, 0.0f, 0.0f);

			m_Move.x += GRAVITY;

			if (Input::IsInputKey(KEY_LEFT))
			{
				m_Move.y = -MOVE_SPEED;
			}
			if (Input::IsInputKey(KEY_RIGHT))
			{
				m_Move.y = MOVE_SPEED;
			}

			if (Input::IsTriggerKey(KEY_SPACE))
			{
				m_Move.x = -JUMP_POW;
			}
		}
		if (StageRoll == 3)
		{
			m_Move = VGet(0.0, m_Move.y, 0.0f);

			m_Move.y += GRAVITY;

			if (Input::IsInputKey(KEY_LEFT))
			{
				m_Move.x = MOVE_SPEED;
			}
			if (Input::IsInputKey(KEY_RIGHT))
			{
				m_Move.x = -MOVE_SPEED;
			}

			if (Input::IsTriggerKey(KEY_SPACE))
			{
				m_Move.y = -JUMP_POW;
			}
		}
		if (StageRoll == 4)
		{
			m_Move = VGet(m_Move.x, 0.0f, 0.0f);

			m_Move.x -= GRAVITY;

			if (Input::IsInputKey(KEY_LEFT))
			{
				m_Move.y = MOVE_SPEED;
			}
			if (Input::IsInputKey(KEY_RIGHT))
			{
				m_Move.y = -MOVE_SPEED;
			}

			if (Input::IsTriggerKey(KEY_SPACE))
			{
				m_Move.x = JUMP_POW;
			}
		}
	}
	else
	{
		m_Move = VGet(0.0f, 0.0f, 0.0f);
	}

	m_Move.z = MOVE_SPEED_AUTO;

	if (Input::IsTriggerKey(KEY_D) && GetStageCameraFlg() == 1)
	{
		if (StageRoll == 4)
		{
			StageRoll = 1;
		}
		else
		{
			StageRoll++;
		}
	}
	if (Input::IsTriggerKey(KEY_A) && GetStageCameraFlg() == 1)
	{
		if (StageRoll == 1)
		{
			StageRoll = 4;
		}
		else
		{
			StageRoll--;
		}
	}

	// 移動前の座標を記録
	m_PrevPos = m_Pos;

	// 移動量を反映
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
}

// 更新
void Player::Update()
{

	// 3Dモデルの座標を設定する
	MV1SetPosition(m_Handle, m_Pos);
	// 3Dモデルの回転値を設定する
	MV1SetRotationXYZ(m_Handle, m_Rot);
	// 3Dモデルのスケールを設定する
	MV1SetScale(m_Handle, m_Scale);
}

// 描画
void Player::Draw()
{
	// 3Dモデルを描画する
	MV1DrawModel(m_Handle);

	// 座標を描画する
	DrawFormatString(0, 0, GetColor(255, 255, 255), "座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);

	// 回転値を描画する
	DrawFormatString(0, 20, GetColor(255, 255, 255), "stageFlg::%d", StageRoll);

	
}

// 終了
void Player::Fin()
{
	// モデルをメモリから削除
	MV1DeleteModel(m_Handle);
}

void Player::CheckHitStageObjects(const std::vector<StageObject*> objects)
{
	// 移動前の座標に戻す
	m_Pos = m_PrevPos;

	// X軸だけ移動させて当たり判定
	m_Pos.x += m_Move.x;
	for (auto obj : objects)
	{
		const CollisionAABB* objAABB = obj->GetAABB();
		if (!objAABB) continue;

		if (m_AABB->CheckAABB(objAABB))
		{
			m_Pos.x = m_PrevPos.x;
		}
	}

	// Y軸だけ移動させて当たり判定
	m_Pos.y += m_Move.y;
	for (auto obj : objects)
	{
		const CollisionAABB* objAABB = obj->GetAABB();
		if (!objAABB) continue;

		if (m_AABB->CheckAABB(objAABB))
		{
			m_Pos.y = m_PrevPos.y;
			m_Move.y = 0.0f;// 着地
		}
	}

	// Z軸だけ移動させて当たり判定
	m_Pos.z += m_Move.z;
	for (auto obj : objects)
	{
		const CollisionAABB* objAABB = obj->GetAABB();
		if (!objAABB) continue;

		if (m_AABB->CheckAABB(objAABB))
		{
			m_Pos.z = m_PrevPos.z;
		}
	}
}

void Player::HitGoal()
{
	m_IsGoal = true;
}

int GetStageRollFlg()
{
	return StageRoll;
}