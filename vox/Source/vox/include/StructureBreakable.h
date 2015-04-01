#pragma once

#include <Box2D/Box2D.h>

#include "Structure.h"

class Box2DSprite;
class Box2DWorld;

class StructureBreakable : public Structure{
public:

	float health;
	float maxHealth;

	StructureBreakable(float _maxHealth, Box2DWorld * _world, int16 _categoryBits, int16 _maskBits = -1, int16 _groupIndex = 0);
	
	virtual void takeDamage(float _damage);

	enum state_t{
		kNORMAL,
		kDAMAGED,
		kDEAD
	} state;
};