#pragma once

#include "PuppetScene.h"

class MeshEntity;
class PuppetCharacter;
class PuppetCharacterDragon;
class Fortification;

class SlayTheDragon : public PuppetScene{
public:
	Sprite * fortBackground;
	Box2DSprite * fortForeground;
	Fortification * fort;

	PuppetCharacterDragon * dragon;

	PuppetCharacter * playerCharacter1;
	PuppetCharacter * playerCharacter2;
	PuppetCharacter * playerCharacter3;
	PuppetCharacter * playerCharacter4;

	explicit SlayTheDragon(PuppetGame * _game);

	virtual void update(Step * _step) override;
};