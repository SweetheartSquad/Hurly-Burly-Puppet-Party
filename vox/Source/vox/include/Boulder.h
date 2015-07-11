#pragma once

#include <Box2D/Box2D.h>

#include "Item.h"

class Box2DSprite;
class Box2DWorld;
class PuppetCharacter;
class Catapult;

class Boulder : public Item{
public:
	Box2DSprite * boulder;
	Catapult * catapult;

	Boulder(Box2DWorld * _world, int16 _categoryBits, int16 _maskBits = -1, int16 _groupIndex = 0);
	~Boulder();	
	
	void update(Step* _step) override;
};