#include "StageManager.h"
#include "StageParameter.h"
#include "../StageObject/StageObjectManager.h"
#include "../Player/PlayerManager.h"
#include <fstream>

StageManager* StageManager::m_Instance = nullptr;

// usingして使いやすくする
using json = nlohmann::json;
// データがまとまっている階層のキー名
constexpr const char* KEY_ITEMS = "items";

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
    Fin();
}

void StageManager::Load(const char* fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return;
    }

    json stageJson;
    file >> stageJson;

    m_Objects = stageJson[KEY_ITEMS].get<std::vector<GameObject>>();

    file.close();
}

/// <summary>
/// ステージ開始処理
/// 主に各オブジェクトを配置する
/// </summary>
void StageManager::Start()
{
    for (GameObject obj : m_Objects)
    {
        if (obj.id <= FLOOR_00)
        {
            int id = obj.id - FLOOR_00;
            StageObjectManager::GetInstance()->CreateFloor(id, obj.pos, obj.rot, obj.scale);
        }
        else if (obj.id <= PLAYER)
        {
            int id = obj.id - PLAYER;
            PlayerManager::GetInstance()->CreatePlayer(obj.pos, obj.rot, obj.scale);
        }
        else if (obj.id <= BLOCK_00)
        {
            int id = obj.id - BLOCK_00;
            StageObjectManager::GetInstance()->CreateBlock(id, obj.pos, obj.rot, obj.scale);
        }
    }
}

void StageManager::Draw()
{
}

void StageManager::Fin()
{

}
