#include "Camera.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"

#define CAMERA_NEAR_CLIP 0.01f
#define CAMERA_FAR_CLIP 2000.0f

#define PLAYER_DISTANCE -15.0f
#define ROTATION_SPEED 0.025f

#define X_ROTATION_MAX (DX_PI_F * 0.49f)

int stageFlg = 1;
bool CameraRollFlg = true;

float m_Roll = 0.0f;
float saveRoll = 0.0f;

float PosZ;

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

	m_Pos.z = -45.0f + PLAYER_DISTANCE;

	stageFlg = 1;

	m_Roll = 0.0f;
}

void Camera::Step()
{

}

void Camera::Update()
{
	VECTOR playerPos = m_TargetPlayer->GetPos();

	// カメラの位置
	m_Pos.x = 0.0f;                  // X固定
	m_Pos.y = 10.0f;                  // Y固定
	m_Pos.z += 0.2;

	m_Target.x = 5.0f * sinf(m_Roll);
	m_Target.y = 10.0f - 5.0f * cosf(m_Roll);
	m_Target.z = m_Pos.z - PLAYER_DISTANCE;

	if (Input::IsTriggerKey(KEY_D) && stageFlg == 1 && CameraRollFlg)
	{
		stageFlg = 2;
		CameraRollFlg = false;
	}
	else if (Input::IsTriggerKey(KEY_A) && stageFlg == 1 && CameraRollFlg)
	{
		stageFlg = 4;
		CameraRollFlg = false;
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

	PosZ = m_Pos.z;

	if (GetStageRollFlg())
	{
		CameraRollFlg = true;
	}

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

float GetCameraPosZ()
{
	return PosZ;
}