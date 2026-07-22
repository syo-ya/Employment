#pragma once
#include "DxLib.h"
#include "../Library/json/json.hpp"
#include <string>

struct GameObject
{
	int id = 1;
	VECTOR pos = {};
	VECTOR rot = {};
	VECTOR scale = {};
	std::string name = "";
};

enum LcateObjectID
{
	FLOOR_00,
	PLAYER,
	BLOCK_00,
};

inline void jsonConvXYZ(const nlohmann::json& j, VECTOR& v)
{
	v.x = j.value("x", 0.0f);
	v.y = j.value("y", 0.0f);
	v.z = j.value("z", 0.0f);
}

inline void from_json(const nlohmann::json& j, GameObject& obj)
{
	obj.id = j.value("id", 0);
	jsonConvXYZ(j.at("pos"), obj.pos);
	jsonConvXYZ(j.at("rot"), obj.rot);
	jsonConvXYZ(j.at("scale"), obj.scale);
	obj.name = j.value("name", "");
}