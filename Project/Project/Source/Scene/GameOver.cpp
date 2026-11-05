#include "DxLib.h"
#include "GameOver.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"

GameOver::GameOver() : SceneBase()
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
}

void GameOver::Load()
{
}

void GameOver::Start()
{
}

void GameOver::Step()
{
	// Zキーでタイトルシーンへ
	if (Input::IsTriggerKey(KEY_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene(TITLE);
	}
}

void GameOver::Update()
{
}

void GameOver::Draw()
{
	DrawString(0, 0, "ゲームオーバーシーン", GetColor(255, 255, 255));
}

void GameOver::Fin()
{
}
