#pragma once
#include "SceneBase.h"

class GameOver : public SceneBase
{
public:
	GameOver();
	~GameOver();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;
};


