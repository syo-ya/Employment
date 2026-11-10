#pragma once
#include "../../StageObject.h"

class CollisionAABB;

// è∞ÉNÉâÉX
class SpeedDown : public StageObject
{
public:
	SpeedDown() = default;
	virtual ~SpeedDown() = default;

	void Start() override;
	StageObject* Clone() override;
};
