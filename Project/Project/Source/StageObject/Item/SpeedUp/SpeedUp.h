#pragma once
#include "../../StageObject.h"

class CollisionAABB;

// è∞ÉNÉâÉX
class SpeedUp : public StageObject
{
public:
	SpeedUp() = default;
	virtual ~SpeedUp() = default;

	void Start() override;
	StageObject* Clone() override;
};
