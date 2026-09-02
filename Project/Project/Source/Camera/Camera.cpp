#include "Camera.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"

#define CAMERA_NEAR_CLIP 0.01f
#define CAMERA_FAR_CLIP 1000.0f

#define PLAYER_DISTANCE -15.0f
#define ROTATION_SPEED 0.025f

#define X_ROTATION_MAX (DX_PI_F * 0.49f)

int stageFlg = 1;

float m_Roll = 0.0f;
float saveRoll = 0.0f;

// 基底クラスのコンストラクタ呼ぶ際は追加で書く
Camera::Camera() : CameraBase()
{
	m_TargetPlayer = nullptr;
}

Camera::~Camera()
{
	Fin();
}

void Camera::Init()
{
}

void Camera::Load()
{
}

void Camera::Start()
{
	// ニア、ファークリップの設定
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	// アップベクトル設定
	m_UpVec = VGet(0.0f, 1.0f, 0.0f);

	// 追従するプレイヤー
	m_TargetPlayer = PlayerManager::GetInstance()->GetPlayer();
}

void Camera::Step()
{
	// キー入力処理
	if (Input::IsInputKey(KEY_A))
	{
		// 左回転
		m_Rot.z += ROTATION_SPEED;
	}
	if (Input::IsInputKey(KEY_D))
	{
		// 右回転
		m_Rot.z -= ROTATION_SPEED;
	}
	if (Input::IsInputKey(KEY_W))
	{
		// 手前回転
		m_Rot.x += ROTATION_SPEED;
	}
	if (Input::IsInputKey(KEY_S))
	{
		// 奥回転
		m_Rot.x -= ROTATION_SPEED;
	}

	// X軸回転は頭上や足元を超えようとするとカメラ向きがひっくり返るため
	// 超えないように止める
	if (m_Rot.x >= X_ROTATION_MAX)
	{
		m_Rot.x = X_ROTATION_MAX;
	}
	else if (m_Rot.x <= -X_ROTATION_MAX)
	{
		m_Rot.x = -X_ROTATION_MAX;
	}
}

void Camera::Update()
{
	VECTOR playerPos = m_TargetPlayer->GetPos();

	// カメラの位置
	m_Pos.x = 0.0f;                  // X固定
	m_Pos.y = 10.0f;                  // Y固定
	m_Pos.z = playerPos.z + PLAYER_DISTANCE;

	m_Target.x = 5.0f * sinf(m_Roll);
	m_Target.y = 10.0f - 5.0f * cosf(m_Roll);
	m_Target.z = playerPos.z;

	if (Input::IsTriggerKey(KEY_D) && stageFlg == 1)
	{
		stageFlg = 2;
	}
	else if (Input::IsTriggerKey(KEY_A) && stageFlg == 1)
	{
		stageFlg = 4;
	}

	if (stageFlg == 2)
	{
		saveRoll = m_Roll;
		stageFlg = 3;
	}
	else if(stageFlg == 4)
	{
		saveRoll = m_Roll;
		stageFlg = 5;
	}

	if (stageFlg == 3)
	{
		m_Roll += 0.05f;

		if (m_Roll >= saveRoll + DX_PI_F / 2.0f)
		{
			m_Roll = saveRoll + DX_PI_F / 2.0f;
			saveRoll = 0.0f;
			stageFlg = 1;
		}
	}
	if (stageFlg == 5)
	{
		m_Roll -= 0.05f;

		if (m_Roll <= saveRoll - DX_PI_F / 2.0f)
		{
			m_Roll = saveRoll - DX_PI_F / 2.0f;
			saveRoll = 0.0f;
			stageFlg = 1;
		}
	}

	m_UpVec = VGet(
		-sinf(m_Roll),
		cosf(m_Roll),
		0.0f
	);

	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

void Camera::Draw()
{
	DrawFormatString(0, 60, GetColor(255, 255, 255), "カメラの座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
}

void Camera::Fin()
{

}

int GetStageCameraFlg()
{
	return stageFlg;
}

float GetRoll()
{
	return m_Roll;
}